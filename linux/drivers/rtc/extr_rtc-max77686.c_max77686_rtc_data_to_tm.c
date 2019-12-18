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
typedef  int u8 ;
struct rtc_time {int tm_sec; int tm_min; int tm_hour; int tm_mday; int tm_mon; int tm_year; scalar_t__ tm_isdst; scalar_t__ tm_yday; scalar_t__ tm_wday; } ;
struct max77686_rtc_info {TYPE_1__* drv_data; scalar_t__ rtc_24hr_mode; } ;
struct TYPE_2__ {int mask; int /*<<< orphan*/  alarm_enable_reg; } ;

/* Variables and functions */
 int HOUR_PM_MASK ; 
 size_t RTC_DATE ; 
 size_t RTC_HOUR ; 
 size_t RTC_MIN ; 
 size_t RTC_MONTH ; 
 size_t RTC_SEC ; 
 size_t RTC_WEEKDAY ; 
 size_t RTC_YEAR ; 
 scalar_t__ ffs (int) ; 

__attribute__((used)) static void max77686_rtc_data_to_tm(u8 *data, struct rtc_time *tm,
				    struct max77686_rtc_info *info)
{
	u8 mask = info->drv_data->mask;

	tm->tm_sec = data[RTC_SEC] & mask;
	tm->tm_min = data[RTC_MIN] & mask;
	if (info->rtc_24hr_mode) {
		tm->tm_hour = data[RTC_HOUR] & 0x1f;
	} else {
		tm->tm_hour = data[RTC_HOUR] & 0x0f;
		if (data[RTC_HOUR] & HOUR_PM_MASK)
			tm->tm_hour += 12;
	}

	/* Only a single bit is set in data[], so fls() would be equivalent */
	tm->tm_wday = ffs(data[RTC_WEEKDAY] & mask) - 1;
	tm->tm_mday = data[RTC_DATE] & 0x1f;
	tm->tm_mon = (data[RTC_MONTH] & 0x0f) - 1;
	tm->tm_year = data[RTC_YEAR] & mask;
	tm->tm_yday = 0;
	tm->tm_isdst = 0;

	/*
	 * MAX77686 uses 1 bit from sec/min/hour/etc RTC registers and the
	 * year values are just 0..99 so add 100 to support up to 2099.
	 */
	if (!info->drv_data->alarm_enable_reg)
		tm->tm_year += 100;
}