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
struct malidp_hw_device {int /*<<< orphan*/  pxlclk; } ;
struct malidp_drm {struct malidp_hw_device* dev; } ;
struct drm_display_mode {int crtc_clock; } ;
struct drm_crtc {int dummy; } ;
typedef  enum drm_mode_status { ____Placeholder_drm_mode_status } drm_mode_status ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,long) ; 
 int MODE_NOCLOCK ; 
 int MODE_OK ; 
 long clk_round_rate (int /*<<< orphan*/ ,long) ; 
 struct malidp_drm* crtc_to_malidp_device (struct drm_crtc*) ; 

__attribute__((used)) static enum drm_mode_status malidp_crtc_mode_valid(struct drm_crtc *crtc,
						   const struct drm_display_mode *mode)
{
	struct malidp_drm *malidp = crtc_to_malidp_device(crtc);
	struct malidp_hw_device *hwdev = malidp->dev;

	/*
	 * check that the hardware can drive the required clock rate,
	 * but skip the check if the clock is meant to be disabled (req_rate = 0)
	 */
	long rate, req_rate = mode->crtc_clock * 1000;

	if (req_rate) {
		rate = clk_round_rate(hwdev->pxlclk, req_rate);
		if (rate != req_rate) {
			DRM_DEBUG_DRIVER("pxlclk doesn't support %ld Hz\n",
					 req_rate);
			return MODE_NOCLOCK;
		}
	}

	return MODE_OK;
}