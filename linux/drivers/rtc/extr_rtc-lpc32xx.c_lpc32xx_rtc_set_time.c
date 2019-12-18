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
struct rtc_time {int dummy; } ;
struct lpc32xx_rtc {int /*<<< orphan*/  lock; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPC32XX_RTC_CTRL ; 
 int LPC32XX_RTC_CTRL_CNTR_DIS ; 
 int /*<<< orphan*/  LPC32XX_RTC_DCOUNT ; 
 int /*<<< orphan*/  LPC32XX_RTC_UCOUNT ; 
 struct lpc32xx_rtc* dev_get_drvdata (struct device*) ; 
 int rtc_readl (struct lpc32xx_rtc*,int /*<<< orphan*/ ) ; 
 int rtc_tm_to_time64 (struct rtc_time*) ; 
 int /*<<< orphan*/  rtc_writel (struct lpc32xx_rtc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lpc32xx_rtc_set_time(struct device *dev, struct rtc_time *time)
{
	struct lpc32xx_rtc *rtc = dev_get_drvdata(dev);
	u32 secs = rtc_tm_to_time64(time);
	u32 tmp;

	spin_lock_irq(&rtc->lock);

	/* RTC must be disabled during count update */
	tmp = rtc_readl(rtc, LPC32XX_RTC_CTRL);
	rtc_writel(rtc, LPC32XX_RTC_CTRL, tmp | LPC32XX_RTC_CTRL_CNTR_DIS);
	rtc_writel(rtc, LPC32XX_RTC_UCOUNT, secs);
	rtc_writel(rtc, LPC32XX_RTC_DCOUNT, 0xFFFFFFFF - secs);
	rtc_writel(rtc, LPC32XX_RTC_CTRL, tmp &= ~LPC32XX_RTC_CTRL_CNTR_DIS);

	spin_unlock_irq(&rtc->lock);

	return 0;
}