#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct komeda_pipeline {int /*<<< orphan*/  id; int /*<<< orphan*/  pxlclk; } ;
struct komeda_dev {int dpmode; int /*<<< orphan*/  lock; int /*<<< orphan*/  aclk; TYPE_4__* funcs; } ;
struct drm_display_mode {int crtc_clock; } ;
struct TYPE_7__ {struct drm_display_mode adjusted_mode; } ;
struct komeda_crtc_state {TYPE_3__ base; } ;
struct TYPE_6__ {int /*<<< orphan*/  state; TYPE_1__* dev; } ;
struct komeda_crtc {TYPE_2__ base; struct komeda_pipeline* master; } ;
struct TYPE_8__ {int (* change_opmode ) (struct komeda_dev*,int) ;} ;
struct TYPE_5__ {struct komeda_dev* dev_private; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int KOMEDA_MODE_DUAL_DISP ; 
 scalar_t__ WARN_ON (int) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,int) ; 
 int komeda_crtc_get_aclk (struct komeda_crtc_state*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct komeda_dev*,int) ; 
 struct komeda_crtc_state* to_kcrtc_st (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
komeda_crtc_prepare(struct komeda_crtc *kcrtc)
{
	struct komeda_dev *mdev = kcrtc->base.dev->dev_private;
	struct komeda_pipeline *master = kcrtc->master;
	struct komeda_crtc_state *kcrtc_st = to_kcrtc_st(kcrtc->base.state);
	struct drm_display_mode *mode = &kcrtc_st->base.adjusted_mode;
	u32 new_mode;
	int err;

	mutex_lock(&mdev->lock);

	new_mode = mdev->dpmode | BIT(master->id);
	if (WARN_ON(new_mode == mdev->dpmode)) {
		err = 0;
		goto unlock;
	}

	err = mdev->funcs->change_opmode(mdev, new_mode);
	if (err) {
		DRM_ERROR("failed to change opmode: 0x%x -> 0x%x.\n,",
			  mdev->dpmode, new_mode);
		goto unlock;
	}

	mdev->dpmode = new_mode;
	/* Only need to enable aclk on single display mode, but no need to
	 * enable aclk it on dual display mode, since the dual mode always
	 * switch from single display mode, the aclk already enabled, no need
	 * to enable it again.
	 */
	if (new_mode != KOMEDA_MODE_DUAL_DISP) {
		err = clk_set_rate(mdev->aclk, komeda_crtc_get_aclk(kcrtc_st));
		if (err)
			DRM_ERROR("failed to set aclk.\n");
		err = clk_prepare_enable(mdev->aclk);
		if (err)
			DRM_ERROR("failed to enable aclk.\n");
	}

	err = clk_set_rate(master->pxlclk, mode->crtc_clock * 1000);
	if (err)
		DRM_ERROR("failed to set pxlclk for pipe%d\n", master->id);
	err = clk_prepare_enable(master->pxlclk);
	if (err)
		DRM_ERROR("failed to enable pxl clk for pipe%d.\n", master->id);

unlock:
	mutex_unlock(&mdev->lock);

	return err;
}