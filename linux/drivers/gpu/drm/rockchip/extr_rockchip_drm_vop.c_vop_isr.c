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
typedef  int uint32_t ;
struct drm_crtc {int dummy; } ;
struct vop {int /*<<< orphan*/  dev; int /*<<< orphan*/  line_flag_completion; int /*<<< orphan*/  dsp_hold_completion; int /*<<< orphan*/  irq_lock; struct drm_crtc crtc; } ;
typedef  int irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR_RATELIMITED (int /*<<< orphan*/ ,char*) ; 
 int DSP_HOLD_VALID_INTR ; 
 int FS_INTR ; 
 int /*<<< orphan*/  INTR_MASK ; 
 int IRQ_HANDLED ; 
 int IRQ_NONE ; 
 int LINE_FLAG_INTR ; 
 int VOP_INTR_GET_TYPE (struct vop*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOP_INTR_SET_TYPE (struct vop*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  clear ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_crtc_handle_vblank (struct drm_crtc*) ; 
 int /*<<< orphan*/  pm_runtime_get_if_in_use (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  status ; 
 int /*<<< orphan*/  vop_core_clks_disable (struct vop*) ; 
 scalar_t__ vop_core_clks_enable (struct vop*) ; 
 int /*<<< orphan*/  vop_handle_vblank (struct vop*) ; 

__attribute__((used)) static irqreturn_t vop_isr(int irq, void *data)
{
	struct vop *vop = data;
	struct drm_crtc *crtc = &vop->crtc;
	uint32_t active_irqs;
	int ret = IRQ_NONE;

	/*
	 * The irq is shared with the iommu. If the runtime-pm state of the
	 * vop-device is disabled the irq has to be targeted at the iommu.
	 */
	if (!pm_runtime_get_if_in_use(vop->dev))
		return IRQ_NONE;

	if (vop_core_clks_enable(vop)) {
		DRM_DEV_ERROR_RATELIMITED(vop->dev, "couldn't enable clocks\n");
		goto out;
	}

	/*
	 * interrupt register has interrupt status, enable and clear bits, we
	 * must hold irq_lock to avoid a race with enable/disable_vblank().
	*/
	spin_lock(&vop->irq_lock);

	active_irqs = VOP_INTR_GET_TYPE(vop, status, INTR_MASK);
	/* Clear all active interrupt sources */
	if (active_irqs)
		VOP_INTR_SET_TYPE(vop, clear, active_irqs, 1);

	spin_unlock(&vop->irq_lock);

	/* This is expected for vop iommu irqs, since the irq is shared */
	if (!active_irqs)
		goto out_disable;

	if (active_irqs & DSP_HOLD_VALID_INTR) {
		complete(&vop->dsp_hold_completion);
		active_irqs &= ~DSP_HOLD_VALID_INTR;
		ret = IRQ_HANDLED;
	}

	if (active_irqs & LINE_FLAG_INTR) {
		complete(&vop->line_flag_completion);
		active_irqs &= ~LINE_FLAG_INTR;
		ret = IRQ_HANDLED;
	}

	if (active_irqs & FS_INTR) {
		drm_crtc_handle_vblank(crtc);
		vop_handle_vblank(vop);
		active_irqs &= ~FS_INTR;
		ret = IRQ_HANDLED;
	}

	/* Unhandled irqs are spurious. */
	if (active_irqs)
		DRM_DEV_ERROR(vop->dev, "Unknown VOP IRQs: %#02x\n",
			      active_irqs);

out_disable:
	vop_core_clks_disable(vop);
out:
	pm_runtime_put(vop->dev);
	return ret;
}