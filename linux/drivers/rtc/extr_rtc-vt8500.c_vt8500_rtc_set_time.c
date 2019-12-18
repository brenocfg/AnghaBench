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
struct vt8500_rtc {scalar_t__ regbase; } ;
struct rtc_time {int tm_year; int tm_mon; int tm_mday; int tm_wday; int tm_hour; int tm_min; int tm_sec; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int DATE_CENTURY_S ; 
 int DATE_MONTH_S ; 
 int DATE_YEAR_S ; 
 int EINVAL ; 
 int TIME_DOW_S ; 
 int TIME_HOUR_S ; 
 int TIME_MIN_S ; 
 scalar_t__ VT8500_RTC_DS ; 
 scalar_t__ VT8500_RTC_TS ; 
 int bin2bcd (int) ; 
 struct vt8500_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int vt8500_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	struct vt8500_rtc *vt8500_rtc = dev_get_drvdata(dev);

	if (tm->tm_year < 100) {
		dev_warn(dev, "Only years 2000-2199 are supported by the "
			      "hardware!\n");
		return -EINVAL;
	}

	writel((bin2bcd(tm->tm_year % 100) << DATE_YEAR_S)
		| (bin2bcd(tm->tm_mon + 1) << DATE_MONTH_S)
		| (bin2bcd(tm->tm_mday))
		| ((tm->tm_year >= 200) << DATE_CENTURY_S),
		vt8500_rtc->regbase + VT8500_RTC_DS);
	writel((bin2bcd(tm->tm_wday) << TIME_DOW_S)
		| (bin2bcd(tm->tm_hour) << TIME_HOUR_S)
		| (bin2bcd(tm->tm_min) << TIME_MIN_S)
		| (bin2bcd(tm->tm_sec)),
		vt8500_rtc->regbase + VT8500_RTC_TS);

	return 0;
}