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
struct drm_i915_private {int /*<<< orphan*/ * engine; } ;

/* Variables and functions */
 size_t BCS ; 
 int GEN8_BCS_IRQ_SHIFT ; 
 int GEN8_GT_BCS_IRQ ; 
 int GEN8_GT_GUC_IRQ ; 
 int GEN8_GT_PM_IRQ ; 
 int GEN8_GT_RCS_IRQ ; 
 int GEN8_GT_VCS1_IRQ ; 
 int GEN8_GT_VCS2_IRQ ; 
 int GEN8_GT_VECS_IRQ ; 
 int GEN8_RCS_IRQ_SHIFT ; 
 int GEN8_VCS1_IRQ_SHIFT ; 
 int GEN8_VCS2_IRQ_SHIFT ; 
 int GEN8_VECS_IRQ_SHIFT ; 
 size_t RCS ; 
 size_t VCS ; 
 size_t VCS2 ; 
 size_t VECS ; 
 int /*<<< orphan*/  gen6_rps_irq_handler (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  gen8_cs_irq_handler (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gen9_guc_irq_handler (struct drm_i915_private*,int) ; 

__attribute__((used)) static void gen8_gt_irq_handler(struct drm_i915_private *i915,
				u32 master_ctl, u32 gt_iir[4])
{
	if (master_ctl & (GEN8_GT_RCS_IRQ | GEN8_GT_BCS_IRQ)) {
		gen8_cs_irq_handler(i915->engine[RCS],
				    gt_iir[0] >> GEN8_RCS_IRQ_SHIFT);
		gen8_cs_irq_handler(i915->engine[BCS],
				    gt_iir[0] >> GEN8_BCS_IRQ_SHIFT);
	}

	if (master_ctl & (GEN8_GT_VCS1_IRQ | GEN8_GT_VCS2_IRQ)) {
		gen8_cs_irq_handler(i915->engine[VCS],
				    gt_iir[1] >> GEN8_VCS1_IRQ_SHIFT);
		gen8_cs_irq_handler(i915->engine[VCS2],
				    gt_iir[1] >> GEN8_VCS2_IRQ_SHIFT);
	}

	if (master_ctl & GEN8_GT_VECS_IRQ) {
		gen8_cs_irq_handler(i915->engine[VECS],
				    gt_iir[3] >> GEN8_VECS_IRQ_SHIFT);
	}

	if (master_ctl & (GEN8_GT_PM_IRQ | GEN8_GT_GUC_IRQ)) {
		gen6_rps_irq_handler(i915, gt_iir[2]);
		gen9_guc_irq_handler(i915, gt_iir[2]);
	}
}