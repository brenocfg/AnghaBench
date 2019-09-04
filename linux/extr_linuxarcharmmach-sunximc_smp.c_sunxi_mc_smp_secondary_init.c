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
 int /*<<< orphan*/  sunxi_cpu0_hotplug_support_set (int) ; 

__attribute__((used)) static void sunxi_mc_smp_secondary_init(unsigned int cpu)
{
	/* Clear hotplug support magic flags for cpu0 */
	if (cpu == 0)
		sunxi_cpu0_hotplug_support_set(false);
}