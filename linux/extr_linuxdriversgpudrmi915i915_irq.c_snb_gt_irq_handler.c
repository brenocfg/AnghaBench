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
 int /*<<< orphan*/  DRM_DEBUG (char*,int) ; 
 int GT_BLT_CS_ERROR_INTERRUPT ; 
 int GT_BLT_USER_INTERRUPT ; 
 int GT_BSD_CS_ERROR_INTERRUPT ; 
 int GT_BSD_USER_INTERRUPT ; 
 int GT_PARITY_ERROR (struct drm_i915_private*) ; 
 int GT_RENDER_CS_MASTER_ERROR_INTERRUPT ; 
 int GT_RENDER_USER_INTERRUPT ; 
 size_t RCS ; 
 size_t VCS ; 
 int /*<<< orphan*/  ivybridge_parity_error_irq_handler (struct drm_i915_private*,int) ; 
 int /*<<< orphan*/  notify_ring (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snb_gt_irq_handler(struct drm_i915_private *dev_priv,
			       u32 gt_iir)
{
	if (gt_iir & GT_RENDER_USER_INTERRUPT)
		notify_ring(dev_priv->engine[RCS]);
	if (gt_iir & GT_BSD_USER_INTERRUPT)
		notify_ring(dev_priv->engine[VCS]);
	if (gt_iir & GT_BLT_USER_INTERRUPT)
		notify_ring(dev_priv->engine[BCS]);

	if (gt_iir & (GT_BLT_CS_ERROR_INTERRUPT |
		      GT_BSD_CS_ERROR_INTERRUPT |
		      GT_RENDER_CS_MASTER_ERROR_INTERRUPT))
		DRM_DEBUG("Command parser error, gt_iir 0x%08x\n", gt_iir);

	if (gt_iir & GT_PARITY_ERROR(dev_priv))
		ivybridge_parity_error_irq_handler(dev_priv, gt_iir);
}