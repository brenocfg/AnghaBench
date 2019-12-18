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
struct rtc_wkalrm {int pending; int /*<<< orphan*/  time; int /*<<< orphan*/  enabled; } ;
struct lpc32xx_rtc {int /*<<< orphan*/  alarm_enabled; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPC32XX_RTC_INTSTAT ; 
 int LPC32XX_RTC_INTSTAT_MATCH0 ; 
 int /*<<< orphan*/  LPC32XX_RTC_MATCH0 ; 
 struct lpc32xx_rtc* dev_get_drvdata (struct device*) ; 
 int rtc_readl (struct lpc32xx_rtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_time64_to_tm (int,int /*<<< orphan*/ *) ; 
 int rtc_valid_tm (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lpc32xx_rtc_read_alarm(struct device *dev,
	struct rtc_wkalrm *wkalrm)
{
	struct lpc32xx_rtc *rtc = dev_get_drvdata(dev);

	rtc_time64_to_tm(rtc_readl(rtc, LPC32XX_RTC_MATCH0), &wkalrm->time);
	wkalrm->enabled = rtc->alarm_enabled;
	wkalrm->pending = !!(rtc_readl(rtc, LPC32XX_RTC_INTSTAT) &
		LPC32XX_RTC_INTSTAT_MATCH0);

	return rtc_valid_tm(&wkalrm->time);
}