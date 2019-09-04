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
struct cpu_mask_set {int /*<<< orphan*/  mask; int /*<<< orphan*/  used; scalar_t__ gen; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpumask_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ cpumask_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _cpu_mask_set_gen_dec(struct cpu_mask_set *set)
{
	if (cpumask_empty(&set->used) && set->gen) {
		set->gen--;
		cpumask_copy(&set->used, &set->mask);
	}
}