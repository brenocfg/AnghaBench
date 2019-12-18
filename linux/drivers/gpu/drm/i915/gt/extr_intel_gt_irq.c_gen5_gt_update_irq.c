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
typedef  int u32 ;
struct intel_gt {int gt_imr; int /*<<< orphan*/  uncore; int /*<<< orphan*/  irq_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  GTIMR ; 
 int /*<<< orphan*/  intel_uncore_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gen5_gt_update_irq(struct intel_gt *gt,
			       u32 interrupt_mask,
			       u32 enabled_irq_mask)
{
	lockdep_assert_held(&gt->irq_lock);

	GEM_BUG_ON(enabled_irq_mask & ~interrupt_mask);

	gt->gt_imr &= ~interrupt_mask;
	gt->gt_imr |= (~enabled_irq_mask & interrupt_mask);
	intel_uncore_write(gt->uncore, GTIMR, gt->gt_imr);
}