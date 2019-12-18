#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vop {int is_enabled; int /*<<< orphan*/  vop_lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  dclk; int /*<<< orphan*/  drm_dev; int /*<<< orphan*/  dsp_hold_completion; int /*<<< orphan*/  reg_lock; int /*<<< orphan*/  event; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {TYPE_2__* state; TYPE_1__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * event; int /*<<< orphan*/  active; scalar_t__ self_refresh_active; } ;
struct TYPE_3__ {int /*<<< orphan*/  event_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  VOP_REG_SET (struct vop*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  common ; 
 int /*<<< orphan*/  drm_crtc_send_vblank_event (struct drm_crtc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_crtc_vblank_off (struct drm_crtc*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rockchip_drm_dma_detach_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rockchip_drm_set_win_enabled (struct drm_crtc*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  standby ; 
 struct vop* to_vop (struct drm_crtc*) ; 
 int /*<<< orphan*/  vop_core_clks_disable (struct vop*) ; 
 int /*<<< orphan*/  vop_dsp_hold_valid_irq_disable (struct vop*) ; 
 int /*<<< orphan*/  vop_dsp_hold_valid_irq_enable (struct vop*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vop_crtc_atomic_disable(struct drm_crtc *crtc,
				    struct drm_crtc_state *old_state)
{
	struct vop *vop = to_vop(crtc);

	WARN_ON(vop->event);

	if (crtc->state->self_refresh_active)
		rockchip_drm_set_win_enabled(crtc, false);

	mutex_lock(&vop->vop_lock);

	drm_crtc_vblank_off(crtc);

	if (crtc->state->self_refresh_active)
		goto out;

	/*
	 * Vop standby will take effect at end of current frame,
	 * if dsp hold valid irq happen, it means standby complete.
	 *
	 * we must wait standby complete when we want to disable aclk,
	 * if not, memory bus maybe dead.
	 */
	reinit_completion(&vop->dsp_hold_completion);
	vop_dsp_hold_valid_irq_enable(vop);

	spin_lock(&vop->reg_lock);

	VOP_REG_SET(vop, common, standby, 1);

	spin_unlock(&vop->reg_lock);

	wait_for_completion(&vop->dsp_hold_completion);

	vop_dsp_hold_valid_irq_disable(vop);

	vop->is_enabled = false;

	/*
	 * vop standby complete, so iommu detach is safe.
	 */
	rockchip_drm_dma_detach_device(vop->drm_dev, vop->dev);

	clk_disable(vop->dclk);
	vop_core_clks_disable(vop);
	pm_runtime_put(vop->dev);

out:
	mutex_unlock(&vop->vop_lock);

	if (crtc->state->event && !crtc->state->active) {
		spin_lock_irq(&crtc->dev->event_lock);
		drm_crtc_send_vblank_event(crtc, crtc->state->event);
		spin_unlock_irq(&crtc->dev->event_lock);

		crtc->state->event = NULL;
	}
}