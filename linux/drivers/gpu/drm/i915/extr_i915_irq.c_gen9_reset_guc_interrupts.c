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
struct intel_guc {int dummy; } ;
struct intel_gt {int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  pm_guc_events; TYPE_1__* i915; } ;
struct TYPE_2__ {int /*<<< orphan*/  runtime_pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_rpm_wakelock_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen6_gt_pm_reset_iir (struct intel_gt*,int /*<<< orphan*/ ) ; 
 struct intel_gt* guc_to_gt (struct intel_guc*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void gen9_reset_guc_interrupts(struct intel_guc *guc)
{
	struct intel_gt *gt = guc_to_gt(guc);

	assert_rpm_wakelock_held(&gt->i915->runtime_pm);

	spin_lock_irq(&gt->irq_lock);
	gen6_gt_pm_reset_iir(gt, gt->pm_guc_events);
	spin_unlock_irq(&gt->irq_lock);
}