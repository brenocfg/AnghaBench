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
struct drm_i915_private {int /*<<< orphan*/  irq_lock; } ;

/* Variables and functions */
 int const GEN11_GT_DW_IRQ (unsigned int) ; 
 int /*<<< orphan*/  gen11_gt_bank_handler (struct drm_i915_private* const,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
gen11_gt_irq_handler(struct drm_i915_private * const i915,
		     const u32 master_ctl)
{
	unsigned int bank;

	spin_lock(&i915->irq_lock);

	for (bank = 0; bank < 2; bank++) {
		if (master_ctl & GEN11_GT_DW_IRQ(bank))
			gen11_gt_bank_handler(i915, bank);
	}

	spin_unlock(&i915->irq_lock);
}