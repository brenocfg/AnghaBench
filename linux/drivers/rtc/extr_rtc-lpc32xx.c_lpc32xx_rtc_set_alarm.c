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
typedef  unsigned long u32 ;
struct rtc_wkalrm {scalar_t__ enabled; int /*<<< orphan*/  time; } ;
struct lpc32xx_rtc {int /*<<< orphan*/  lock; scalar_t__ alarm_enabled; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPC32XX_RTC_CTRL ; 
 unsigned long LPC32XX_RTC_CTRL_MATCH0 ; 
 int /*<<< orphan*/  LPC32XX_RTC_INTSTAT ; 
 unsigned long LPC32XX_RTC_INTSTAT_MATCH0 ; 
 int /*<<< orphan*/  LPC32XX_RTC_MATCH0 ; 
 struct lpc32xx_rtc* dev_get_drvdata (struct device*) ; 
 unsigned long rtc_readl (struct lpc32xx_rtc*,int /*<<< orphan*/ ) ; 
 unsigned long rtc_tm_to_time64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtc_writel (struct lpc32xx_rtc*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lpc32xx_rtc_set_alarm(struct device *dev,
	struct rtc_wkalrm *wkalrm)
{
	struct lpc32xx_rtc *rtc = dev_get_drvdata(dev);
	unsigned long alarmsecs;
	u32 tmp;

	alarmsecs = rtc_tm_to_time64(&wkalrm->time);

	spin_lock_irq(&rtc->lock);

	/* Disable alarm during update */
	tmp = rtc_readl(rtc, LPC32XX_RTC_CTRL);
	rtc_writel(rtc, LPC32XX_RTC_CTRL, tmp & ~LPC32XX_RTC_CTRL_MATCH0);

	rtc_writel(rtc, LPC32XX_RTC_MATCH0, alarmsecs);

	rtc->alarm_enabled = wkalrm->enabled;
	if (wkalrm->enabled) {
		rtc_writel(rtc, LPC32XX_RTC_INTSTAT,
			   LPC32XX_RTC_INTSTAT_MATCH0);
		rtc_writel(rtc, LPC32XX_RTC_CTRL, tmp |
			   LPC32XX_RTC_CTRL_MATCH0);
	}

	spin_unlock_irq(&rtc->lock);

	return 0;
}