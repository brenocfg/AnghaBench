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
struct TYPE_2__ {int /*<<< orphan*/  real_cpu_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_online_mask ; 
 int /*<<< orphan*/  cpumask_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_clear_cpu (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int cpumask_first (int /*<<< orphan*/ *) ; 
 int cpumask_next (int,int /*<<< orphan*/ *) ; 
 int cpumask_weight (int /*<<< orphan*/ *) ; 
 TYPE_1__ node_affinity ; 
 int /*<<< orphan*/ * topology_sibling_cpumask (int) ; 

void init_real_cpu_mask(void)
{
	int possible, curr_cpu, i, ht;

	cpumask_clear(&node_affinity.real_cpu_mask);

	/* Start with cpu online mask as the real cpu mask */
	cpumask_copy(&node_affinity.real_cpu_mask, cpu_online_mask);

	/*
	 * Remove HT cores from the real cpu mask.  Do this in two steps below.
	 */
	possible = cpumask_weight(&node_affinity.real_cpu_mask);
	ht = cpumask_weight(topology_sibling_cpumask(
				cpumask_first(&node_affinity.real_cpu_mask)));
	/*
	 * Step 1.  Skip over the first N HT siblings and use them as the
	 * "real" cores.  Assumes that HT cores are not enumerated in
	 * succession (except in the single core case).
	 */
	curr_cpu = cpumask_first(&node_affinity.real_cpu_mask);
	for (i = 0; i < possible / ht; i++)
		curr_cpu = cpumask_next(curr_cpu, &node_affinity.real_cpu_mask);
	/*
	 * Step 2.  Remove the remaining HT siblings.  Use cpumask_next() to
	 * skip any gaps.
	 */
	for (; i < possible; i++) {
		cpumask_clear_cpu(curr_cpu, &node_affinity.real_cpu_mask);
		curr_cpu = cpumask_next(curr_cpu, &node_affinity.real_cpu_mask);
	}
}