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
struct intel_gt {int /*<<< orphan*/  i915; int /*<<< orphan*/ ** engine_class; } ;

/* Variables and functions */
 size_t COPY_ENGINE_CLASS ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,int) ; 
 int GT_BLT_CS_ERROR_INTERRUPT ; 
 int GT_BLT_USER_INTERRUPT ; 
 int GT_BSD_CS_ERROR_INTERRUPT ; 
 int GT_BSD_USER_INTERRUPT ; 
 int GT_PARITY_ERROR (int /*<<< orphan*/ ) ; 
 int GT_RENDER_CS_MASTER_ERROR_INTERRUPT ; 
 int GT_RENDER_USER_INTERRUPT ; 
 size_t RENDER_CLASS ; 
 size_t VIDEO_DECODE_CLASS ; 
 int /*<<< orphan*/  gen7_parity_error_irq_handler (struct intel_gt*,int) ; 
 int /*<<< orphan*/  intel_engine_breadcrumbs_irq (int /*<<< orphan*/ ) ; 

void gen6_gt_irq_handler(struct intel_gt *gt, u32 gt_iir)
{
	if (gt_iir & GT_RENDER_USER_INTERRUPT)
		intel_engine_breadcrumbs_irq(gt->engine_class[RENDER_CLASS][0]);
	if (gt_iir & GT_BSD_USER_INTERRUPT)
		intel_engine_breadcrumbs_irq(gt->engine_class[VIDEO_DECODE_CLASS][0]);
	if (gt_iir & GT_BLT_USER_INTERRUPT)
		intel_engine_breadcrumbs_irq(gt->engine_class[COPY_ENGINE_CLASS][0]);

	if (gt_iir & (GT_BLT_CS_ERROR_INTERRUPT |
		      GT_BSD_CS_ERROR_INTERRUPT |
		      GT_RENDER_CS_MASTER_ERROR_INTERRUPT))
		DRM_DEBUG("Command parser error, gt_iir 0x%08x\n", gt_iir);

	if (gt_iir & GT_PARITY_ERROR(gt->i915))
		gen7_parity_error_irq_handler(gt, gt_iir);
}