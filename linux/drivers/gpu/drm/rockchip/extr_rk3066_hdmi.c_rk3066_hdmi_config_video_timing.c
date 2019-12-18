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
struct TYPE_2__ {int vic; } ;
struct rk3066_hdmi {TYPE_1__ hdmi_data; } ;
struct drm_display_mode {int flags; int htotal; int hdisplay; int hsync_start; int hsync_end; int vtotal; int vdisplay; int vsync_start; int vsync_end; } ;

/* Variables and functions */
 int DRM_MODE_FLAG_INTERLACE ; 
 int DRM_MODE_FLAG_PHSYNC ; 
 int DRM_MODE_FLAG_PVSYNC ; 
 int /*<<< orphan*/  HDMI_EXT_HBLANK_H ; 
 int /*<<< orphan*/  HDMI_EXT_HBLANK_L ; 
 int /*<<< orphan*/  HDMI_EXT_HDELAY_H ; 
 int /*<<< orphan*/  HDMI_EXT_HDELAY_L ; 
 int /*<<< orphan*/  HDMI_EXT_HDURATION_H ; 
 int /*<<< orphan*/  HDMI_EXT_HDURATION_L ; 
 int /*<<< orphan*/  HDMI_EXT_HTOTAL_H ; 
 int /*<<< orphan*/  HDMI_EXT_HTOTAL_L ; 
 int /*<<< orphan*/  HDMI_EXT_VBLANK_L ; 
 int /*<<< orphan*/  HDMI_EXT_VDELAY ; 
 int /*<<< orphan*/  HDMI_EXT_VDURATION ; 
 int /*<<< orphan*/  HDMI_EXT_VIDEO_PARA ; 
 int HDMI_EXT_VIDEO_SET_EN ; 
 int /*<<< orphan*/  HDMI_EXT_VTOTAL_H ; 
 int /*<<< orphan*/  HDMI_EXT_VTOTAL_L ; 
 int HDMI_VIDEO_HSYNC_ACTIVE_HIGH ; 
 int HDMI_VIDEO_HSYNC_ACTIVE_LOW ; 
 int HDMI_VIDEO_MODE_INTERLACE ; 
 int HDMI_VIDEO_MODE_PROGRESSIVE ; 
 int HDMI_VIDEO_VSYNC_ACTIVE_HIGH ; 
 int HDMI_VIDEO_VSYNC_ACTIVE_LOW ; 
 int HDMI_VIDEO_VSYNC_OFFSET_SHIFT ; 
 int /*<<< orphan*/  hdmi_writeb (struct rk3066_hdmi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rk3066_hdmi_config_video_timing(struct rk3066_hdmi *hdmi,
					   struct drm_display_mode *mode)
{
	int value, vsync_offset;

	/* Set the details for the external polarity and interlace mode. */
	value = HDMI_EXT_VIDEO_SET_EN;
	value |= mode->flags & DRM_MODE_FLAG_PHSYNC ?
		 HDMI_VIDEO_HSYNC_ACTIVE_HIGH : HDMI_VIDEO_HSYNC_ACTIVE_LOW;
	value |= mode->flags & DRM_MODE_FLAG_PVSYNC ?
		 HDMI_VIDEO_VSYNC_ACTIVE_HIGH : HDMI_VIDEO_VSYNC_ACTIVE_LOW;
	value |= mode->flags & DRM_MODE_FLAG_INTERLACE ?
		 HDMI_VIDEO_MODE_INTERLACE : HDMI_VIDEO_MODE_PROGRESSIVE;

	if (hdmi->hdmi_data.vic == 2 || hdmi->hdmi_data.vic == 3)
		vsync_offset = 6;
	else
		vsync_offset = 0;

	value |= vsync_offset << HDMI_VIDEO_VSYNC_OFFSET_SHIFT;
	hdmi_writeb(hdmi, HDMI_EXT_VIDEO_PARA, value);

	/* Set the details for the external video timing. */
	value = mode->htotal;
	hdmi_writeb(hdmi, HDMI_EXT_HTOTAL_L, value & 0xFF);
	hdmi_writeb(hdmi, HDMI_EXT_HTOTAL_H, (value >> 8) & 0xFF);

	value = mode->htotal - mode->hdisplay;
	hdmi_writeb(hdmi, HDMI_EXT_HBLANK_L, value & 0xFF);
	hdmi_writeb(hdmi, HDMI_EXT_HBLANK_H, (value >> 8) & 0xFF);

	value = mode->htotal - mode->hsync_start;
	hdmi_writeb(hdmi, HDMI_EXT_HDELAY_L, value & 0xFF);
	hdmi_writeb(hdmi, HDMI_EXT_HDELAY_H, (value >> 8) & 0xFF);

	value = mode->hsync_end - mode->hsync_start;
	hdmi_writeb(hdmi, HDMI_EXT_HDURATION_L, value & 0xFF);
	hdmi_writeb(hdmi, HDMI_EXT_HDURATION_H, (value >> 8) & 0xFF);

	value = mode->vtotal;
	hdmi_writeb(hdmi, HDMI_EXT_VTOTAL_L, value & 0xFF);
	hdmi_writeb(hdmi, HDMI_EXT_VTOTAL_H, (value >> 8) & 0xFF);

	value = mode->vtotal - mode->vdisplay;
	hdmi_writeb(hdmi, HDMI_EXT_VBLANK_L, value & 0xFF);

	value = mode->vtotal - mode->vsync_start + vsync_offset;
	hdmi_writeb(hdmi, HDMI_EXT_VDELAY, value & 0xFF);

	value = mode->vsync_end - mode->vsync_start;
	hdmi_writeb(hdmi, HDMI_EXT_VDURATION, value & 0xFF);

	return 0;
}