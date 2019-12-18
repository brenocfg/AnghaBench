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
struct intel_gt {int /*<<< orphan*/  i915; } ;

/* Variables and functions */
 int const GEN11_GU_MISC_GSE ; 
 int /*<<< orphan*/  intel_opregion_asle_intr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gen11_gu_misc_irq_handler(struct intel_gt *gt, const u32 iir)
{
	if (iir & GEN11_GU_MISC_GSE)
		intel_opregion_asle_intr(gt->i915);
}