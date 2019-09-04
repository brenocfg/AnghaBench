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
 int /*<<< orphan*/  cpu_online_mask ; 
 int /*<<< orphan*/  cpumask_of_node (int) ; 
 int kfd_cpumask_to_apic_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

int kfd_numa_node_to_apic_id(int numa_node_id)
{
	if (numa_node_id == -1) {
		pr_warn("Invalid NUMA Node. Use online CPU mask\n");
		return kfd_cpumask_to_apic_id(cpu_online_mask);
	}
	return kfd_cpumask_to_apic_id(cpumask_of_node(numa_node_id));
}