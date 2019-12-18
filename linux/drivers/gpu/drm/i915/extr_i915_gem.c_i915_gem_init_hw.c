#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct intel_uncore {int dummy; } ;
struct intel_gt {int /*<<< orphan*/  uc; int /*<<< orphan*/  last_init_time; } ;
struct drm_i915_private {int /*<<< orphan*/  kernel_context; struct intel_gt gt; struct intel_uncore uncore; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  FORCEWAKE_ALL ; 
 scalar_t__ HAS_EDRAM (struct drm_i915_private*) ; 
 int /*<<< orphan*/  HSW_IDICR ; 
 int /*<<< orphan*/  IDIHASHMSK (int) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_HASWELL (struct drm_i915_private*) ; 
 scalar_t__ IS_HSW_GT3 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  LOWER_SLICE_DISABLED ; 
 int /*<<< orphan*/  LOWER_SLICE_ENABLED ; 
 int /*<<< orphan*/  MI_PREDICATE_RESULT_2 ; 
 int i915_ppgtt_init_hw (struct intel_gt*) ; 
 int /*<<< orphan*/  i915_probe_error (struct drm_i915_private*,char*,int) ; 
 int /*<<< orphan*/  init_unused_rings (struct intel_gt*) ; 
 int /*<<< orphan*/  intel_gt_apply_workarounds (struct intel_gt*) ; 
 int /*<<< orphan*/  intel_gt_init_swizzling (struct intel_gt*) ; 
 int intel_gt_terminally_wedged (struct intel_gt*) ; 
 int /*<<< orphan*/  intel_gt_verify_workarounds (struct intel_gt*,char*) ; 
 int /*<<< orphan*/  intel_mocs_init (struct intel_gt*) ; 
 int intel_uc_init_hw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_get (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_put (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_rmw (struct intel_uncore*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_write (struct intel_uncore*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 

int i915_gem_init_hw(struct drm_i915_private *i915)
{
	struct intel_uncore *uncore = &i915->uncore;
	struct intel_gt *gt = &i915->gt;
	int ret;

	BUG_ON(!i915->kernel_context);
	ret = intel_gt_terminally_wedged(gt);
	if (ret)
		return ret;

	gt->last_init_time = ktime_get();

	/* Double layer security blanket, see i915_gem_init() */
	intel_uncore_forcewake_get(uncore, FORCEWAKE_ALL);

	if (HAS_EDRAM(i915) && INTEL_GEN(i915) < 9)
		intel_uncore_rmw(uncore, HSW_IDICR, 0, IDIHASHMSK(0xf));

	if (IS_HASWELL(i915))
		intel_uncore_write(uncore,
				   MI_PREDICATE_RESULT_2,
				   IS_HSW_GT3(i915) ?
				   LOWER_SLICE_ENABLED : LOWER_SLICE_DISABLED);

	/* Apply the GT workarounds... */
	intel_gt_apply_workarounds(gt);
	/* ...and determine whether they are sticking. */
	intel_gt_verify_workarounds(gt, "init");

	intel_gt_init_swizzling(gt);

	/*
	 * At least 830 can leave some of the unused rings
	 * "active" (ie. head != tail) after resume which
	 * will prevent c3 entry. Makes sure all unused rings
	 * are totally idle.
	 */
	init_unused_rings(gt);

	ret = i915_ppgtt_init_hw(gt);
	if (ret) {
		DRM_ERROR("Enabling PPGTT failed (%d)\n", ret);
		goto out;
	}

	/* We can't enable contexts until all firmware is loaded */
	ret = intel_uc_init_hw(&gt->uc);
	if (ret) {
		i915_probe_error(i915, "Enabling uc failed (%d)\n", ret);
		goto out;
	}

	intel_mocs_init(gt);

out:
	intel_uncore_forcewake_put(uncore, FORCEWAKE_ALL);
	return ret;
}