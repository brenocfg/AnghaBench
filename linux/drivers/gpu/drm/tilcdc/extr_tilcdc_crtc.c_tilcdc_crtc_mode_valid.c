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
typedef  int uint32_t ;
struct tilcdc_drm_private {scalar_t__ max_pixelclock; int max_width; unsigned int max_bandwidth; } ;
struct drm_display_mode {int hdisplay; int vdisplay; scalar_t__ clock; int htotal; int hsync_end; int hsync_start; int vtotal; int vsync_end; int vsync_start; } ;
struct drm_crtc {TYPE_1__* dev; } ;
typedef  enum drm_mode_status { ____Placeholder_drm_mode_status } drm_mode_status ;
struct TYPE_2__ {struct tilcdc_drm_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,...) ; 
 int MODE_BAD ; 
 int MODE_BAD_WIDTH ; 
 int MODE_CLOCK_HIGH ; 
 int MODE_HBLANK_WIDE ; 
 int MODE_HSYNC_WIDE ; 
 int MODE_OK ; 
 int MODE_VBLANK_WIDE ; 
 int MODE_VIRTUAL_X ; 
 int MODE_VIRTUAL_Y ; 
 int MODE_VSYNC_WIDE ; 
 unsigned int drm_mode_vrefresh (struct drm_display_mode const*) ; 
 int tilcdc_crtc_max_width (struct drm_crtc*) ; 

__attribute__((used)) static enum drm_mode_status
tilcdc_crtc_mode_valid(struct drm_crtc *crtc,
		       const struct drm_display_mode *mode)
{
	struct tilcdc_drm_private *priv = crtc->dev->dev_private;
	unsigned int bandwidth;
	uint32_t hbp, hfp, hsw, vbp, vfp, vsw;

	/*
	 * check to see if the width is within the range that
	 * the LCD Controller physically supports
	 */
	if (mode->hdisplay > tilcdc_crtc_max_width(crtc))
		return MODE_VIRTUAL_X;

	/* width must be multiple of 16 */
	if (mode->hdisplay & 0xf)
		return MODE_VIRTUAL_X;

	if (mode->vdisplay > 2048)
		return MODE_VIRTUAL_Y;

	DBG("Processing mode %dx%d@%d with pixel clock %d",
		mode->hdisplay, mode->vdisplay,
		drm_mode_vrefresh(mode), mode->clock);

	hbp = mode->htotal - mode->hsync_end;
	hfp = mode->hsync_start - mode->hdisplay;
	hsw = mode->hsync_end - mode->hsync_start;
	vbp = mode->vtotal - mode->vsync_end;
	vfp = mode->vsync_start - mode->vdisplay;
	vsw = mode->vsync_end - mode->vsync_start;

	if ((hbp-1) & ~0x3ff) {
		DBG("Pruning mode: Horizontal Back Porch out of range");
		return MODE_HBLANK_WIDE;
	}

	if ((hfp-1) & ~0x3ff) {
		DBG("Pruning mode: Horizontal Front Porch out of range");
		return MODE_HBLANK_WIDE;
	}

	if ((hsw-1) & ~0x3ff) {
		DBG("Pruning mode: Horizontal Sync Width out of range");
		return MODE_HSYNC_WIDE;
	}

	if (vbp & ~0xff) {
		DBG("Pruning mode: Vertical Back Porch out of range");
		return MODE_VBLANK_WIDE;
	}

	if (vfp & ~0xff) {
		DBG("Pruning mode: Vertical Front Porch out of range");
		return MODE_VBLANK_WIDE;
	}

	if ((vsw-1) & ~0x3f) {
		DBG("Pruning mode: Vertical Sync Width out of range");
		return MODE_VSYNC_WIDE;
	}

	/*
	 * some devices have a maximum allowed pixel clock
	 * configured from the DT
	 */
	if (mode->clock > priv->max_pixelclock) {
		DBG("Pruning mode: pixel clock too high");
		return MODE_CLOCK_HIGH;
	}

	/*
	 * some devices further limit the max horizontal resolution
	 * configured from the DT
	 */
	if (mode->hdisplay > priv->max_width)
		return MODE_BAD_WIDTH;

	/* filter out modes that would require too much memory bandwidth: */
	bandwidth = mode->hdisplay * mode->vdisplay *
		drm_mode_vrefresh(mode);
	if (bandwidth > priv->max_bandwidth) {
		DBG("Pruning mode: exceeds defined bandwidth limit");
		return MODE_BAD;
	}

	return MODE_OK;
}