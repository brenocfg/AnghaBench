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
struct TYPE_2__ {int enabled; } ;
struct intel_guc {TYPE_1__ interrupts; } ;
struct intel_gt {int /*<<< orphan*/  i915; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  uncore; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN11_GUC_SG_INTR_ENABLE ; 
 int /*<<< orphan*/  GEN11_GUC_SG_INTR_MASK ; 
 int /*<<< orphan*/  gen11_reset_guc_interrupts (struct intel_guc*) ; 
 struct intel_gt* guc_to_gt (struct intel_guc*) ; 
 int /*<<< orphan*/  intel_synchronize_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void gen11_disable_guc_interrupts(struct intel_guc *guc)
{
	struct intel_gt *gt = guc_to_gt(guc);

	spin_lock_irq(&gt->irq_lock);
	guc->interrupts.enabled = false;

	intel_uncore_write(gt->uncore, GEN11_GUC_SG_INTR_MASK, ~0);
	intel_uncore_write(gt->uncore, GEN11_GUC_SG_INTR_ENABLE, 0);

	spin_unlock_irq(&gt->irq_lock);
	intel_synchronize_irq(gt->i915);

	gen11_reset_guc_interrupts(guc);
}