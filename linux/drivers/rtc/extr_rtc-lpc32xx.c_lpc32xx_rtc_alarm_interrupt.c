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
struct lpc32xx_rtc {int /*<<< orphan*/  rtc; int /*<<< orphan*/  lock; scalar_t__ alarm_enabled; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  LPC32XX_RTC_CTRL ; 
 int LPC32XX_RTC_CTRL_MATCH0 ; 
 int /*<<< orphan*/  LPC32XX_RTC_INTSTAT ; 
 int LPC32XX_RTC_INTSTAT_MATCH0 ; 
 int /*<<< orphan*/  LPC32XX_RTC_MATCH0 ; 
 int RTC_AF ; 
 int RTC_IRQF ; 
 int rtc_readl (struct lpc32xx_rtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_update_irq (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rtc_writel (struct lpc32xx_rtc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t lpc32xx_rtc_alarm_interrupt(int irq, void *dev)
{
	struct lpc32xx_rtc *rtc = dev;

	spin_lock(&rtc->lock);

	/* Disable alarm interrupt */
	rtc_writel(rtc, LPC32XX_RTC_CTRL,
		rtc_readl(rtc, LPC32XX_RTC_CTRL) &
			  ~LPC32XX_RTC_CTRL_MATCH0);
	rtc->alarm_enabled = 0;

	/*
	 * Write a large value to the match value so the RTC won't
	 * keep firing the match status
	 */
	rtc_writel(rtc, LPC32XX_RTC_MATCH0, 0xFFFFFFFF);
	rtc_writel(rtc, LPC32XX_RTC_INTSTAT, LPC32XX_RTC_INTSTAT_MATCH0);

	spin_unlock(&rtc->lock);

	rtc_update_irq(rtc->rtc, 1, RTC_IRQF | RTC_AF);

	return IRQ_HANDLED;
}