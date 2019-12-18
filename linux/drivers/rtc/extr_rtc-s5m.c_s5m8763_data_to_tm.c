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
typedef  int u8 ;
struct rtc_time {int tm_sec; int tm_min; int tm_hour; int tm_wday; int tm_mday; int tm_mon; int tm_year; } ;

/* Variables and functions */
 int HOUR_12 ; 
 int HOUR_PM ; 
 size_t RTC_DATE ; 
 size_t RTC_HOUR ; 
 size_t RTC_MIN ; 
 size_t RTC_MONTH ; 
 size_t RTC_SEC ; 
 size_t RTC_WEEKDAY ; 
 size_t RTC_YEAR1 ; 
 size_t RTC_YEAR2 ; 
 int bcd2bin (int) ; 

__attribute__((used)) static void s5m8763_data_to_tm(u8 *data, struct rtc_time *tm)
{
	tm->tm_sec = bcd2bin(data[RTC_SEC]);
	tm->tm_min = bcd2bin(data[RTC_MIN]);

	if (data[RTC_HOUR] & HOUR_12) {
		tm->tm_hour = bcd2bin(data[RTC_HOUR] & 0x1f);
		if (data[RTC_HOUR] & HOUR_PM)
			tm->tm_hour += 12;
	} else {
		tm->tm_hour = bcd2bin(data[RTC_HOUR] & 0x3f);
	}

	tm->tm_wday = data[RTC_WEEKDAY] & 0x07;
	tm->tm_mday = bcd2bin(data[RTC_DATE]);
	tm->tm_mon = bcd2bin(data[RTC_MONTH]);
	tm->tm_year = bcd2bin(data[RTC_YEAR1]) + bcd2bin(data[RTC_YEAR2]) * 100;
	tm->tm_year -= 1900;
}