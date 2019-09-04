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

/* Variables and functions */
 int /*<<< orphan*/  omap2_can_sleep () ; 
 int /*<<< orphan*/  omap2_enter_full_retention () ; 
 int /*<<< orphan*/  omap2_enter_mpu_retention () ; 
 scalar_t__ omap_irq_pending () ; 

__attribute__((used)) static void omap2_pm_idle(void)
{
	if (!omap2_can_sleep()) {
		if (omap_irq_pending())
			return;
		omap2_enter_mpu_retention();
		return;
	}

	if (omap_irq_pending())
		return;

	omap2_enter_full_retention();
}