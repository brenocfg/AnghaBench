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
struct rtc_time {int tm_sec; int tm_min; int tm_hour; int tm_mday; int tm_wday; int tm_mon; int tm_year; int tm_yday; int tm_isdst; } ;
struct rtc7301_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTC7301_1000_YEAR ; 
 int /*<<< orphan*/  RTC7301_100_YEAR ; 
 int /*<<< orphan*/  RTC7301_10_DAY ; 
 int /*<<< orphan*/  RTC7301_10_HOUR ; 
 int /*<<< orphan*/  RTC7301_10_MIN ; 
 int /*<<< orphan*/  RTC7301_10_MONTH ; 
 int /*<<< orphan*/  RTC7301_10_SEC ; 
 int /*<<< orphan*/  RTC7301_10_YEAR ; 
 int /*<<< orphan*/  RTC7301_1_DAY ; 
 int /*<<< orphan*/  RTC7301_1_HOUR ; 
 int /*<<< orphan*/  RTC7301_1_MIN ; 
 int /*<<< orphan*/  RTC7301_1_MONTH ; 
 int /*<<< orphan*/  RTC7301_1_SEC ; 
 int /*<<< orphan*/  RTC7301_1_YEAR ; 
 int RTC7301_AE ; 
 int /*<<< orphan*/  RTC7301_DAY_OF_WEEK ; 
 int rtc7301_read (struct rtc7301_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtc7301_get_time(struct rtc7301_priv *priv, struct rtc_time *tm,
			     bool alarm)
{
	int year;

	tm->tm_sec = rtc7301_read(priv, RTC7301_1_SEC);
	tm->tm_sec += (rtc7301_read(priv, RTC7301_10_SEC) & ~RTC7301_AE) * 10;
	tm->tm_min = rtc7301_read(priv, RTC7301_1_MIN);
	tm->tm_min += (rtc7301_read(priv, RTC7301_10_MIN) & ~RTC7301_AE) * 10;
	tm->tm_hour = rtc7301_read(priv, RTC7301_1_HOUR);
	tm->tm_hour += (rtc7301_read(priv, RTC7301_10_HOUR) & ~RTC7301_AE) * 10;
	tm->tm_mday = rtc7301_read(priv, RTC7301_1_DAY);
	tm->tm_mday += (rtc7301_read(priv, RTC7301_10_DAY) & ~RTC7301_AE) * 10;

	if (alarm) {
		tm->tm_wday = -1;
		tm->tm_mon = -1;
		tm->tm_year = -1;
		tm->tm_yday = -1;
		tm->tm_isdst = -1;
		return;
	}

	tm->tm_wday = (rtc7301_read(priv, RTC7301_DAY_OF_WEEK) & ~RTC7301_AE);
	tm->tm_mon = rtc7301_read(priv, RTC7301_10_MONTH) * 10 +
		     rtc7301_read(priv, RTC7301_1_MONTH) - 1;
	year = rtc7301_read(priv, RTC7301_1000_YEAR) * 1000 +
	       rtc7301_read(priv, RTC7301_100_YEAR) * 100 +
	       rtc7301_read(priv, RTC7301_10_YEAR) * 10 +
	       rtc7301_read(priv, RTC7301_1_YEAR);

	tm->tm_year = year - 1900;
}