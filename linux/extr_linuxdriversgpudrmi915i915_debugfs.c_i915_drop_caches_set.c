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
typedef  int u64 ;
struct TYPE_2__ {int /*<<< orphan*/  idle_work; int /*<<< orphan*/  retire_work; int /*<<< orphan*/  active_requests; int /*<<< orphan*/  awake; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_1__ gt; struct drm_device drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int,int) ; 
 int DROP_ACTIVE ; 
 int DROP_ALL ; 
 int DROP_BOUND ; 
 int DROP_FREED ; 
 int DROP_IDLE ; 
 int DROP_RETIRE ; 
 int DROP_SHRINK_ALL ; 
 int DROP_UNBOUND ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I915_SHRINK_BOUND ; 
 int /*<<< orphan*/  I915_SHRINK_UNBOUND ; 
 int I915_WAIT_INTERRUPTIBLE ; 
 int I915_WAIT_LOCKED ; 
 int /*<<< orphan*/  LONG_MAX ; 
 int /*<<< orphan*/  MAX_SCHEDULE_TIMEOUT ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drain_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fs_reclaim_acquire (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs_reclaim_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_drain_freed_objects (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_shrink (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_shrink_all (struct drm_i915_private*) ; 
 int i915_gem_wait_for_idle (struct drm_i915_private*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_retire_requests (struct drm_i915_private*) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
i915_drop_caches_set(void *data, u64 val)
{
	struct drm_i915_private *dev_priv = data;
	struct drm_device *dev = &dev_priv->drm;
	int ret = 0;

	DRM_DEBUG("Dropping caches: 0x%08llx [0x%08llx]\n",
		  val, val & DROP_ALL);

	/* No need to check and wait for gpu resets, only libdrm auto-restarts
	 * on ioctls on -EAGAIN. */
	if (val & (DROP_ACTIVE | DROP_RETIRE)) {
		ret = mutex_lock_interruptible(&dev->struct_mutex);
		if (ret)
			return ret;

		if (val & DROP_ACTIVE)
			ret = i915_gem_wait_for_idle(dev_priv,
						     I915_WAIT_INTERRUPTIBLE |
						     I915_WAIT_LOCKED,
						     MAX_SCHEDULE_TIMEOUT);

		if (val & DROP_RETIRE)
			i915_retire_requests(dev_priv);

		mutex_unlock(&dev->struct_mutex);
	}

	fs_reclaim_acquire(GFP_KERNEL);
	if (val & DROP_BOUND)
		i915_gem_shrink(dev_priv, LONG_MAX, NULL, I915_SHRINK_BOUND);

	if (val & DROP_UNBOUND)
		i915_gem_shrink(dev_priv, LONG_MAX, NULL, I915_SHRINK_UNBOUND);

	if (val & DROP_SHRINK_ALL)
		i915_gem_shrink_all(dev_priv);
	fs_reclaim_release(GFP_KERNEL);

	if (val & DROP_IDLE) {
		do {
			if (READ_ONCE(dev_priv->gt.active_requests))
				flush_delayed_work(&dev_priv->gt.retire_work);
			drain_delayed_work(&dev_priv->gt.idle_work);
		} while (READ_ONCE(dev_priv->gt.awake));
	}

	if (val & DROP_FREED)
		i915_gem_drain_freed_objects(dev_priv);

	return ret;
}