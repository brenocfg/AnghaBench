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
 int /*<<< orphan*/  cpu_mask ; 
 int cpumask_any_but (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  cpumask_set_cpu (unsigned int,int /*<<< orphan*/ *) ; 
 int nr_cpumask_bits ; 
 int /*<<< orphan*/  topology_sibling_cpumask (unsigned int) ; 

__attribute__((used)) static int power_cpu_init(unsigned int cpu)
{
	int target;

	/*
	 * 1) If any CPU is set at cpu_mask in the same compute unit, do
	 * nothing.
	 * 2) If no CPU is set at cpu_mask in the same compute unit,
	 * set current ONLINE CPU.
	 *
	 * Note: if there is a CPU aside of the new one already in the
	 * sibling mask, then it is also in cpu_mask.
	 */
	target = cpumask_any_but(topology_sibling_cpumask(cpu), cpu);
	if (target >= nr_cpumask_bits)
		cpumask_set_cpu(cpu, &cpu_mask);
	return 0;
}