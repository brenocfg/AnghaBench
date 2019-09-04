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
struct TYPE_3__ {int /*<<< orphan*/  retire_work; } ;
struct drm_i915_private {TYPE_1__ gt; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct drm_i915_gem_object {TYPE_2__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  I915_WAIT_INTERRUPTIBLE ; 
 int /*<<< orphan*/  MAX_SCHEDULE_TIMEOUT ; 
 int drm_gem_create_mmap_offset (TYPE_2__*) ; 
 scalar_t__ flush_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_drain_freed_objects (struct drm_i915_private*) ; 
 int i915_gem_wait_for_idle (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i915_gem_object_create_mmap_offset(struct drm_i915_gem_object *obj)
{
	struct drm_i915_private *dev_priv = to_i915(obj->base.dev);
	int err;

	err = drm_gem_create_mmap_offset(&obj->base);
	if (likely(!err))
		return 0;

	/* Attempt to reap some mmap space from dead objects */
	do {
		err = i915_gem_wait_for_idle(dev_priv,
					     I915_WAIT_INTERRUPTIBLE,
					     MAX_SCHEDULE_TIMEOUT);
		if (err)
			break;

		i915_gem_drain_freed_objects(dev_priv);
		err = drm_gem_create_mmap_offset(&obj->base);
		if (!err)
			break;

	} while (flush_delayed_work(&dev_priv->gt.retire_work));

	return err;
}