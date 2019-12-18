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
struct intel_gt {int pm_guc_events; int /*<<< orphan*/  irq_lock; TYPE_2__* i915; int /*<<< orphan*/  uncore; } ;
struct TYPE_4__ {int /*<<< orphan*/  runtime_pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  assert_rpm_wakelock_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen6_gt_pm_enable_irq (struct intel_gt*,int) ; 
 int /*<<< orphan*/  gen6_pm_iir (TYPE_2__*) ; 
 struct intel_gt* guc_to_gt (struct intel_guc*) ; 
 int intel_uncore_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void gen9_enable_guc_interrupts(struct intel_guc *guc)
{
	struct intel_gt *gt = guc_to_gt(guc);

	assert_rpm_wakelock_held(&gt->i915->runtime_pm);

	spin_lock_irq(&gt->irq_lock);
	if (!guc->interrupts.enabled) {
		WARN_ON_ONCE(intel_uncore_read(gt->uncore,
					       gen6_pm_iir(gt->i915)) &
			     gt->pm_guc_events);
		guc->interrupts.enabled = true;
		gen6_gt_pm_enable_irq(gt, gt->pm_guc_events);
	}
	spin_unlock_irq(&gt->irq_lock);
}