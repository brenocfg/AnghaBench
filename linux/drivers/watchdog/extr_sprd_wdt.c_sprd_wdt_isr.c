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
struct sprd_wdt {int /*<<< orphan*/  wdd; scalar_t__ base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  SPRD_WDT_INT_CLEAR_BIT ; 
 scalar_t__ SPRD_WDT_INT_CLR ; 
 int /*<<< orphan*/  sprd_wdt_lock (scalar_t__) ; 
 int /*<<< orphan*/  sprd_wdt_unlock (scalar_t__) ; 
 int /*<<< orphan*/  watchdog_notify_pretimeout (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t sprd_wdt_isr(int irq, void *dev_id)
{
	struct sprd_wdt *wdt = (struct sprd_wdt *)dev_id;

	sprd_wdt_unlock(wdt->base);
	writel_relaxed(SPRD_WDT_INT_CLEAR_BIT, wdt->base + SPRD_WDT_INT_CLR);
	sprd_wdt_lock(wdt->base);
	watchdog_notify_pretimeout(&wdt->wdd);
	return IRQ_HANDLED;
}