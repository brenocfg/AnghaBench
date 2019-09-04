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

__attribute__((used)) static void fix_b0_for_bsp(void)
{
#ifdef CONFIG_HOTPLUG_CPU
	int cpuid;
	static int fix_bsp_b0 = 1;

	cpuid = smp_processor_id();

	/*
	 * Cache the b0 value on the first AP that comes up
	 */
	if (!(fix_bsp_b0 && cpuid))
		return;

	sal_boot_rendez_state[0].br[0] = sal_boot_rendez_state[cpuid].br[0];
	printk ("Fixed BSP b0 value from CPU %d\n", cpuid);

	fix_bsp_b0 = 0;
#endif
}