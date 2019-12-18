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
typedef  int u64 ;
struct TYPE_4__ {int /*<<< orphan*/  idle_work; int /*<<< orphan*/  retire_work; } ;
struct TYPE_3__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_2__ gem; int /*<<< orphan*/  gt; TYPE_1__ drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_ENGINES ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,int,int) ; 
 int DROP_ACTIVE ; 
 int DROP_ALL ; 
 int DROP_BOUND ; 
 int DROP_FREED ; 
 int DROP_IDLE ; 
 int DROP_RESET_ACTIVE ; 
 int DROP_RESET_SEQNO ; 
 int DROP_RETIRE ; 
 int DROP_SHRINK_ALL ; 
 int DROP_UNBOUND ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I915_IDLE_ENGINES_TIMEOUT ; 
 int /*<<< orphan*/  I915_SHRINK_BOUND ; 
 int /*<<< orphan*/  I915_SHRINK_UNBOUND ; 
 int I915_WAIT_INTERRUPTIBLE ; 
 int I915_WAIT_LOCKED ; 
 int /*<<< orphan*/  LONG_MAX ; 
 int /*<<< orphan*/  MAX_SCHEDULE_TIMEOUT ; 
 int /*<<< orphan*/  flush_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fs_reclaim_acquire (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs_reclaim_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_drain_freed_objects (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_shrink (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_gem_shrink_all (struct drm_i915_private*) ; 
 int i915_gem_wait_for_idle (struct drm_i915_private*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_retire_requests (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_engines_are_idle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_gt_handle_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int intel_gt_pm_wait_for_idle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_gt_set_wedged (int /*<<< orphan*/ *) ; 
 scalar_t__ intel_gt_terminally_wedged (int /*<<< orphan*/ *) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ wait_for (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
i915_drop_caches_set(void *data, u64 val)
{
	struct drm_i915_private *i915 = data;

	DRM_DEBUG("Dropping caches: 0x%08llx [0x%08llx]\n",
		  val, val & DROP_ALL);

	if (val & DROP_RESET_ACTIVE &&
	    wait_for(intel_engines_are_idle(&i915->gt),
		     I915_IDLE_ENGINES_TIMEOUT))
		intel_gt_set_wedged(&i915->gt);

	/* No need to check and wait for gpu resets, only libdrm auto-restarts
	 * on ioctls on -EAGAIN. */
	if (val & (DROP_ACTIVE | DROP_IDLE | DROP_RETIRE | DROP_RESET_SEQNO)) {
		int ret;

		ret = mutex_lock_interruptible(&i915->drm.struct_mutex);
		if (ret)
			return ret;

		/*
		 * To finish the flush of the idle_worker, we must complete
		 * the switch-to-kernel-context, which requires a double
		 * pass through wait_for_idle: first queues the switch,
		 * second waits for the switch.
		 */
		if (ret == 0 && val & (DROP_IDLE | DROP_ACTIVE))
			ret = i915_gem_wait_for_idle(i915,
						     I915_WAIT_INTERRUPTIBLE |
						     I915_WAIT_LOCKED,
						     MAX_SCHEDULE_TIMEOUT);

		if (ret == 0 && val & DROP_IDLE)
			ret = i915_gem_wait_for_idle(i915,
						     I915_WAIT_INTERRUPTIBLE |
						     I915_WAIT_LOCKED,
						     MAX_SCHEDULE_TIMEOUT);

		if (val & DROP_RETIRE)
			i915_retire_requests(i915);

		mutex_unlock(&i915->drm.struct_mutex);

		if (ret == 0 && val & DROP_IDLE)
			ret = intel_gt_pm_wait_for_idle(&i915->gt);
	}

	if (val & DROP_RESET_ACTIVE && intel_gt_terminally_wedged(&i915->gt))
		intel_gt_handle_error(&i915->gt, ALL_ENGINES, 0, NULL);

	fs_reclaim_acquire(GFP_KERNEL);
	if (val & DROP_BOUND)
		i915_gem_shrink(i915, LONG_MAX, NULL, I915_SHRINK_BOUND);

	if (val & DROP_UNBOUND)
		i915_gem_shrink(i915, LONG_MAX, NULL, I915_SHRINK_UNBOUND);

	if (val & DROP_SHRINK_ALL)
		i915_gem_shrink_all(i915);
	fs_reclaim_release(GFP_KERNEL);

	if (val & DROP_IDLE) {
		flush_delayed_work(&i915->gem.retire_work);
		flush_work(&i915->gem.idle_work);
	}

	if (val & DROP_FREED)
		i915_gem_drain_freed_objects(i915);

	return 0;
}