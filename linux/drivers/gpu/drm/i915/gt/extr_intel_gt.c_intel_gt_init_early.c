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
struct intel_gt {int /*<<< orphan*/  uc; int /*<<< orphan*/  closed_lock; int /*<<< orphan*/  closed_vma; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/ * uncore; struct drm_i915_private* i915; } ;
struct drm_i915_private {int /*<<< orphan*/  uncore; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_gt_init_hangcheck (struct intel_gt*) ; 
 int /*<<< orphan*/  intel_gt_init_reset (struct intel_gt*) ; 
 int /*<<< orphan*/  intel_gt_pm_init_early (struct intel_gt*) ; 
 int /*<<< orphan*/  intel_uc_init_early (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void intel_gt_init_early(struct intel_gt *gt, struct drm_i915_private *i915)
{
	gt->i915 = i915;
	gt->uncore = &i915->uncore;

	spin_lock_init(&gt->irq_lock);

	INIT_LIST_HEAD(&gt->closed_vma);
	spin_lock_init(&gt->closed_lock);

	intel_gt_init_hangcheck(gt);
	intel_gt_init_reset(gt);
	intel_gt_pm_init_early(gt);
	intel_uc_init_early(&gt->uc);
}