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
struct sun4i_tcon {int dclk_min_div; int dclk_max_div; int /*<<< orphan*/  dclk; } ;
struct sun4i_rgb {int /*<<< orphan*/  bridge; scalar_t__ panel; struct sun4i_tcon* tcon; } ;
struct drm_encoder {int dummy; } ;
struct drm_display_mode {int hsync_end; int hsync_start; int vsync_end; int vsync_start; int clock; int hdisplay; int htotal; int vdisplay; int vtotal; } ;
typedef  enum drm_mode_status { ____Placeholder_drm_mode_status } drm_mode_status ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int MODE_BAD_HVALUE ; 
 int MODE_BAD_VVALUE ; 
 int MODE_CLOCK_HIGH ; 
 int MODE_CLOCK_LOW ; 
 int MODE_HSYNC_NARROW ; 
 int MODE_HSYNC_WIDE ; 
 int MODE_H_ILLEGAL ; 
 int MODE_OK ; 
 int MODE_VSYNC_NARROW ; 
 int MODE_VSYNC_WIDE ; 
 int MODE_V_ILLEGAL ; 
 int SUN4I_RGB_DOTCLOCK_TOLERANCE_PER_MILLE ; 
 unsigned long long clk_round_rate (int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  do_div (unsigned long long,int) ; 
 struct sun4i_rgb* drm_encoder_to_sun4i_rgb (struct drm_encoder*) ; 

__attribute__((used)) static enum drm_mode_status sun4i_rgb_mode_valid(struct drm_encoder *crtc,
						 const struct drm_display_mode *mode)
{
	struct sun4i_rgb *rgb = drm_encoder_to_sun4i_rgb(crtc);
	struct sun4i_tcon *tcon = rgb->tcon;
	u32 hsync = mode->hsync_end - mode->hsync_start;
	u32 vsync = mode->vsync_end - mode->vsync_start;
	unsigned long long rate = mode->clock * 1000;
	unsigned long long lowest, highest;
	unsigned long long rounded_rate;

	DRM_DEBUG_DRIVER("Validating modes...\n");

	if (hsync < 1)
		return MODE_HSYNC_NARROW;

	if (hsync > 0x3ff)
		return MODE_HSYNC_WIDE;

	if ((mode->hdisplay < 1) || (mode->htotal < 1))
		return MODE_H_ILLEGAL;

	if ((mode->hdisplay > 0x7ff) || (mode->htotal > 0xfff))
		return MODE_BAD_HVALUE;

	DRM_DEBUG_DRIVER("Horizontal parameters OK\n");

	if (vsync < 1)
		return MODE_VSYNC_NARROW;

	if (vsync > 0x3ff)
		return MODE_VSYNC_WIDE;

	if ((mode->vdisplay < 1) || (mode->vtotal < 1))
		return MODE_V_ILLEGAL;

	if ((mode->vdisplay > 0x7ff) || (mode->vtotal > 0xfff))
		return MODE_BAD_VVALUE;

	DRM_DEBUG_DRIVER("Vertical parameters OK\n");

	/*
	 * TODO: We should use the struct display_timing if available
	 * and / or trying to stretch the timings within that
	 * tolerancy to take care of panels that we wouldn't be able
	 * to have a exact match for.
	 */
	if (rgb->panel) {
		DRM_DEBUG_DRIVER("RGB panel used, skipping clock rate checks");
		goto out;
	}

	/*
	 * That shouldn't ever happen unless something is really wrong, but it
	 * doesn't harm to check.
	 */
	if (!rgb->bridge)
		goto out;

	tcon->dclk_min_div = 6;
	tcon->dclk_max_div = 127;
	rounded_rate = clk_round_rate(tcon->dclk, rate);

	lowest = rate * (1000 - SUN4I_RGB_DOTCLOCK_TOLERANCE_PER_MILLE);
	do_div(lowest, 1000);
	if (rounded_rate < lowest)
		return MODE_CLOCK_LOW;

	highest = rate * (1000 + SUN4I_RGB_DOTCLOCK_TOLERANCE_PER_MILLE);
	do_div(highest, 1000);
	if (rounded_rate > highest)
		return MODE_CLOCK_HIGH;

out:
	DRM_DEBUG_DRIVER("Clock rate OK\n");

	return MODE_OK;
}