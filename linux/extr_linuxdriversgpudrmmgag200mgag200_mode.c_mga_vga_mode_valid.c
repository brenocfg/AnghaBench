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
struct TYPE_3__ {int vram_size; } ;
struct mga_device {int unique_rev_id; scalar_t__ type; TYPE_1__ mc; } ;
struct drm_display_mode {int hdisplay; int vdisplay; int hsync_start; int hsync_end; int htotal; int crtc_hdisplay; int crtc_hsync_start; int crtc_hsync_end; int crtc_htotal; int crtc_vdisplay; int crtc_vsync_start; int crtc_vsync_end; int crtc_vtotal; } ;
struct drm_device {scalar_t__ dev_private; } ;
struct TYPE_4__ {int specified; int bpp; scalar_t__ bpp_specified; } ;
struct drm_connector {TYPE_2__ cmdline_mode; struct drm_device* dev; } ;
typedef  enum drm_mode_status { ____Placeholder_drm_mode_status } drm_mode_status ;

/* Variables and functions */
 scalar_t__ G200_EH ; 
 scalar_t__ G200_ER ; 
 scalar_t__ G200_EV ; 
 scalar_t__ G200_WB ; 
 scalar_t__ IS_G200_SE (struct mga_device*) ; 
 int MODE_BAD ; 
 int MODE_BANDWIDTH ; 
 int MODE_H_ILLEGAL ; 
 int MODE_OK ; 
 int MODE_VIRTUAL_X ; 
 int MODE_VIRTUAL_Y ; 
 int mga_vga_calculate_mode_bandwidth (struct drm_display_mode*,int) ; 

__attribute__((used)) static enum drm_mode_status mga_vga_mode_valid(struct drm_connector *connector,
				 struct drm_display_mode *mode)
{
	struct drm_device *dev = connector->dev;
	struct mga_device *mdev = (struct mga_device*)dev->dev_private;
	int bpp = 32;

	if (IS_G200_SE(mdev)) {
		if (mdev->unique_rev_id == 0x01) {
			if (mode->hdisplay > 1600)
				return MODE_VIRTUAL_X;
			if (mode->vdisplay > 1200)
				return MODE_VIRTUAL_Y;
			if (mga_vga_calculate_mode_bandwidth(mode, bpp)
				> (24400 * 1024))
				return MODE_BANDWIDTH;
		} else if (mdev->unique_rev_id == 0x02) {
			if (mode->hdisplay > 1920)
				return MODE_VIRTUAL_X;
			if (mode->vdisplay > 1200)
				return MODE_VIRTUAL_Y;
			if (mga_vga_calculate_mode_bandwidth(mode, bpp)
				> (30100 * 1024))
				return MODE_BANDWIDTH;
		} else {
			if (mga_vga_calculate_mode_bandwidth(mode, bpp)
				> (55000 * 1024))
				return MODE_BANDWIDTH;
		}
	} else if (mdev->type == G200_WB) {
		if (mode->hdisplay > 1280)
			return MODE_VIRTUAL_X;
		if (mode->vdisplay > 1024)
			return MODE_VIRTUAL_Y;
		if (mga_vga_calculate_mode_bandwidth(mode, bpp) >
		    (31877 * 1024))
			return MODE_BANDWIDTH;
	} else if (mdev->type == G200_EV &&
		(mga_vga_calculate_mode_bandwidth(mode, bpp)
			> (32700 * 1024))) {
		return MODE_BANDWIDTH;
	} else if (mdev->type == G200_EH &&
		(mga_vga_calculate_mode_bandwidth(mode, bpp)
			> (37500 * 1024))) {
		return MODE_BANDWIDTH;
	} else if (mdev->type == G200_ER &&
		(mga_vga_calculate_mode_bandwidth(mode,
			bpp) > (55000 * 1024))) {
		return MODE_BANDWIDTH;
	}

	if ((mode->hdisplay % 8) != 0 || (mode->hsync_start % 8) != 0 ||
	    (mode->hsync_end % 8) != 0 || (mode->htotal % 8) != 0) {
		return MODE_H_ILLEGAL;
	}

	if (mode->crtc_hdisplay > 2048 || mode->crtc_hsync_start > 4096 ||
	    mode->crtc_hsync_end > 4096 || mode->crtc_htotal > 4096 ||
	    mode->crtc_vdisplay > 2048 || mode->crtc_vsync_start > 4096 ||
	    mode->crtc_vsync_end > 4096 || mode->crtc_vtotal > 4096) {
		return MODE_BAD;
	}

	/* Validate the mode input by the user */
	if (connector->cmdline_mode.specified) {
		if (connector->cmdline_mode.bpp_specified)
			bpp = connector->cmdline_mode.bpp;
	}

	if ((mode->hdisplay * mode->vdisplay * (bpp/8)) > mdev->mc.vram_size) {
		if (connector->cmdline_mode.specified)
			connector->cmdline_mode.specified = false;
		return MODE_BAD;
	}

	return MODE_OK;
}