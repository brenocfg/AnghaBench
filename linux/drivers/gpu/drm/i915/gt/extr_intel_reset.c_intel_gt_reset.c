#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  flags; } ;
struct intel_gt {TYPE_3__ reset; TYPE_4__* i915; } ;
typedef  int /*<<< orphan*/  intel_engine_mask_t ;
struct TYPE_17__ {scalar_t__ reset; } ;
struct TYPE_14__ {int /*<<< orphan*/  dev; } ;
struct TYPE_13__ {int /*<<< orphan*/  reset_count; } ;
struct TYPE_16__ {TYPE_2__ drm; TYPE_1__ gpu_error; } ;
struct TYPE_12__ {scalar_t__ gpu_reset_clobbers_display; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  GEM_TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_RESET_BACKOFF ; 
 TYPE_10__* INTEL_INFO (TYPE_4__*) ; 
 int /*<<< orphan*/  TAINT_WARN ; 
 int /*<<< orphan*/  __intel_gt_set_wedged (struct intel_gt*) ; 
 int /*<<< orphan*/  __intel_gt_unset_wedged (struct intel_gt*) ; 
 int /*<<< orphan*/  add_taint_for_CI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ do_reset (struct intel_gt*,int /*<<< orphan*/ ) ; 
 int i915_gem_init_hw (TYPE_4__*) ; 
 TYPE_8__ i915_modparams ; 
 int /*<<< orphan*/  intel_gt_queue_hangcheck (struct intel_gt*) ; 
 int /*<<< orphan*/  intel_has_gpu_reset (TYPE_4__*) ; 
 int /*<<< orphan*/  intel_overlay_reset (TYPE_4__*) ; 
 int /*<<< orphan*/  intel_runtime_pm_disable_interrupts (TYPE_4__*) ; 
 int /*<<< orphan*/  intel_runtime_pm_enable_interrupts (TYPE_4__*) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_finish (struct intel_gt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_prepare (struct intel_gt*) ; 
 int resume (struct intel_gt*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void intel_gt_reset(struct intel_gt *gt,
		    intel_engine_mask_t stalled_mask,
		    const char *reason)
{
	intel_engine_mask_t awake;
	int ret;

	GEM_TRACE("flags=%lx\n", gt->reset.flags);

	might_sleep();
	GEM_BUG_ON(!test_bit(I915_RESET_BACKOFF, &gt->reset.flags));
	mutex_lock(&gt->reset.mutex);

	/* Clear any previous failed attempts at recovery. Time to try again. */
	if (!__intel_gt_unset_wedged(gt))
		goto unlock;

	if (reason)
		dev_notice(gt->i915->drm.dev,
			   "Resetting chip for %s\n", reason);
	atomic_inc(&gt->i915->gpu_error.reset_count);

	awake = reset_prepare(gt);

	if (!intel_has_gpu_reset(gt->i915)) {
		if (i915_modparams.reset)
			dev_err(gt->i915->drm.dev, "GPU reset not supported\n");
		else
			DRM_DEBUG_DRIVER("GPU reset disabled\n");
		goto error;
	}

	if (INTEL_INFO(gt->i915)->gpu_reset_clobbers_display)
		intel_runtime_pm_disable_interrupts(gt->i915);

	if (do_reset(gt, stalled_mask)) {
		dev_err(gt->i915->drm.dev, "Failed to reset chip\n");
		goto taint;
	}

	if (INTEL_INFO(gt->i915)->gpu_reset_clobbers_display)
		intel_runtime_pm_enable_interrupts(gt->i915);

	intel_overlay_reset(gt->i915);

	/*
	 * Next we need to restore the context, but we don't use those
	 * yet either...
	 *
	 * Ring buffer needs to be re-initialized in the KMS case, or if X
	 * was running at the time of the reset (i.e. we weren't VT
	 * switched away).
	 */
	ret = i915_gem_init_hw(gt->i915);
	if (ret) {
		DRM_ERROR("Failed to initialise HW following reset (%d)\n",
			  ret);
		goto taint;
	}

	ret = resume(gt);
	if (ret)
		goto taint;

	intel_gt_queue_hangcheck(gt);

finish:
	reset_finish(gt, awake);
unlock:
	mutex_unlock(&gt->reset.mutex);
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
	add_taint_for_CI(TAINT_WARN);
error:
	__intel_gt_set_wedged(gt);
	goto finish;
}