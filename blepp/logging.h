/*
 *
 *  blepp - Implementation of the Generic ATTribute Protocol
 *
 *  Copyright (C) 2013, 2014 Edward Rosten
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#ifndef __INC_LIBATTGATT_LOGGING_H
#define __INC_LIBATTGATT_LOGGING_H
#include <iostream>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <cstdint>
#include <blepp/xtoa.h>

namespace BLEPP
{

	enum LogLevels
	{
		Error,
		Warning,
		Info,
		Debug,
		Trace
	};

	static const char* log_types[] = 
	{
		"error",
		"warning",
		"info",
		"debug",
		"trace"
	};
}
namespace BLEPP{

	extern LogLevels log_level;

	template<class T> const T& log_no_uint8(const T& a)
	{
		return a;
	}
	inline int log_no_uint8(uint8_t a)
	{
		return a;
	}

	#define LOGVAR(Y, X) LOG(Y,  #X << " = " << log_no_uint8(X))
	#define LOGVARHEX(Y, X) LOG(Y,  #X << " = " << std::hex <<log_no_uint8(X) <<std::dec)
	#define LOG(X, Y) do{\
		if(X <= BLEPP::log_level)\
		{\
			std::ostringstream blepp_os_4edc409;\
			std::ostream& blepp_out_4edc409(X>=BLEPP::LogLevels::Trace ? std::clog:blepp_os_4edc409);\
			blepp_out_4edc409 << std::fixed << std::setprecision(6) << std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::system_clock::now().time_since_epoch()).count() <<  " " << BLEPP::log_types[X]<< ": "; \
			if(X >= BLEPP::LogLevels::Trace)\
				blepp_out_4edc409 << __FUNCTION__ << ":" << __LINE__ <<": " << Y << std::endl;\
			else if(X >= BLEPP::LogLevels::Debug)\
				blepp_out_4edc409 << __FUNCTION__ << " " << Y << std::endl;\
			else\
				blepp_out_4edc409 << Y << std::endl;\
			if(&blepp_out_4edc409 == &blepp_os_4edc409)\
				std::clog << blepp_os_4edc409.str();\
		}\
	}while(0)

	struct EnterThenLeave
	{
		std::string who;
		EnterThenLeave(const std::string& s)
		:who(s)
		{
			if(BLEPP::log_level >= Trace)\
				std::clog << log_types[Trace] << ": " << who << " entering\n";
		}

		~EnterThenLeave()
		{
			if(BLEPP::log_level >= Trace)\
				std::clog << log_types[Trace] << ": " << who << " leaving\n";
		}

	};

	#define ENTER() EnterThenLeave log_enter_then_leave(__FUNCTION__);
}
#endif
