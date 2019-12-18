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
struct sirfsoc_rtc_drv {unsigned long overflow_rtc; } ;
struct rtc_time {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 unsigned long BITS_PER_LONG ; 
 int /*<<< orphan*/  RTC_CN ; 
 unsigned long RTC_SHIFT ; 
 int /*<<< orphan*/  cpu_relax () ; 
 struct sirfsoc_rtc_drv* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  rtc_time_to_tm (unsigned long,struct rtc_time*) ; 
 unsigned long sirfsoc_rtc_readl (struct sirfsoc_rtc_drv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sirfsoc_rtc_read_time(struct device *dev,
		struct rtc_time *tm)
{
	unsigned long tmp_rtc = 0;
	struct sirfsoc_rtc_drv *rtcdrv;
	rtcdrv = dev_get_drvdata(dev);
	/*
	 * This patch is taken from WinCE - Need to validate this for
	 * correctness. To work around sirfsoc RTC counter double sync logic
	 * fail, read several times to make sure get stable value.
	 */
	do {
		tmp_rtc = sirfsoc_rtc_readl(rtcdrv, RTC_CN);
		cpu_relax();
	} while (tmp_rtc != sirfsoc_rtc_readl(rtcdrv, RTC_CN));

	rtc_time_to_tm(rtcdrv->overflow_rtc << (BITS_PER_LONG - RTC_SHIFT) |
					tmp_rtc >> RTC_SHIFT, tm);
	return 0;
}