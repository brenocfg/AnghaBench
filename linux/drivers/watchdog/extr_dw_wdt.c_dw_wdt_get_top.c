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
 scalar_t__ WDOG_TIMEOUT_RANGE_REG_OFFSET ; 
 int dw_wdt_top_in_seconds (struct dw_wdt*,int) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static int dw_wdt_get_top(struct dw_wdt *dw_wdt)
{
	int top = readl(dw_wdt->regs + WDOG_TIMEOUT_RANGE_REG_OFFSET) & 0xF;

	return dw_wdt_top_in_seconds(dw_wdt, top);
}