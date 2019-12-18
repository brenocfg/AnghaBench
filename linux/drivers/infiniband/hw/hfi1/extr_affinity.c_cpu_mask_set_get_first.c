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
struct cpu_mask_set {int /*<<< orphan*/  used; int /*<<< orphan*/  mask; } ;
typedef  int /*<<< orphan*/  cpumask_var_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  _cpu_mask_set_gen_inc (struct cpu_mask_set*) ; 
 int /*<<< orphan*/  cpumask_andnot (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int cpumask_first (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_set_cpu (int,int /*<<< orphan*/ *) ; 
 int nr_cpu_ids ; 

__attribute__((used)) static int cpu_mask_set_get_first(struct cpu_mask_set *set, cpumask_var_t diff)
{
	int cpu;

	if (!diff || !set)
		return -EINVAL;

	_cpu_mask_set_gen_inc(set);

	/* Find out CPUs left in CPU mask */
	cpumask_andnot(diff, &set->mask, &set->used);

	cpu = cpumask_first(diff);
	if (cpu >= nr_cpu_ids) /* empty */
		cpu = -EINVAL;
	else
		cpumask_set_cpu(cpu, &set->used);

	return cpu;
}