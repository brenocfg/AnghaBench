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
struct llist_node {int /*<<< orphan*/ * next; } ;
struct TYPE_2__ {int /*<<< orphan*/  free_lock; int /*<<< orphan*/  free_list; } ;
struct drm_i915_private {TYPE_1__ mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  __i915_gem_free_objects (struct drm_i915_private*,struct llist_node*) ; 
 struct llist_node* llist_del_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  llist_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (struct llist_node*) ; 

__attribute__((used)) static void i915_gem_flush_free_objects(struct drm_i915_private *i915)
{
	struct llist_node *freed;

	/* Free the oldest, most stale object to keep the free_list short */
	freed = NULL;
	if (!llist_empty(&i915->mm.free_list)) { /* quick test for hotpath */
		/* Only one consumer of llist_del_first() allowed */
		spin_lock(&i915->mm.free_lock);
		freed = llist_del_first(&i915->mm.free_list);
		spin_unlock(&i915->mm.free_lock);
	}
	if (unlikely(freed)) {
		freed->next = NULL;
		__i915_gem_free_objects(i915, freed);
	}
}