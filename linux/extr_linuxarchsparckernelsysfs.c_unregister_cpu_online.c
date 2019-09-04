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

__attribute__((used)) static int unregister_cpu_online(unsigned int cpu)
{
#ifdef CONFIG_HOTPLUG_CPU
	struct cpu *c = &per_cpu(cpu_devices, cpu);
	struct device *s = &c->dev;
	int i;

	unregister_mmu_stats(s);
	for (i = 0; i < ARRAY_SIZE(cpu_core_attrs); i++)
		device_remove_file(s, &cpu_core_attrs[i]);
#endif
	return 0;
}