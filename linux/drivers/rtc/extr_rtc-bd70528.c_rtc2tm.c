#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rtc_time {int tm_hour; void* tm_wday; void* tm_year; void* tm_mon; void* tm_mday; void* tm_min; void* tm_sec; } ;
struct TYPE_2__ {int sec; int min; int hour; } ;
struct bd70528_rtc_data {int day; int month; int year; int week; TYPE_1__ time; } ;

/* Variables and functions */
 int BD70528_MASK_RTC_DAY ; 
 int BD70528_MASK_RTC_HOUR ; 
 int BD70528_MASK_RTC_HOUR_24H ; 
 int BD70528_MASK_RTC_HOUR_PM ; 
 int BD70528_MASK_RTC_MINUTE ; 
 int BD70528_MASK_RTC_MONTH ; 
 int BD70528_MASK_RTC_SEC ; 
 int BD70528_MASK_RTC_WEEK ; 
 int BD70528_MASK_RTC_YEAR ; 
 void* bcd2bin (int) ; 

__attribute__((used)) static inline void rtc2tm(struct bd70528_rtc_data *r, struct rtc_time *t)
{
	t->tm_sec = bcd2bin(r->time.sec & BD70528_MASK_RTC_SEC);
	t->tm_min = bcd2bin(r->time.min & BD70528_MASK_RTC_MINUTE);
	t->tm_hour = bcd2bin(r->time.hour & BD70528_MASK_RTC_HOUR);
	/*
	 * If RTC is in 12H mode, then bit BD70528_MASK_RTC_HOUR_PM
	 * is not BCD value but tells whether it is AM or PM
	 */
	if (!(r->time.hour & BD70528_MASK_RTC_HOUR_24H)) {
		t->tm_hour %= 12;
		if (r->time.hour & BD70528_MASK_RTC_HOUR_PM)
			t->tm_hour += 12;
	}
	t->tm_mday = bcd2bin(r->day & BD70528_MASK_RTC_DAY);
	t->tm_mon = bcd2bin(r->month & BD70528_MASK_RTC_MONTH) - 1;
	t->tm_year = 100 + bcd2bin(r->year & BD70528_MASK_RTC_YEAR);
	t->tm_wday = bcd2bin(r->week & BD70528_MASK_RTC_WEEK);
}