#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vop_win {int dummy; } ;
struct vop {int len; int is_enabled; int /*<<< orphan*/  dev; int /*<<< orphan*/  dclk; int /*<<< orphan*/  reg_lock; struct vop_win* win; TYPE_1__* data; scalar_t__ regs; int /*<<< orphan*/ * regsbak; int /*<<< orphan*/  drm_dev; } ;
struct drm_crtc_state {int /*<<< orphan*/  self_refresh_active; } ;
struct drm_crtc {int dummy; } ;
struct TYPE_2__ {int win_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  VOP_REG_SET (struct vop*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  common ; 
 int /*<<< orphan*/  drm_crtc_vblank_on (struct drm_crtc*) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 int rockchip_drm_dma_attach_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  standby ; 
 struct vop* to_vop (struct drm_crtc*) ; 
 int /*<<< orphan*/  vop_cfg_done (struct vop*) ; 
 int /*<<< orphan*/  vop_core_clks_disable (struct vop*) ; 
 int vop_core_clks_enable (struct vop*) ; 
 int /*<<< orphan*/  vop_win_disable (struct vop*,struct vop_win*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int vop_enable(struct drm_crtc *crtc, struct drm_crtc_state *old_state)
{
	struct vop *vop = to_vop(crtc);
	int ret, i;

	ret = pm_runtime_get_sync(vop->dev);
	if (ret < 0) {
		DRM_DEV_ERROR(vop->dev, "failed to get pm runtime: %d\n", ret);
		return ret;
	}

	ret = vop_core_clks_enable(vop);
	if (WARN_ON(ret < 0))
		goto err_put_pm_runtime;

	ret = clk_enable(vop->dclk);
	if (WARN_ON(ret < 0))
		goto err_disable_core;

	/*
	 * Slave iommu shares power, irq and clock with vop.  It was associated
	 * automatically with this master device via common driver code.
	 * Now that we have enabled the clock we attach it to the shared drm
	 * mapping.
	 */
	ret = rockchip_drm_dma_attach_device(vop->drm_dev, vop->dev);
	if (ret) {
		DRM_DEV_ERROR(vop->dev,
			      "failed to attach dma mapping, %d\n", ret);
		goto err_disable_dclk;
	}

	spin_lock(&vop->reg_lock);
	for (i = 0; i < vop->len; i += 4)
		writel_relaxed(vop->regsbak[i / 4], vop->regs + i);

	/*
	 * We need to make sure that all windows are disabled before we
	 * enable the crtc. Otherwise we might try to scan from a destroyed
	 * buffer later.
	 *
	 * In the case of enable-after-PSR, we don't need to worry about this
	 * case since the buffer is guaranteed to be valid and disabling the
	 * window will result in screen glitches on PSR exit.
	 */
	if (!old_state || !old_state->self_refresh_active) {
		for (i = 0; i < vop->data->win_size; i++) {
			struct vop_win *vop_win = &vop->win[i];

			vop_win_disable(vop, vop_win);
		}
	}
	spin_unlock(&vop->reg_lock);

	vop_cfg_done(vop);

	/*
	 * At here, vop clock & iommu is enable, R/W vop regs would be safe.
	 */
	vop->is_enabled = true;

	spin_lock(&vop->reg_lock);

	VOP_REG_SET(vop, common, standby, 1);

	spin_unlock(&vop->reg_lock);

	drm_crtc_vblank_on(crtc);

	return 0;

err_disable_dclk:
	clk_disable(vop->dclk);
err_disable_core:
	vop_core_clks_disable(vop);
err_put_pm_runtime:
	pm_runtime_put_sync(vop->dev);
	return ret;
}