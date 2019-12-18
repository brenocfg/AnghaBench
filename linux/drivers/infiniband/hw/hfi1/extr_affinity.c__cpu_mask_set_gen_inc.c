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
struct cpu_mask_set {int /*<<< orphan*/  used; int /*<<< orphan*/  gen; int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpumask_clear (int /*<<< orphan*/ *) ; 
 scalar_t__ cpumask_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _cpu_mask_set_gen_inc(struct cpu_mask_set *set)
{
	if (cpumask_equal(&set->mask, &set->used)) {
		/*
		 * We've used up all the CPUs, bump up the generation
		 * and reset the 'used' map
		 */
		set->gen++;
		cpumask_clear(&set->used);
	}
}