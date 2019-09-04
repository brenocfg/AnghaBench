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
typedef  int /*<<< orphan*/  cpumask_t ;

/* Variables and functions */
 scalar_t__ TOPOLOGY_MODE_HW ; 
 scalar_t__ cpu_present (unsigned int) ; 
 int /*<<< orphan*/  cpumask_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_of (unsigned int) ; 
 int /*<<< orphan*/  cpumask_set_cpu (unsigned int,int /*<<< orphan*/ *) ; 
 int smp_cpu_mtid ; 
 scalar_t__ topology_mode ; 

__attribute__((used)) static cpumask_t cpu_thread_map(unsigned int cpu)
{
	cpumask_t mask;
	int i;

	cpumask_copy(&mask, cpumask_of(cpu));
	if (topology_mode != TOPOLOGY_MODE_HW)
		return mask;
	cpu -= cpu % (smp_cpu_mtid + 1);
	for (i = 0; i <= smp_cpu_mtid; i++)
		if (cpu_present(cpu + i))
			cpumask_set_cpu(cpu + i, &mask);
	return mask;
}