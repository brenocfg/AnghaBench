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
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 scalar_t__ clk_set_rate (int /*<<< orphan*/ ,int) ; 
 struct ltdc_device* crtc_to_ltdc (struct drm_crtc*) ; 

__attribute__((used)) static bool ltdc_crtc_mode_fixup(struct drm_crtc *crtc,
				 const struct drm_display_mode *mode,
				 struct drm_display_mode *adjusted_mode)
{
	struct ltdc_device *ldev = crtc_to_ltdc(crtc);
	int rate = mode->clock * 1000;

	/*
	 * TODO clk_round_rate() does not work yet. When ready, it can
	 * be used instead of clk_set_rate() then clk_get_rate().
	 */

	clk_disable(ldev->pixel_clk);
	if (clk_set_rate(ldev->pixel_clk, rate) < 0) {
		DRM_ERROR("Cannot set rate (%dHz) for pixel clk\n", rate);
		return false;
	}
	clk_enable(ldev->pixel_clk);

	adjusted_mode->clock = clk_get_rate(ldev->pixel_clk) / 1000;

	return true;
}