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
typedef  int /*<<< orphan*/  u32 ;
struct intel_gt {int /*<<< orphan*/  pm_ier; int /*<<< orphan*/  irq_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  gen6_gt_pm_mask_irq (struct intel_gt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_pm_ier (struct intel_gt*) ; 

void gen6_gt_pm_disable_irq(struct intel_gt *gt, u32 disable_mask)
{
	lockdep_assert_held(&gt->irq_lock);

	gt->pm_ier &= ~disable_mask;
	gen6_gt_pm_mask_irq(gt, disable_mask);
	write_pm_ier(gt);
}