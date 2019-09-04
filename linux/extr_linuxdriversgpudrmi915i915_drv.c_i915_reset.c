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
struct i915_gpu_error {int /*<<< orphan*/  flags; int /*<<< orphan*/  reset_count; } ;
struct TYPE_3__ {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_1__ drm; struct i915_gpu_error gpu_error; } ;
struct TYPE_4__ {scalar_t__ reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_ENGINES ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  GEM_TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_RESET_BACKOFF ; 
 int /*<<< orphan*/  I915_RESET_HANDOFF ; 
 int /*<<< orphan*/  LOCKDEP_STILL_OK ; 
 int /*<<< orphan*/  TAINT_WARN ; 
 int /*<<< orphan*/  add_taint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int i915_gem_init_hw (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_reset (struct drm_i915_private*,unsigned int) ; 
 int /*<<< orphan*/  i915_gem_reset_finish (struct drm_i915_private*) ; 
 int i915_gem_reset_prepare (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_set_wedged (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_gem_unset_wedged (struct drm_i915_private*) ; 
 int i915_ggtt_enable_hw (struct drm_i915_private*) ; 
 TYPE_2__ i915_modparams ; 
 int /*<<< orphan*/  i915_queue_hangcheck (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_retire_requests (struct drm_i915_private*) ; 
 int intel_gpu_reset (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_has_gpu_reset (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_overlay_reset (struct drm_i915_private*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void i915_reset(struct drm_i915_private *i915,
		unsigned int stalled_mask,
		const char *reason)
{
	struct i915_gpu_error *error = &i915->gpu_error;
	int ret;
	int i;

	GEM_TRACE("flags=%lx\n", error->flags);

	might_sleep();
	lockdep_assert_held(&i915->drm.struct_mutex);
	GEM_BUG_ON(!test_bit(I915_RESET_BACKOFF, &error->flags));

	if (!test_bit(I915_RESET_HANDOFF, &error->flags))
		return;

	/* Clear any previous failed attempts at recovery. Time to try again. */
	if (!i915_gem_unset_wedged(i915))
		goto wakeup;

	if (reason)
		dev_notice(i915->drm.dev, "Resetting chip for %s\n", reason);
	error->reset_count++;

	disable_irq(i915->drm.irq);
	ret = i915_gem_reset_prepare(i915);
	if (ret) {
		dev_err(i915->drm.dev, "GPU recovery failed\n");
		goto taint;
	}

	if (!intel_has_gpu_reset(i915)) {
		if (i915_modparams.reset)
			dev_err(i915->drm.dev, "GPU reset not supported\n");
		else
			DRM_DEBUG_DRIVER("GPU reset disabled\n");
		goto error;
	}

	for (i = 0; i < 3; i++) {
		ret = intel_gpu_reset(i915, ALL_ENGINES);
		if (ret == 0)
			break;

		msleep(100);
	}
	if (ret) {
		dev_err(i915->drm.dev, "Failed to reset chip\n");
		goto taint;
	}

	/* Ok, now get things going again... */

	/*
	 * Everything depends on having the GTT running, so we need to start
	 * there.
	 */
	ret = i915_ggtt_enable_hw(i915);
	if (ret) {
		DRM_ERROR("Failed to re-enable GGTT following reset (%d)\n",
			  ret);
		goto error;
	}

	i915_gem_reset(i915, stalled_mask);
	intel_overlay_reset(i915);

	/*
	 * Next we need to restore the context, but we don't use those
	 * yet either...
	 *
	 * Ring buffer needs to be re-initialized in the KMS case, or if X
	 * was running at the time of the reset (i.e. we weren't VT
	 * switched away).
	 */
	ret = i915_gem_init_hw(i915);
	if (ret) {
		DRM_ERROR("Failed to initialise HW following reset (%d)\n",
			  ret);
		goto error;
	}

	i915_queue_hangcheck(i915);

finish:
	i915_gem_reset_finish(i915);
	enable_irq(i915->drm.irq);

wakeup:
	clear_bit(I915_RESET_HANDOFF, &error->flags);
	wake_up_bit(&error->flags, I915_RESET_HANDOFF);
	return;

taint:
	/*
	 * History tells us that if we cannot reset the GPU now, we
	 * never will. This then impacts everything that is run
	 * subsequently. On failing the reset, we mark the driver
	 * as wedged, preventing further execution on the GPU.
	 * We also want to go one step further and add a taint to the
	 * kernel so that any subsequent faults can be traced back to
	 * this failure. This is important for CI, where if the
	 * GPU/driver fails we would like to reboot and restart testing
	 * rather than continue on into oblivion. For everyone else,
	 * the system should still plod along, but they have been warned!
	 */
	add_taint(TAINT_WARN, LOCKDEP_STILL_OK);
error:
	i915_gem_set_wedged(i915);
	i915_retire_requests(i915);
	goto finish;
}