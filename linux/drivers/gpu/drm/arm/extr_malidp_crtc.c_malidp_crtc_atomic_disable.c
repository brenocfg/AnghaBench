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
struct malidp_hw_device {int /*<<< orphan*/  pxlclk; TYPE_1__* hw; } ;
struct malidp_drm {struct malidp_hw_device* dev; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {TYPE_2__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* enter_config_mode ) (struct malidp_hw_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct malidp_drm* crtc_to_malidp_device (struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_atomic_helper_disable_planes_on_crtc (struct drm_crtc_state*,int) ; 
 int /*<<< orphan*/  drm_crtc_vblank_off (struct drm_crtc*) ; 
 int pm_runtime_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct malidp_hw_device*) ; 

__attribute__((used)) static void malidp_crtc_atomic_disable(struct drm_crtc *crtc,
				       struct drm_crtc_state *old_state)
{
	struct malidp_drm *malidp = crtc_to_malidp_device(crtc);
	struct malidp_hw_device *hwdev = malidp->dev;
	int err;

	/* always disable planes on the CRTC that is being turned off */
	drm_atomic_helper_disable_planes_on_crtc(old_state, false);

	drm_crtc_vblank_off(crtc);
	hwdev->hw->enter_config_mode(hwdev);

	clk_disable_unprepare(hwdev->pxlclk);

	err = pm_runtime_put(crtc->dev->dev);
	if (err < 0) {
		DRM_DEBUG_DRIVER("Failed to disable runtime power management: %d\n", err);
	}
}