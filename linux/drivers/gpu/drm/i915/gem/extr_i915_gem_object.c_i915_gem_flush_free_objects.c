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
struct llist_node {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  free_list; } ;
struct drm_i915_private {TYPE_1__ mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  __i915_gem_free_objects (struct drm_i915_private*,struct llist_node*) ; 
 struct llist_node* llist_del_all (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (struct llist_node*) ; 

void i915_gem_flush_free_objects(struct drm_i915_private *i915)
{
	struct llist_node *freed = llist_del_all(&i915->mm.free_list);

	if (unlikely(freed))
		__i915_gem_free_objects(i915, freed);
}