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
struct tegra_wdt {scalar_t__ tmr_regs; scalar_t__ wdt_regs; } ;

/* Variables and functions */
 scalar_t__ TIMER_PTV ; 
 scalar_t__ WDT_CMD ; 
 int /*<<< orphan*/  WDT_CMD_DISABLE_COUNTER ; 
 scalar_t__ WDT_UNLOCK ; 
 int /*<<< orphan*/  WDT_UNLOCK_PATTERN ; 
 struct tegra_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int tegra_wdt_stop(struct watchdog_device *wdd)
{
	struct tegra_wdt *wdt = watchdog_get_drvdata(wdd);

	writel(WDT_UNLOCK_PATTERN, wdt->wdt_regs + WDT_UNLOCK);
	writel(WDT_CMD_DISABLE_COUNTER, wdt->wdt_regs + WDT_CMD);
	writel(0, wdt->tmr_regs + TIMER_PTV);

	return 0;
}