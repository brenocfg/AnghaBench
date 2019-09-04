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
 unsigned int cpumask_first (int /*<<< orphan*/ ) ; 
 unsigned int nr_cpu_ids ; 
 int /*<<< orphan*/  topology_sibling_cpumask (unsigned int) ; 

__attribute__((used)) static int get_first_sibling(unsigned int cpu)
{
	unsigned int ret;

	ret = cpumask_first(topology_sibling_cpumask(cpu));
	if (ret < nr_cpu_ids)
		return ret;

	return cpu;
}