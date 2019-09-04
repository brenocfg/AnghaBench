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
struct oaktrail_timing_info {int hactive_hi; int hactive_lo; int vactive_hi; int vactive_lo; int hsync_offset_hi; int hsync_offset_lo; int hsync_pulse_width_hi; int hsync_pulse_width_lo; int hblank_hi; int hblank_lo; int vsync_offset_hi; int vsync_offset_lo; int vsync_pulse_width_hi; int vsync_pulse_width_lo; int vblank_hi; int vblank_lo; int pixel_clock; } ;
struct TYPE_2__ {struct oaktrail_timing_info DTD; } ;
struct drm_psb_private {TYPE_1__ gct_data; } ;
struct drm_display_mode {int hdisplay; int vdisplay; int hsync_start; int hsync_end; int htotal; int vsync_start; int vsync_end; int vtotal; int clock; int /*<<< orphan*/  type; } ;
struct drm_device {int /*<<< orphan*/  dev; struct drm_psb_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_TYPE_PREFERRED ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  drm_mode_set_crtcinfo (struct drm_display_mode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mode_set_name (struct drm_display_mode*) ; 
 struct drm_display_mode* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct drm_display_mode *tmd_vid_get_config_mode(struct drm_device *dev)
{
	struct drm_display_mode *mode;
	struct drm_psb_private *dev_priv = dev->dev_private;
	struct oaktrail_timing_info *ti = &dev_priv->gct_data.DTD;
	bool use_gct = false; /*Disable GCT for now*/

	mode = kzalloc(sizeof(*mode), GFP_KERNEL);
	if (!mode)
		return NULL;

	if (use_gct) {
		mode->hdisplay = (ti->hactive_hi << 8) | ti->hactive_lo;
		mode->vdisplay = (ti->vactive_hi << 8) | ti->vactive_lo;
		mode->hsync_start = mode->hdisplay + \
				((ti->hsync_offset_hi << 8) | \
				ti->hsync_offset_lo);
		mode->hsync_end = mode->hsync_start + \
				((ti->hsync_pulse_width_hi << 8) | \
				ti->hsync_pulse_width_lo);
		mode->htotal = mode->hdisplay + ((ti->hblank_hi << 8) | \
								ti->hblank_lo);
		mode->vsync_start = \
			mode->vdisplay + ((ti->vsync_offset_hi << 8) | \
						ti->vsync_offset_lo);
		mode->vsync_end = \
			mode->vsync_start + ((ti->vsync_pulse_width_hi << 8) | \
						ti->vsync_pulse_width_lo);
		mode->vtotal = mode->vdisplay + \
				((ti->vblank_hi << 8) | ti->vblank_lo);
		mode->clock = ti->pixel_clock * 10;

		dev_dbg(dev->dev, "hdisplay is %d\n", mode->hdisplay);
		dev_dbg(dev->dev, "vdisplay is %d\n", mode->vdisplay);
		dev_dbg(dev->dev, "HSS is %d\n", mode->hsync_start);
		dev_dbg(dev->dev, "HSE is %d\n", mode->hsync_end);
		dev_dbg(dev->dev, "htotal is %d\n", mode->htotal);
		dev_dbg(dev->dev, "VSS is %d\n", mode->vsync_start);
		dev_dbg(dev->dev, "VSE is %d\n", mode->vsync_end);
		dev_dbg(dev->dev, "vtotal is %d\n", mode->vtotal);
		dev_dbg(dev->dev, "clock is %d\n", mode->clock);
	} else {
		mode->hdisplay = 480;
		mode->vdisplay = 854;
		mode->hsync_start = 487;
		mode->hsync_end = 490;
		mode->htotal = 499;
		mode->vsync_start = 861;
		mode->vsync_end = 865;
		mode->vtotal = 873;
		mode->clock = 33264;
	}

	drm_mode_set_name(mode);
	drm_mode_set_crtcinfo(mode, 0);

	mode->type |= DRM_MODE_TYPE_PREFERRED;

	return mode;
}