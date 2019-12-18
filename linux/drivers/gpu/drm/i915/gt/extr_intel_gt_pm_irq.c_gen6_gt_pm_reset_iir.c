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
struct intel_uncore {int dummy; } ;
struct intel_gt {int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  i915; struct intel_uncore* uncore; } ;
typedef  int /*<<< orphan*/  i915_reg_t ;

/* Variables and functions */
 int /*<<< orphan*/  GEN6_PMIIR ; 
 int /*<<< orphan*/  GEN8_GT_IIR (int) ; 
 int INTEL_GEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_posting_read (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_write (struct intel_uncore*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

void gen6_gt_pm_reset_iir(struct intel_gt *gt, u32 reset_mask)
{
	struct intel_uncore *uncore = gt->uncore;
	i915_reg_t reg = INTEL_GEN(gt->i915) >= 8 ? GEN8_GT_IIR(2) : GEN6_PMIIR;

	lockdep_assert_held(&gt->irq_lock);

	intel_uncore_write(uncore, reg, reset_mask);
	intel_uncore_write(uncore, reg, reset_mask);
	intel_uncore_posting_read(uncore, reg);
}