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
struct watchdog_device {int dummy; } ;
struct lpc18xx_wdt_dev {int /*<<< orphan*/  lock; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ LPC18XX_WDT_FEED ; 
 int LPC18XX_WDT_FEED_MAGIC1 ; 
 int LPC18XX_WDT_FEED_MAGIC2 ; 
 scalar_t__ LPC18XX_WDT_MOD ; 
 int LPC18XX_WDT_MOD_WDEN ; 
 int LPC18XX_WDT_MOD_WDRESET ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct lpc18xx_wdt_dev* watchdog_get_drvdata (struct watchdog_device*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int lpc18xx_wdt_restart(struct watchdog_device *wdt_dev,
			       unsigned long action, void *data)
{
	struct lpc18xx_wdt_dev *lpc18xx_wdt = watchdog_get_drvdata(wdt_dev);
	unsigned long flags;
	int val;

	/*
	 * Incorrect feed sequence causes immediate watchdog reset if enabled.
	 */
	spin_lock_irqsave(&lpc18xx_wdt->lock, flags);

	val = readl(lpc18xx_wdt->base + LPC18XX_WDT_MOD);
	val |= LPC18XX_WDT_MOD_WDEN;
	val |= LPC18XX_WDT_MOD_WDRESET;
	writel(val, lpc18xx_wdt->base + LPC18XX_WDT_MOD);

	writel(LPC18XX_WDT_FEED_MAGIC1, lpc18xx_wdt->base + LPC18XX_WDT_FEED);
	writel(LPC18XX_WDT_FEED_MAGIC2, lpc18xx_wdt->base + LPC18XX_WDT_FEED);

	writel(LPC18XX_WDT_FEED_MAGIC1, lpc18xx_wdt->base + LPC18XX_WDT_FEED);
	writel(LPC18XX_WDT_FEED_MAGIC1, lpc18xx_wdt->base + LPC18XX_WDT_FEED);

	spin_unlock_irqrestore(&lpc18xx_wdt->lock, flags);

	return 0;
}