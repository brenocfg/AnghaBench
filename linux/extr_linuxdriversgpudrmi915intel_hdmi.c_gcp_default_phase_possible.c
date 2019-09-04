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
struct drm_display_mode {unsigned int crtc_hdisplay; unsigned int crtc_htotal; unsigned int crtc_hblank_start; unsigned int crtc_hblank_end; unsigned int crtc_hsync_start; unsigned int crtc_hsync_end; int flags; } ;

/* Variables and functions */
 int DRM_MODE_FLAG_INTERLACE ; 

__attribute__((used)) static bool gcp_default_phase_possible(int pipe_bpp,
				       const struct drm_display_mode *mode)
{
	unsigned int pixels_per_group;

	switch (pipe_bpp) {
	case 30:
		/* 4 pixels in 5 clocks */
		pixels_per_group = 4;
		break;
	case 36:
		/* 2 pixels in 3 clocks */
		pixels_per_group = 2;
		break;
	case 48:
		/* 1 pixel in 2 clocks */
		pixels_per_group = 1;
		break;
	default:
		/* phase information not relevant for 8bpc */
		return false;
	}

	return mode->crtc_hdisplay % pixels_per_group == 0 &&
		mode->crtc_htotal % pixels_per_group == 0 &&
		mode->crtc_hblank_start % pixels_per_group == 0 &&
		mode->crtc_hblank_end % pixels_per_group == 0 &&
		mode->crtc_hsync_start % pixels_per_group == 0 &&
		mode->crtc_hsync_end % pixels_per_group == 0 &&
		((mode->flags & DRM_MODE_FLAG_INTERLACE) == 0 ||
		 mode->crtc_htotal/2 % pixels_per_group == 0);
}