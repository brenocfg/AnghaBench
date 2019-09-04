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
struct cpu_mask_set {int /*<<< orphan*/  used; } ;

/* Variables and functions */
 int /*<<< orphan*/  _cpu_mask_set_gen_dec (struct cpu_mask_set*) ; 
 int /*<<< orphan*/  cpumask_clear_cpu (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cpu_mask_set_put(struct cpu_mask_set *set, int cpu)
{
	if (!set)
		return;

	cpumask_clear_cpu(cpu, &set->used);
	_cpu_mask_set_gen_dec(set);
}