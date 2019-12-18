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
typedef  int uint8_t ;
struct rtc_time {int tm_year; int tm_mon; int tm_mday; int tm_hour; int tm_min; scalar_t__ tm_sec; } ;
struct da9055 {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9055_REG_ALARM_MI ; 
 int DA9055_RTC_ALM_DAY ; 
 int DA9055_RTC_ALM_HOUR ; 
 int DA9055_RTC_ALM_MIN ; 
 int DA9055_RTC_ALM_MONTH ; 
 int DA9055_RTC_ALM_YEAR ; 
 int da9055_group_read (struct da9055*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int rtc_valid_tm (struct rtc_time*) ; 

__attribute__((used)) static int da9055_read_alarm(struct da9055 *da9055, struct rtc_time *rtc_tm)
{
	int ret;
	uint8_t v[5];

	ret = da9055_group_read(da9055, DA9055_REG_ALARM_MI, 5, v);
	if (ret != 0) {
		dev_err(da9055->dev, "Failed to group read ALM: %d\n", ret);
		return ret;
	}

	rtc_tm->tm_year = (v[4] & DA9055_RTC_ALM_YEAR) + 100;
	rtc_tm->tm_mon  = (v[3] & DA9055_RTC_ALM_MONTH) - 1;
	rtc_tm->tm_mday = v[2] & DA9055_RTC_ALM_DAY;
	rtc_tm->tm_hour = v[1] & DA9055_RTC_ALM_HOUR;
	rtc_tm->tm_min  = v[0] & DA9055_RTC_ALM_MIN;
	rtc_tm->tm_sec = 0;

	return rtc_valid_tm(rtc_tm);
}