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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int enabled; } ;
struct intel_guc {TYPE_1__ interrupts; } ;
struct intel_gt {int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  uncore; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENGINE1_MASK ; 
 int /*<<< orphan*/  GEN11_GUC ; 
 int /*<<< orphan*/  GEN11_GUC_SG_INTR_ENABLE ; 
 int /*<<< orphan*/  GEN11_GUC_SG_INTR_MASK ; 
 int /*<<< orphan*/  GUC_INTR_GUC2HOST ; 
 int /*<<< orphan*/  REG_FIELD_PREP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen11_gt_reset_one_iir (struct intel_gt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct intel_gt* guc_to_gt (struct intel_guc*) ; 
 int /*<<< orphan*/  intel_uncore_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void gen11_enable_guc_interrupts(struct intel_guc *guc)
{
	struct intel_gt *gt = guc_to_gt(guc);

	spin_lock_irq(&gt->irq_lock);
	if (!guc->interrupts.enabled) {
		u32 events = REG_FIELD_PREP(ENGINE1_MASK, GUC_INTR_GUC2HOST);

		WARN_ON_ONCE(gen11_gt_reset_one_iir(gt, 0, GEN11_GUC));
		intel_uncore_write(gt->uncore, GEN11_GUC_SG_INTR_ENABLE, events);
		intel_uncore_write(gt->uncore, GEN11_GUC_SG_INTR_MASK, ~events);
		guc->interrupts.enabled = true;
	}
	spin_unlock_irq(&gt->irq_lock);
}