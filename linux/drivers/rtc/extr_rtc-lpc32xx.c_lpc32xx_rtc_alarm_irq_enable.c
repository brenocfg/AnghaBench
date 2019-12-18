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
typedef  int /*<<< orphan*/  u32 ;
struct lpc32xx_rtc {int alarm_enabled; int /*<<< orphan*/  lock; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPC32XX_RTC_CTRL ; 
 int /*<<< orphan*/  LPC32XX_RTC_CTRL_MATCH0 ; 
 struct lpc32xx_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  rtc_readl (struct lpc32xx_rtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_writel (struct lpc32xx_rtc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lpc32xx_rtc_alarm_irq_enable(struct device *dev,
	unsigned int enabled)
{
	struct lpc32xx_rtc *rtc = dev_get_drvdata(dev);
	u32 tmp;

	spin_lock_irq(&rtc->lock);
	tmp = rtc_readl(rtc, LPC32XX_RTC_CTRL);

	if (enabled) {
		rtc->alarm_enabled = 1;
		tmp |= LPC32XX_RTC_CTRL_MATCH0;
	} else {
		rtc->alarm_enabled = 0;
		tmp &= ~LPC32XX_RTC_CTRL_MATCH0;
	}

	rtc_writel(rtc, LPC32XX_RTC_CTRL, tmp);
	spin_unlock_irq(&rtc->lock);

	return 0;
}