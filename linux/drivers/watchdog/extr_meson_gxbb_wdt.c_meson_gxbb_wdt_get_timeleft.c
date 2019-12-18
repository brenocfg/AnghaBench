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
struct meson_gxbb_wdt {scalar_t__ reg_base; } ;

/* Variables and functions */
 unsigned long GXBB_WDT_TCNT_CNT_SHIFT ; 
 scalar_t__ GXBB_WDT_TCNT_REG ; 
 unsigned long GXBB_WDT_TCNT_SETUP_MASK ; 
 unsigned long readl (scalar_t__) ; 
 struct meson_gxbb_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static unsigned int meson_gxbb_wdt_get_timeleft(struct watchdog_device *wdt_dev)
{
	struct meson_gxbb_wdt *data = watchdog_get_drvdata(wdt_dev);
	unsigned long reg;

	reg = readl(data->reg_base + GXBB_WDT_TCNT_REG);

	return ((reg & GXBB_WDT_TCNT_SETUP_MASK) -
		(reg >> GXBB_WDT_TCNT_CNT_SHIFT)) / 1000;
}