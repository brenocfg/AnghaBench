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
typedef  int uint32_t ;
struct hdmi_bridge {struct hdmi* hdmi; } ;
struct hdmi {int pixclock; scalar_t__ hdmi_mode; } ;
struct drm_display_mode {int clock; int htotal; int hsync_start; int hdisplay; int vtotal; int vsync_start; int vdisplay; int flags; } ;
struct drm_bridge {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int,...) ; 
 int DRM_MODE_FLAG_INTERLACE ; 
 int DRM_MODE_FLAG_NHSYNC ; 
 int DRM_MODE_FLAG_NVSYNC ; 
 int HDMI_ACTIVE_HSYNC_END (int) ; 
 int HDMI_ACTIVE_HSYNC_START (int) ; 
 int HDMI_ACTIVE_VSYNC_END (int) ; 
 int HDMI_ACTIVE_VSYNC_START (int) ; 
 int HDMI_FRAME_CTRL_HSYNC_LOW ; 
 int HDMI_FRAME_CTRL_INTERLACED_EN ; 
 int HDMI_FRAME_CTRL_VSYNC_LOW ; 
 int HDMI_TOTAL_H_TOTAL (int) ; 
 int HDMI_TOTAL_V_TOTAL (int) ; 
 int HDMI_VSYNC_ACTIVE_F2_END (int) ; 
 int HDMI_VSYNC_ACTIVE_F2_START (int) ; 
 int HDMI_VSYNC_TOTAL_F2_V_TOTAL (int) ; 
 int /*<<< orphan*/  REG_HDMI_ACTIVE_HSYNC ; 
 int /*<<< orphan*/  REG_HDMI_ACTIVE_VSYNC ; 
 int /*<<< orphan*/  REG_HDMI_FRAME_CTRL ; 
 int /*<<< orphan*/  REG_HDMI_TOTAL ; 
 int /*<<< orphan*/  REG_HDMI_VSYNC_ACTIVE_F2 ; 
 int /*<<< orphan*/  REG_HDMI_VSYNC_TOTAL_F2 ; 
 int /*<<< orphan*/  hdmi_write (struct hdmi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msm_hdmi_audio_update (struct hdmi*) ; 
 struct hdmi_bridge* to_hdmi_bridge (struct drm_bridge*) ; 

__attribute__((used)) static void msm_hdmi_bridge_mode_set(struct drm_bridge *bridge,
		 const struct drm_display_mode *mode,
		 const struct drm_display_mode *adjusted_mode)
{
	struct hdmi_bridge *hdmi_bridge = to_hdmi_bridge(bridge);
	struct hdmi *hdmi = hdmi_bridge->hdmi;
	int hstart, hend, vstart, vend;
	uint32_t frame_ctrl;

	mode = adjusted_mode;

	hdmi->pixclock = mode->clock * 1000;

	hstart = mode->htotal - mode->hsync_start;
	hend   = mode->htotal - mode->hsync_start + mode->hdisplay;

	vstart = mode->vtotal - mode->vsync_start - 1;
	vend   = mode->vtotal - mode->vsync_start + mode->vdisplay - 1;

	DBG("htotal=%d, vtotal=%d, hstart=%d, hend=%d, vstart=%d, vend=%d",
			mode->htotal, mode->vtotal, hstart, hend, vstart, vend);

	hdmi_write(hdmi, REG_HDMI_TOTAL,
			HDMI_TOTAL_H_TOTAL(mode->htotal - 1) |
			HDMI_TOTAL_V_TOTAL(mode->vtotal - 1));

	hdmi_write(hdmi, REG_HDMI_ACTIVE_HSYNC,
			HDMI_ACTIVE_HSYNC_START(hstart) |
			HDMI_ACTIVE_HSYNC_END(hend));
	hdmi_write(hdmi, REG_HDMI_ACTIVE_VSYNC,
			HDMI_ACTIVE_VSYNC_START(vstart) |
			HDMI_ACTIVE_VSYNC_END(vend));

	if (mode->flags & DRM_MODE_FLAG_INTERLACE) {
		hdmi_write(hdmi, REG_HDMI_VSYNC_TOTAL_F2,
				HDMI_VSYNC_TOTAL_F2_V_TOTAL(mode->vtotal));
		hdmi_write(hdmi, REG_HDMI_VSYNC_ACTIVE_F2,
				HDMI_VSYNC_ACTIVE_F2_START(vstart + 1) |
				HDMI_VSYNC_ACTIVE_F2_END(vend + 1));
	} else {
		hdmi_write(hdmi, REG_HDMI_VSYNC_TOTAL_F2,
				HDMI_VSYNC_TOTAL_F2_V_TOTAL(0));
		hdmi_write(hdmi, REG_HDMI_VSYNC_ACTIVE_F2,
				HDMI_VSYNC_ACTIVE_F2_START(0) |
				HDMI_VSYNC_ACTIVE_F2_END(0));
	}

	frame_ctrl = 0;
	if (mode->flags & DRM_MODE_FLAG_NHSYNC)
		frame_ctrl |= HDMI_FRAME_CTRL_HSYNC_LOW;
	if (mode->flags & DRM_MODE_FLAG_NVSYNC)
		frame_ctrl |= HDMI_FRAME_CTRL_VSYNC_LOW;
	if (mode->flags & DRM_MODE_FLAG_INTERLACE)
		frame_ctrl |= HDMI_FRAME_CTRL_INTERLACED_EN;
	DBG("frame_ctrl=%08x", frame_ctrl);
	hdmi_write(hdmi, REG_HDMI_FRAME_CTRL, frame_ctrl);

	if (hdmi->hdmi_mode)
		msm_hdmi_audio_update(hdmi);
}