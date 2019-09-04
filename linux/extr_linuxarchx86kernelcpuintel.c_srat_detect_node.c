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
struct cpuinfo_x86 {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void srat_detect_node(struct cpuinfo_x86 *c)
{
#ifdef CONFIG_NUMA
	unsigned node;
	int cpu = smp_processor_id();

	/* Don't do the funky fallback heuristics the AMD version employs
	   for now. */
	node = numa_cpu_node(cpu);
	if (node == NUMA_NO_NODE || !node_online(node)) {
		/* reuse the value from init_cpu_to_node() */
		node = cpu_to_node(cpu);
	}
	numa_set_node(cpu, node);
#endif
}