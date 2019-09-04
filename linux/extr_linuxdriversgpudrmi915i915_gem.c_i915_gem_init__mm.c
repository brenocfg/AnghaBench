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
struct TYPE_2__ {int /*<<< orphan*/  free_work; int /*<<< orphan*/  userfault_list; int /*<<< orphan*/  fence_list; int /*<<< orphan*/  bound_list; int /*<<< orphan*/  unbound_list; int /*<<< orphan*/  free_list; int /*<<< orphan*/  free_lock; int /*<<< orphan*/  obj_lock; int /*<<< orphan*/  object_stat_lock; } ;
struct drm_i915_private {TYPE_1__ mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __i915_gem_free_work ; 
 int /*<<< orphan*/  init_llist_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void i915_gem_init__mm(struct drm_i915_private *i915)
{
	spin_lock_init(&i915->mm.object_stat_lock);
	spin_lock_init(&i915->mm.obj_lock);
	spin_lock_init(&i915->mm.free_lock);

	init_llist_head(&i915->mm.free_list);

	INIT_LIST_HEAD(&i915->mm.unbound_list);
	INIT_LIST_HEAD(&i915->mm.bound_list);
	INIT_LIST_HEAD(&i915->mm.fence_list);
	INIT_LIST_HEAD(&i915->mm.userfault_list);

	INIT_WORK(&i915->mm.free_work, __i915_gem_free_work);
}