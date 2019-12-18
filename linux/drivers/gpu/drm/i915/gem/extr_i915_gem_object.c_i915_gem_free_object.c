#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  free_work; int /*<<< orphan*/  free_list; int /*<<< orphan*/  free_count; } ;
struct drm_i915_private {TYPE_2__ mm; int /*<<< orphan*/  wq; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct drm_i915_gem_object {int /*<<< orphan*/  freed; TYPE_1__ base; } ;
struct drm_gem_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_object_is_framebuffer (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_gem_object_make_unshrinkable (struct drm_i915_gem_object*) ; 
 scalar_t__ llist_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct drm_i915_gem_object* to_intel_bo (struct drm_gem_object*) ; 

void i915_gem_free_object(struct drm_gem_object *gem_obj)
{
	struct drm_i915_gem_object *obj = to_intel_bo(gem_obj);
	struct drm_i915_private *i915 = to_i915(obj->base.dev);

	GEM_BUG_ON(i915_gem_object_is_framebuffer(obj));

	/*
	 * Before we free the object, make sure any pure RCU-only
	 * read-side critical sections are complete, e.g.
	 * i915_gem_busy_ioctl(). For the corresponding synchronized
	 * lookup see i915_gem_object_lookup_rcu().
	 */
	atomic_inc(&i915->mm.free_count);

	/*
	 * This serializes freeing with the shrinker. Since the free
	 * is delayed, first by RCU then by the workqueue, we want the
	 * shrinker to be able to free pages of unreferenced objects,
	 * or else we may oom whilst there are plenty of deferred
	 * freed objects.
	 */
	i915_gem_object_make_unshrinkable(obj);

	/*
	 * Since we require blocking on struct_mutex to unbind the freed
	 * object from the GPU before releasing resources back to the
	 * system, we can not do that directly from the RCU callback (which may
	 * be a softirq context), but must instead then defer that work onto a
	 * kthread. We use the RCU callback rather than move the freed object
	 * directly onto the work queue so that we can mix between using the
	 * worker and performing frees directly from subsequent allocations for
	 * crude but effective memory throttling.
	 */
	if (llist_add(&obj->freed, &i915->mm.free_list))
		queue_work(i915->wq, &i915->mm.free_work);
}