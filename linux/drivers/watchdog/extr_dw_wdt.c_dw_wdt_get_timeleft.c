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
struct dw_wdt {unsigned int rate; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ WDOG_CURRENT_COUNT_REG_OFFSET ; 
 unsigned int readl (scalar_t__) ; 
 struct dw_wdt* to_dw_wdt (struct watchdog_device*) ; 

__attribute__((used)) static unsigned int dw_wdt_get_timeleft(struct watchdog_device *wdd)
{
	struct dw_wdt *dw_wdt = to_dw_wdt(wdd);

	return readl(dw_wdt->regs + WDOG_CURRENT_COUNT_REG_OFFSET) /
		dw_wdt->rate;
}