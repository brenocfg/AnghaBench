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
struct ltdc_device {int /*<<< orphan*/  pixel_clk; } ;
struct drm_display_mode {int clock; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
struct drm_crtc {struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 scalar_t__ clk_set_rate (int /*<<< orphan*/ ,int) ; 
 struct ltdc_device* crtc_to_ltdc (struct drm_crtc*) ; 
 int pm_runtime_active (int /*<<< orphan*/ ) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ltdc_crtc_mode_fixup(struct drm_crtc *crtc,
				 const struct drm_display_mode *mode,
				 struct drm_display_mode *adjusted_mode)
{
	struct ltdc_device *ldev = crtc_to_ltdc(crtc);
	struct drm_device *ddev = crtc->dev;
	int rate = mode->clock * 1000;
	bool runtime_active;
	int ret;

	runtime_active = pm_runtime_active(ddev->dev);

	if (runtime_active)
		pm_runtime_put_sync(ddev->dev);

	if (clk_set_rate(ldev->pixel_clk, rate) < 0) {
		DRM_ERROR("Cannot set rate (%dHz) for pixel clk\n", rate);
		return false;
	}

	adjusted_mode->clock = clk_get_rate(ldev->pixel_clk) / 1000;

	if (runtime_active) {
		ret = pm_runtime_get_sync(ddev->dev);
		if (ret) {
			DRM_ERROR("Failed to fixup mode, cannot get sync\n");
			return false;
		}
	}

	DRM_DEBUG_DRIVER("requested clock %dkHz, adjusted clock %dkHz\n",
			 mode->clock, adjusted_mode->clock);

	return true;
}