#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ time64_t ;
struct tm {int tm_sec; int tm_min; int tm_hour; int tm_mday; int tm_mon; int tm_year; } ;
struct timespec64 {scalar_t__ tv_sec; int tv_nsec; } ;
struct date_time_t {int MilliSecond; int Second; int Minute; int Hour; int Day; int Month; int Year; } ;

/* Variables and functions */
 int NSEC_PER_MSEC ; 
 scalar_t__ UNIX_SECS_1980 ; 
 scalar_t__ UNIX_SECS_2108 ; 
 int /*<<< orphan*/  time64_to_tm (scalar_t__,int /*<<< orphan*/ ,struct tm*) ; 

__attribute__((used)) static void exfat_time_unix2fat(struct timespec64 *ts, struct date_time_t *tp)
{
	time64_t second = ts->tv_sec;
	struct tm tm;

	time64_to_tm(second, 0, &tm);

	if (second < UNIX_SECS_1980) {
		tp->MilliSecond = 0;
		tp->Second	= 0;
		tp->Minute	= 0;
		tp->Hour	= 0;
		tp->Day		= 1;
		tp->Month	= 1;
		tp->Year	= 0;
		return;
	}

	if (second >= UNIX_SECS_2108) {
		tp->MilliSecond = 999;
		tp->Second	= 59;
		tp->Minute	= 59;
		tp->Hour	= 23;
		tp->Day		= 31;
		tp->Month	= 12;
		tp->Year	= 127;
		return;
	}

	tp->MilliSecond = ts->tv_nsec / NSEC_PER_MSEC;
	tp->Second	= tm.tm_sec;
	tp->Minute	= tm.tm_min;
	tp->Hour	= tm.tm_hour;
	tp->Day		= tm.tm_mday;
	tp->Month	= tm.tm_mon + 1;
	tp->Year	= tm.tm_year + 1900 - 1980;
}