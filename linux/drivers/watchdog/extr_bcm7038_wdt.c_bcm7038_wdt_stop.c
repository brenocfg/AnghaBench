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
struct bcm7038_watchdog {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ WDT_CMD_REG ; 
 int /*<<< orphan*/  WDT_STOP_1 ; 
 int /*<<< orphan*/  WDT_STOP_2 ; 
 struct bcm7038_watchdog* watchdog_get_drvdata (struct watchdog_device*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int bcm7038_wdt_stop(struct watchdog_device *wdog)
{
	struct bcm7038_watchdog *wdt = watchdog_get_drvdata(wdog);

	writel(WDT_STOP_1, wdt->base + WDT_CMD_REG);
	writel(WDT_STOP_2, wdt->base + WDT_CMD_REG);

	return 0;
}