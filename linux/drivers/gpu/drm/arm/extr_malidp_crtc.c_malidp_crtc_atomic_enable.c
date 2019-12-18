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
struct videomode {int dummy; } ;
struct malidp_hw_device {TYPE_3__* hw; int /*<<< orphan*/  pxlclk; } ;
struct malidp_drm {struct malidp_hw_device* dev; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {TYPE_2__* state; TYPE_1__* dev; } ;
struct TYPE_8__ {int crtc_clock; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* leave_config_mode ) (struct malidp_hw_device*) ;int /*<<< orphan*/  (* modeset ) (struct malidp_hw_device*,struct videomode*) ;} ;
struct TYPE_6__ {TYPE_4__ adjusted_mode; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,int) ; 
 struct malidp_drm* crtc_to_malidp_device (struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_crtc_vblank_on (struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_display_mode_to_videomode (TYPE_4__*,struct videomode*) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct malidp_hw_device*,struct videomode*) ; 
 int /*<<< orphan*/  stub2 (struct malidp_hw_device*) ; 

__attribute__((used)) static void malidp_crtc_atomic_enable(struct drm_crtc *crtc,
				      struct drm_crtc_state *old_state)
{
	struct malidp_drm *malidp = crtc_to_malidp_device(crtc);
	struct malidp_hw_device *hwdev = malidp->dev;
	struct videomode vm;
	int err = pm_runtime_get_sync(crtc->dev->dev);

	if (err < 0) {
		DRM_DEBUG_DRIVER("Failed to enable runtime power management: %d\n", err);
		return;
	}

	drm_display_mode_to_videomode(&crtc->state->adjusted_mode, &vm);
	clk_prepare_enable(hwdev->pxlclk);

	/* We rely on firmware to set mclk to a sensible level. */
	clk_set_rate(hwdev->pxlclk, crtc->state->adjusted_mode.crtc_clock * 1000);

	hwdev->hw->modeset(hwdev, &vm);
	hwdev->hw->leave_config_mode(hwdev);
	drm_crtc_vblank_on(crtc);
}