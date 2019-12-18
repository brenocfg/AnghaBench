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
struct intel_guc {int dummy; } ;
struct intel_gt {int /*<<< orphan*/  irq_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN11_GUC ; 
 int /*<<< orphan*/  gen11_gt_reset_one_iir (struct intel_gt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct intel_gt* guc_to_gt (struct intel_guc*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void gen11_reset_guc_interrupts(struct intel_guc *guc)
{
	struct intel_gt *gt = guc_to_gt(guc);

	spin_lock_irq(&gt->irq_lock);
	gen11_gt_reset_one_iir(gt, 0, GEN11_GUC);
	spin_unlock_irq(&gt->irq_lock);
}