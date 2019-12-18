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
struct TYPE_2__ {int dvi_settings; int video_mode; int video_mode_adv; int vso_begin; int vso_end; int vso_eline_present; scalar_t__ max_lncnt; scalar_t__ vso_eline; scalar_t__ vso_bline; scalar_t__ hso_end; scalar_t__ hso_begin; scalar_t__ vavon_bline; scalar_t__ vavon_eline; scalar_t__ havon_begin; scalar_t__ havon_end; scalar_t__ max_pxcnt; } ;
union meson_hdmi_venc_mode {TYPE_1__ encp; } ;
struct drm_display_mode {scalar_t__ vtotal; scalar_t__ vsync_start; scalar_t__ vsync_end; scalar_t__ hsync_start; scalar_t__ hsync_end; scalar_t__ vdisplay; scalar_t__ hdisplay; scalar_t__ htotal; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (union meson_hdmi_venc_mode*,int /*<<< orphan*/ ,int) ; 

void meson_venc_hdmi_get_dmt_vmode(const struct drm_display_mode *mode,
				   union meson_hdmi_venc_mode *dmt_mode)
{
	memset(dmt_mode, 0, sizeof(*dmt_mode));

	dmt_mode->encp.dvi_settings = 0x21;
	dmt_mode->encp.video_mode = 0x4040;
	dmt_mode->encp.video_mode_adv = 0x18;
	dmt_mode->encp.max_pxcnt = mode->htotal - 1;
	dmt_mode->encp.havon_begin = mode->htotal - mode->hsync_start;
	dmt_mode->encp.havon_end = dmt_mode->encp.havon_begin +
				   mode->hdisplay - 1;
	dmt_mode->encp.vavon_bline = mode->vtotal - mode->vsync_start;
	dmt_mode->encp.vavon_eline = dmt_mode->encp.vavon_bline +
				     mode->vdisplay - 1;
	dmt_mode->encp.hso_begin = 0;
	dmt_mode->encp.hso_end = mode->hsync_end - mode->hsync_start;
	dmt_mode->encp.vso_begin = 30;
	dmt_mode->encp.vso_end = 50;
	dmt_mode->encp.vso_bline = 0;
	dmt_mode->encp.vso_eline = mode->vsync_end - mode->vsync_start;
	dmt_mode->encp.vso_eline_present = true;
	dmt_mode->encp.max_lncnt = mode->vtotal - 1;
}