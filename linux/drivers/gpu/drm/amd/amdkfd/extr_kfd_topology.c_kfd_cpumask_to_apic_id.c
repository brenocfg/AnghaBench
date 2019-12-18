#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cpumask {int dummy; } ;
struct TYPE_2__ {int apicid; } ;

/* Variables and functions */
 TYPE_1__ cpu_data (int) ; 
 struct cpumask const* cpu_none_mask ; 
 int cpumask_first (struct cpumask const*) ; 
 int nr_cpu_ids ; 

__attribute__((used)) static int kfd_cpumask_to_apic_id(const struct cpumask *cpumask)
{
	int first_cpu_of_numa_node;

	if (!cpumask || cpumask == cpu_none_mask)
		return -1;
	first_cpu_of_numa_node = cpumask_first(cpumask);
	if (first_cpu_of_numa_node >= nr_cpu_ids)
		return -1;
#ifdef CONFIG_X86_64
	return cpu_data(first_cpu_of_numa_node).apicid;
#else
	return first_cpu_of_numa_node;
#endif
}