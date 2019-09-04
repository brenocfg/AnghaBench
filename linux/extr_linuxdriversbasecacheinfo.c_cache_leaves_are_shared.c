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
struct cacheinfo {int level; } ;

/* Variables and functions */

__attribute__((used)) static inline bool cache_leaves_are_shared(struct cacheinfo *this_leaf,
					   struct cacheinfo *sib_leaf)
{
	/*
	 * For non-DT/ACPI systems, assume unique level 1 caches, system-wide
	 * shared caches for all other levels. This will be used only if
	 * arch specific code has not populated shared_cpu_map
	 */
	return !(this_leaf->level == 1);
}