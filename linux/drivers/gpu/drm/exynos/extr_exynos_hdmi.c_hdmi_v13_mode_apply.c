#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* crtc; } ;
struct hdmi_context {TYPE_3__ encoder; } ;
struct drm_display_mode {int htotal; int hdisplay; int vtotal; int flags; int hsync_start; int hsync_end; int vsync_end; int vdisplay; int vsync_start; } ;
struct TYPE_5__ {TYPE_1__* state; } ;
struct TYPE_4__ {struct drm_display_mode mode; } ;

/* Variables and functions */
 int DRM_MODE_FLAG_INTERLACE ; 
 int DRM_MODE_FLAG_NHSYNC ; 
 int DRM_MODE_FLAG_NVSYNC ; 
 int /*<<< orphan*/  HDMI_H_BLANK_0 ; 
 int /*<<< orphan*/  HDMI_INT_PRO_MODE ; 
 int /*<<< orphan*/  HDMI_TG_HACT_ST_L ; 
 int /*<<< orphan*/  HDMI_TG_HACT_SZ_L ; 
 int /*<<< orphan*/  HDMI_TG_H_FSZ_L ; 
 int /*<<< orphan*/  HDMI_TG_VACT_ST2_L ; 
 int /*<<< orphan*/  HDMI_TG_VACT_ST_L ; 
 int /*<<< orphan*/  HDMI_TG_VACT_SZ_L ; 
 int /*<<< orphan*/  HDMI_TG_V_FSZ_L ; 
 int /*<<< orphan*/  HDMI_V13_H_SYNC_GEN_0 ; 
 int /*<<< orphan*/  HDMI_V13_H_V_LINE_0 ; 
 int /*<<< orphan*/  HDMI_V13_V_BLANK_0 ; 
 int /*<<< orphan*/  HDMI_V13_V_BLANK_F_0 ; 
 int /*<<< orphan*/  HDMI_V13_V_SYNC_GEN_1_0 ; 
 int /*<<< orphan*/  HDMI_V13_V_SYNC_GEN_2_0 ; 
 int /*<<< orphan*/  HDMI_V13_V_SYNC_GEN_3_0 ; 
 int /*<<< orphan*/  HDMI_VSYNC_POL ; 
 int /*<<< orphan*/  hdmi_reg_writev (struct hdmi_context*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void hdmi_v13_mode_apply(struct hdmi_context *hdata)
{
	struct drm_display_mode *m = &hdata->encoder.crtc->state->mode;
	unsigned int val;

	hdmi_reg_writev(hdata, HDMI_H_BLANK_0, 2, m->htotal - m->hdisplay);
	hdmi_reg_writev(hdata, HDMI_V13_H_V_LINE_0, 3,
			(m->htotal << 12) | m->vtotal);

	val = (m->flags & DRM_MODE_FLAG_NVSYNC) ? 1 : 0;
	hdmi_reg_writev(hdata, HDMI_VSYNC_POL, 1, val);

	val = (m->flags & DRM_MODE_FLAG_INTERLACE) ? 1 : 0;
	hdmi_reg_writev(hdata, HDMI_INT_PRO_MODE, 1, val);

	val = (m->hsync_start - m->hdisplay - 2);
	val |= ((m->hsync_end - m->hdisplay - 2) << 10);
	val |= ((m->flags & DRM_MODE_FLAG_NHSYNC) ? 1 : 0)<<20;
	hdmi_reg_writev(hdata, HDMI_V13_H_SYNC_GEN_0, 3, val);

	/*
	 * Quirk requirement for exynos HDMI IP design,
	 * 2 pixels less than the actual calculation for hsync_start
	 * and end.
	 */

	/* Following values & calculations differ for different type of modes */
	if (m->flags & DRM_MODE_FLAG_INTERLACE) {
		val = ((m->vsync_end - m->vdisplay) / 2);
		val |= ((m->vsync_start - m->vdisplay) / 2) << 12;
		hdmi_reg_writev(hdata, HDMI_V13_V_SYNC_GEN_1_0, 3, val);

		val = m->vtotal / 2;
		val |= ((m->vtotal - m->vdisplay) / 2) << 11;
		hdmi_reg_writev(hdata, HDMI_V13_V_BLANK_0, 3, val);

		val = (m->vtotal +
			((m->vsync_end - m->vsync_start) * 4) + 5) / 2;
		val |= m->vtotal << 11;
		hdmi_reg_writev(hdata, HDMI_V13_V_BLANK_F_0, 3, val);

		val = ((m->vtotal / 2) + 7);
		val |= ((m->vtotal / 2) + 2) << 12;
		hdmi_reg_writev(hdata, HDMI_V13_V_SYNC_GEN_2_0, 3, val);

		val = ((m->htotal / 2) + (m->hsync_start - m->hdisplay));
		val |= ((m->htotal / 2) +
			(m->hsync_start - m->hdisplay)) << 12;
		hdmi_reg_writev(hdata, HDMI_V13_V_SYNC_GEN_3_0, 3, val);

		hdmi_reg_writev(hdata, HDMI_TG_VACT_ST_L, 2,
				(m->vtotal - m->vdisplay) / 2);
		hdmi_reg_writev(hdata, HDMI_TG_VACT_SZ_L, 2, m->vdisplay / 2);

		hdmi_reg_writev(hdata, HDMI_TG_VACT_ST2_L, 2, 0x249);
	} else {
		val = m->vtotal;
		val |= (m->vtotal - m->vdisplay) << 11;
		hdmi_reg_writev(hdata, HDMI_V13_V_BLANK_0, 3, val);

		hdmi_reg_writev(hdata, HDMI_V13_V_BLANK_F_0, 3, 0);

		val = (m->vsync_end - m->vdisplay);
		val |= ((m->vsync_start - m->vdisplay) << 12);
		hdmi_reg_writev(hdata, HDMI_V13_V_SYNC_GEN_1_0, 3, val);

		hdmi_reg_writev(hdata, HDMI_V13_V_SYNC_GEN_2_0, 3, 0x1001);
		hdmi_reg_writev(hdata, HDMI_V13_V_SYNC_GEN_3_0, 3, 0x1001);
		hdmi_reg_writev(hdata, HDMI_TG_VACT_ST_L, 2,
				m->vtotal - m->vdisplay);
		hdmi_reg_writev(hdata, HDMI_TG_VACT_SZ_L, 2, m->vdisplay);
	}

	hdmi_reg_writev(hdata, HDMI_TG_H_FSZ_L, 2, m->htotal);
	hdmi_reg_writev(hdata, HDMI_TG_HACT_ST_L, 2, m->htotal - m->hdisplay);
	hdmi_reg_writev(hdata, HDMI_TG_HACT_SZ_L, 2, m->hdisplay);
	hdmi_reg_writev(hdata, HDMI_TG_V_FSZ_L, 2, m->vtotal);
}