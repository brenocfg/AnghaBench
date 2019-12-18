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
struct armada_37xx_watchdog {scalar_t__ reg; int /*<<< orphan*/  cpu_misc; } ;

/* Variables and functions */
 scalar_t__ CNTR_CTRL (int /*<<< orphan*/ ) ; 
 int CNTR_CTRL_ACTIVE ; 
 int /*<<< orphan*/  CNTR_ID_WDOG ; 
 int /*<<< orphan*/  WDT_TIMER_SELECT ; 
 int WDT_TIMER_SELECT_MASK ; 
 int WDT_TIMER_SELECT_VAL ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static bool armada_37xx_wdt_is_running(struct armada_37xx_watchdog *dev)
{
	u32 reg;

	regmap_read(dev->cpu_misc, WDT_TIMER_SELECT, &reg);
	if ((reg & WDT_TIMER_SELECT_MASK) != WDT_TIMER_SELECT_VAL)
		return false;

	reg = readl(dev->reg + CNTR_CTRL(CNTR_ID_WDOG));
	return !!(reg & CNTR_CTRL_ACTIVE);
}