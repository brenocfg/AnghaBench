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
struct rtc_time {int dummy; } ;
struct lpc32xx_rtc {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPC32XX_RTC_UCOUNT ; 
 struct lpc32xx_rtc* dev_get_drvdata (struct device*) ; 
 unsigned long rtc_readl (struct lpc32xx_rtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_time64_to_tm (unsigned long,struct rtc_time*) ; 

__attribute__((used)) static int lpc32xx_rtc_read_time(struct device *dev, struct rtc_time *time)
{
	unsigned long elapsed_sec;
	struct lpc32xx_rtc *rtc = dev_get_drvdata(dev);

	elapsed_sec = rtc_readl(rtc, LPC32XX_RTC_UCOUNT);
	rtc_time64_to_tm(elapsed_sec, time);

	return 0;
}