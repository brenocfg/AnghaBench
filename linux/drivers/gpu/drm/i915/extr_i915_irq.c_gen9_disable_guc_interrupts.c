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
struct TYPE_3__ {int enabled; } ;
struct intel_guc {TYPE_1__ interrupts; } ;
struct intel_gt {TYPE_2__* i915; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  pm_guc_events; } ;
struct TYPE_4__ {int /*<<< orphan*/  runtime_pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_rpm_wakelock_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen6_gt_pm_disable_irq (struct intel_gt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen9_reset_guc_interrupts (struct intel_guc*) ; 
 struct intel_gt* guc_to_gt (struct intel_guc*) ; 
 int /*<<< orphan*/  intel_synchronize_irq (TYPE_2__*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void gen9_disable_guc_interrupts(struct intel_guc *guc)
{
	struct intel_gt *gt = guc_to_gt(guc);

	assert_rpm_wakelock_held(&gt->i915->runtime_pm);

	spin_lock_irq(&gt->irq_lock);
	guc->interrupts.enabled = false;

	gen6_gt_pm_disable_irq(gt, gt->pm_guc_events);

	spin_unlock_irq(&gt->irq_lock);
	intel_synchronize_irq(gt->i915);

	gen9_reset_guc_interrupts(guc);
}