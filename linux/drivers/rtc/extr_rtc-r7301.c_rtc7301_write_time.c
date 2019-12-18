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
struct rtc_time {int tm_sec; int tm_min; int tm_hour; int tm_mday; int tm_wday; int tm_mon; int tm_year; } ;
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
 int /*<<< orphan*/  rtc7301_write (struct rtc7301_priv*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtc7301_write_time(struct rtc7301_priv *priv, struct rtc_time *tm,
			       bool alarm)
{
	int year;

	rtc7301_write(priv, tm->tm_sec % 10, RTC7301_1_SEC);
	rtc7301_write(priv, tm->tm_sec / 10, RTC7301_10_SEC);

	rtc7301_write(priv, tm->tm_min % 10, RTC7301_1_MIN);
	rtc7301_write(priv, tm->tm_min / 10, RTC7301_10_MIN);

	rtc7301_write(priv, tm->tm_hour % 10, RTC7301_1_HOUR);
	rtc7301_write(priv, tm->tm_hour / 10, RTC7301_10_HOUR);

	rtc7301_write(priv, tm->tm_mday % 10, RTC7301_1_DAY);
	rtc7301_write(priv, tm->tm_mday / 10, RTC7301_10_DAY);

	/* Don't care for alarm register */
	rtc7301_write(priv, alarm ? RTC7301_AE : tm->tm_wday,
		      RTC7301_DAY_OF_WEEK);

	if (alarm)
		return;

	rtc7301_write(priv, (tm->tm_mon + 1) % 10, RTC7301_1_MONTH);
	rtc7301_write(priv, (tm->tm_mon + 1) / 10, RTC7301_10_MONTH);

	year = tm->tm_year + 1900;

	rtc7301_write(priv, year % 10, RTC7301_1_YEAR);
	rtc7301_write(priv, (year / 10) % 10, RTC7301_10_YEAR);
	rtc7301_write(priv, (year / 100) % 10, RTC7301_100_YEAR);
	rtc7301_write(priv, year / 1000, RTC7301_1000_YEAR);
}