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
typedef  int u32 ;
struct rtc_time {int tm_year; int tm_mday; int tm_hour; int tm_min; int tm_sec; int tm_mon; } ;
struct device {int dummy; } ;
struct aspeed_rtc {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ RTC_CTRL ; 
 int RTC_ENABLE ; 
 scalar_t__ RTC_TIME ; 
 int RTC_UNLOCK ; 
 scalar_t__ RTC_YEAR ; 
 struct aspeed_rtc* dev_get_drvdata (struct device*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int aspeed_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	struct aspeed_rtc *rtc = dev_get_drvdata(dev);
	u32 reg1, reg2, ctrl;
	int year, cent;

	cent = (tm->tm_year + 1900) / 100;
	year = tm->tm_year % 100;

	reg1 = (tm->tm_mday << 24) | (tm->tm_hour << 16) | (tm->tm_min << 8) |
		tm->tm_sec;

	reg2 = ((cent & 0x1f) << 16) | ((year & 0x7f) << 8) |
		((tm->tm_mon + 1) & 0xf);

	ctrl = readl(rtc->base + RTC_CTRL);
	writel(ctrl | RTC_UNLOCK, rtc->base + RTC_CTRL);

	writel(reg1, rtc->base + RTC_TIME);
	writel(reg2, rtc->base + RTC_YEAR);

	/* Re-lock and ensure enable is set now that a time is programmed */
	writel(ctrl | RTC_ENABLE, rtc->base + RTC_CTRL);

	return 0;
}