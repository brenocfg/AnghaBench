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
struct dw_wdt {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ WDOG_CONTROL_REG_OFFSET ; 
 int WDOG_CONTROL_REG_WDT_EN_MASK ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static inline int dw_wdt_is_enabled(struct dw_wdt *dw_wdt)
{
	return readl(dw_wdt->regs + WDOG_CONTROL_REG_OFFSET) &
		WDOG_CONTROL_REG_WDT_EN_MASK;
}