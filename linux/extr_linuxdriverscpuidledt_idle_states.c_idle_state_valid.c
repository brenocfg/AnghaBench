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
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  cpumask_t ;

/* Variables and functions */
 int cpumask_first (int /*<<< orphan*/  const*) ; 
 int cpumask_next (int,int /*<<< orphan*/  const*) ; 
 int nr_cpu_ids ; 
 struct device_node* of_cpu_device_node_get (int) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,unsigned int) ; 

__attribute__((used)) static bool idle_state_valid(struct device_node *state_node, unsigned int idx,
			     const cpumask_t *cpumask)
{
	int cpu;
	struct device_node *cpu_node, *curr_state_node;
	bool valid = true;

	/*
	 * Compare idle state phandles for index idx on all CPUs in the
	 * CPUidle driver cpumask. Start from next logical cpu following
	 * cpumask_first(cpumask) since that's the CPU state_node was
	 * retrieved from. If a mismatch is found bail out straight
	 * away since we certainly hit a firmware misconfiguration.
	 */
	for (cpu = cpumask_next(cpumask_first(cpumask), cpumask);
	     cpu < nr_cpu_ids; cpu = cpumask_next(cpu, cpumask)) {
		cpu_node = of_cpu_device_node_get(cpu);
		curr_state_node = of_parse_phandle(cpu_node, "cpu-idle-states",
						   idx);
		if (state_node != curr_state_node)
			valid = false;

		of_node_put(curr_state_node);
		of_node_put(cpu_node);
		if (!valid)
			break;
	}

	return valid;
}