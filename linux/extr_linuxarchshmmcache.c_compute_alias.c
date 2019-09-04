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
struct cache_info {int alias_mask; int n_aliases; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 

__attribute__((used)) static void compute_alias(struct cache_info *c)
{
#ifdef CONFIG_MMU
	c->alias_mask = ((c->sets - 1) << c->entry_shift) & ~(PAGE_SIZE - 1);
#else
	c->alias_mask = 0;
#endif
	c->n_aliases = c->alias_mask ? (c->alias_mask >> PAGE_SHIFT) + 1 : 0;
}