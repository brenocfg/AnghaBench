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
struct i915_priolist {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  slab_priorities; } ;

/* Variables and functions */
 TYPE_1__ global ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct i915_priolist*) ; 

void __i915_priolist_free(struct i915_priolist *p)
{
	kmem_cache_free(global.slab_priorities, p);
}