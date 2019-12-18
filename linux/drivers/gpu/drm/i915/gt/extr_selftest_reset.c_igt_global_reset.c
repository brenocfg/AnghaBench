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
struct intel_gt {TYPE_1__* i915; } ;
typedef  int /*<<< orphan*/  intel_wakeref_t ;
struct TYPE_2__ {int /*<<< orphan*/  runtime_pm; int /*<<< orphan*/  gpu_error; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_ENGINES ; 
 int EINVAL ; 
 int EIO ; 
 unsigned int i915_reset_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  igt_global_reset_lock (struct intel_gt*) ; 
 int /*<<< orphan*/  igt_global_reset_unlock (struct intel_gt*) ; 
 scalar_t__ intel_gt_is_wedged (struct intel_gt*) ; 
 int /*<<< orphan*/  intel_gt_reset (struct intel_gt*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_runtime_pm_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int igt_global_reset(void *arg)
{
	struct intel_gt *gt = arg;
	unsigned int reset_count;
	intel_wakeref_t wakeref;
	int err = 0;

	/* Check that we can issue a global GPU reset */

	igt_global_reset_lock(gt);
	wakeref = intel_runtime_pm_get(&gt->i915->runtime_pm);

	reset_count = i915_reset_count(&gt->i915->gpu_error);

	intel_gt_reset(gt, ALL_ENGINES, NULL);

	if (i915_reset_count(&gt->i915->gpu_error) == reset_count) {
		pr_err("No GPU reset recorded!\n");
		err = -EINVAL;
	}

	intel_runtime_pm_put(&gt->i915->runtime_pm, wakeref);
	igt_global_reset_unlock(gt);

	if (intel_gt_is_wedged(gt))
		err = -EIO;

	return err;
}