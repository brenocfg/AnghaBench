#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct intel_gt {TYPE_2__* i915; } ;
struct TYPE_7__ {scalar_t__ reset; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {TYPE_1__ drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETIME ; 
 int /*<<< orphan*/  GEM_TRACE_DUMP () ; 
 int /*<<< orphan*/  I915_GEM_IDLE_TIMEOUT ; 
 int I915_WAIT_FOR_IDLE_BOOST ; 
 int I915_WAIT_LOCKED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  i915_gem_wait_for_idle (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 TYPE_3__ i915_modparams ; 
 scalar_t__ i915_retire_requests (TYPE_2__*) ; 
 int /*<<< orphan*/  intel_gt_is_wedged (struct intel_gt*) ; 
 scalar_t__ intel_gt_pm_wait_for_idle (struct intel_gt*) ; 
 int /*<<< orphan*/  intel_gt_set_wedged (struct intel_gt*) ; 

__attribute__((used)) static bool switch_to_kernel_context_sync(struct intel_gt *gt)
{
	bool result = !intel_gt_is_wedged(gt);

	do {
		if (i915_gem_wait_for_idle(gt->i915,
					   I915_WAIT_LOCKED |
					   I915_WAIT_FOR_IDLE_BOOST,
					   I915_GEM_IDLE_TIMEOUT) == -ETIME) {
			/* XXX hide warning from gem_eio */
			if (i915_modparams.reset) {
				dev_err(gt->i915->drm.dev,
					"Failed to idle engines, declaring wedged!\n");
				GEM_TRACE_DUMP();
			}

			/*
			 * Forcibly cancel outstanding work and leave
			 * the gpu quiet.
			 */
			intel_gt_set_wedged(gt);
			result = false;
		}
	} while (i915_retire_requests(gt->i915) && result);

	if (intel_gt_pm_wait_for_idle(gt))
		result = false;

	return result;
}