#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  struct_mutex; } ;
struct TYPE_4__ {int awake; int /*<<< orphan*/  idle_work; int /*<<< orphan*/  retire_work; } ;
struct TYPE_6__ {int /*<<< orphan*/  hangcheck_work; } ;
struct drm_i915_private {TYPE_2__ drm; TYPE_1__ gt; TYPE_3__ gpu_error; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  GEM_TRACE (char*) ; 
 int I915_WAIT_FOR_IDLE_BOOST ; 
 int I915_WAIT_INTERRUPTIBLE ; 
 int I915_WAIT_LOCKED ; 
 int /*<<< orphan*/  MAX_SCHEDULE_TIMEOUT ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  assert_kernel_context_is_current (struct drm_i915_private*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drain_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i915_gem_set_wedged (struct drm_i915_private*) ; 
 int i915_gem_switch_to_kernel_context (struct drm_i915_private*) ; 
 int i915_gem_wait_for_idle (struct drm_i915_private*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_retire_requests (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_terminally_wedged (TYPE_3__*) ; 
 int /*<<< orphan*/  intel_engines_are_idle (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_get (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_suspend_gt_powersave (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_uc_suspend (struct drm_i915_private*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int i915_gem_suspend(struct drm_i915_private *i915)
{
	int ret;

	GEM_TRACE("\n");

	intel_runtime_pm_get(i915);
	intel_suspend_gt_powersave(i915);

	mutex_lock(&i915->drm.struct_mutex);

	/*
	 * We have to flush all the executing contexts to main memory so
	 * that they can saved in the hibernation image. To ensure the last
	 * context image is coherent, we have to switch away from it. That
	 * leaves the i915->kernel_context still active when
	 * we actually suspend, and its image in memory may not match the GPU
	 * state. Fortunately, the kernel_context is disposable and we do
	 * not rely on its state.
	 */
	if (!i915_terminally_wedged(&i915->gpu_error)) {
		ret = i915_gem_switch_to_kernel_context(i915);
		if (ret)
			goto err_unlock;

		ret = i915_gem_wait_for_idle(i915,
					     I915_WAIT_INTERRUPTIBLE |
					     I915_WAIT_LOCKED |
					     I915_WAIT_FOR_IDLE_BOOST,
					     MAX_SCHEDULE_TIMEOUT);
		if (ret && ret != -EIO)
			goto err_unlock;

		assert_kernel_context_is_current(i915);
	}
	i915_retire_requests(i915); /* ensure we flush after wedging */

	mutex_unlock(&i915->drm.struct_mutex);

	intel_uc_suspend(i915);

	cancel_delayed_work_sync(&i915->gpu_error.hangcheck_work);
	cancel_delayed_work_sync(&i915->gt.retire_work);

	/*
	 * As the idle_work is rearming if it detects a race, play safe and
	 * repeat the flush until it is definitely idle.
	 */
	drain_delayed_work(&i915->gt.idle_work);

	/*
	 * Assert that we successfully flushed all the work and
	 * reset the GPU back to its idle, low power state.
	 */
	WARN_ON(i915->gt.awake);
	if (WARN_ON(!intel_engines_are_idle(i915)))
		i915_gem_set_wedged(i915); /* no hope, discard everything */

	intel_runtime_pm_put(i915);
	return 0;

err_unlock:
	mutex_unlock(&i915->drm.struct_mutex);
	intel_runtime_pm_put(i915);
	return ret;
}