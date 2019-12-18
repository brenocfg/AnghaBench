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
struct dw_wdt {scalar_t__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  WDOG_COUNTER_RESTART_KICK_VALUE ; 
 scalar_t__ WDOG_COUNTER_RESTART_REG_OFFSET ; 
 scalar_t__ WDOG_TIMEOUT_RANGE_REG_OFFSET ; 
 int /*<<< orphan*/  dw_wdt_arm_system_reset (struct dw_wdt*) ; 
 scalar_t__ dw_wdt_is_enabled (struct dw_wdt*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 struct dw_wdt* to_dw_wdt (struct watchdog_device*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int dw_wdt_restart(struct watchdog_device *wdd,
			  unsigned long action, void *data)
{
	struct dw_wdt *dw_wdt = to_dw_wdt(wdd);

	writel(0, dw_wdt->regs + WDOG_TIMEOUT_RANGE_REG_OFFSET);
	if (dw_wdt_is_enabled(dw_wdt))
		writel(WDOG_COUNTER_RESTART_KICK_VALUE,
		       dw_wdt->regs + WDOG_COUNTER_RESTART_REG_OFFSET);
	else
		dw_wdt_arm_system_reset(dw_wdt);

	/* wait for reset to assert... */
	mdelay(500);

	return 0;
}