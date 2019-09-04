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
struct cpu_mask_set {scalar_t__ gen; int /*<<< orphan*/  used; int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpumask_clear (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void init_cpu_mask_set(struct cpu_mask_set *set)
{
	cpumask_clear(&set->mask);
	cpumask_clear(&set->used);
	set->gen = 0;
}