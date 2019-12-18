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
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  pages_pin_count; } ;
struct drm_i915_gem_object {TYPE_1__ mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int /*<<< orphan*/ ) ; 
 int ____i915_gem_object_get_pages (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_object_has_pages (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  i915_gem_object_has_pinned_pages (struct drm_i915_gem_object*) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__before_atomic () ; 
 scalar_t__ unlikely (int) ; 

int __i915_gem_object_get_pages(struct drm_i915_gem_object *obj)
{
	int err;

	err = mutex_lock_interruptible(&obj->mm.lock);
	if (err)
		return err;

	if (unlikely(!i915_gem_object_has_pages(obj))) {
		GEM_BUG_ON(i915_gem_object_has_pinned_pages(obj));

		err = ____i915_gem_object_get_pages(obj);
		if (err)
			goto unlock;

		smp_mb__before_atomic();
	}
	atomic_inc(&obj->mm.pages_pin_count);

unlock:
	mutex_unlock(&obj->mm.lock);
	return err;
}