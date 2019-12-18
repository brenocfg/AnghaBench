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
struct TYPE_2__ {int /*<<< orphan*/  runtime_pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_ENGINES ; 
 int EIO ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  igt_global_reset_lock (struct intel_gt*) ; 
 int /*<<< orphan*/  igt_global_reset_unlock (struct intel_gt*) ; 
 scalar_t__ intel_gt_is_wedged (struct intel_gt*) ; 
 int /*<<< orphan*/  intel_gt_reset (struct intel_gt*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_gt_set_wedged (struct intel_gt*) ; 
 int /*<<< orphan*/  intel_runtime_pm_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int igt_wedged_reset(void *arg)
{
	struct intel_gt *gt = arg;
	intel_wakeref_t wakeref;

	/* Check that we can recover a wedged device with a GPU reset */

	igt_global_reset_lock(gt);
	wakeref = intel_runtime_pm_get(&gt->i915->runtime_pm);

	intel_gt_set_wedged(gt);

	GEM_BUG_ON(!intel_gt_is_wedged(gt));
	intel_gt_reset(gt, ALL_ENGINES, NULL);

	intel_runtime_pm_put(&gt->i915->runtime_pm, wakeref);
	igt_global_reset_unlock(gt);

	return intel_gt_is_wedged(gt) ? -EIO : 0;
}