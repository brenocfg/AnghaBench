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
typedef  int u8 ;
struct hdmi_vmode {int mpixelclock; scalar_t__ mdataenablepolarity; } ;
struct TYPE_2__ {scalar_t__ hdcp_enable; struct hdmi_vmode video_mode; } ;
struct dw_hdmi {int vic; scalar_t__ sink_is_hdmi; TYPE_1__ hdmi_data; int /*<<< orphan*/  dev; } ;
struct drm_display_mode {int clock; int flags; unsigned int vdisplay; int vtotal; int vsync_start; int vsync_end; int hdisplay; int htotal; int hsync_start; int hsync_end; } ;

/* Variables and functions */
 int DRM_MODE_FLAG_INTERLACE ; 
 int DRM_MODE_FLAG_PHSYNC ; 
 int DRM_MODE_FLAG_PVSYNC ; 
 int /*<<< orphan*/  HDMI_FC_HSYNCINDELAY0 ; 
 int /*<<< orphan*/  HDMI_FC_HSYNCINDELAY1 ; 
 int /*<<< orphan*/  HDMI_FC_HSYNCINWIDTH0 ; 
 int /*<<< orphan*/  HDMI_FC_HSYNCINWIDTH1 ; 
 int /*<<< orphan*/  HDMI_FC_INHACTV0 ; 
 int /*<<< orphan*/  HDMI_FC_INHACTV1 ; 
 int /*<<< orphan*/  HDMI_FC_INHBLANK0 ; 
 int /*<<< orphan*/  HDMI_FC_INHBLANK1 ; 
 int /*<<< orphan*/  HDMI_FC_INVACTV0 ; 
 int /*<<< orphan*/  HDMI_FC_INVACTV1 ; 
 int /*<<< orphan*/  HDMI_FC_INVBLANK ; 
 int /*<<< orphan*/  HDMI_FC_INVIDCONF ; 
 int HDMI_FC_INVIDCONF_DE_IN_POLARITY_ACTIVE_HIGH ; 
 int HDMI_FC_INVIDCONF_DE_IN_POLARITY_ACTIVE_LOW ; 
 int HDMI_FC_INVIDCONF_DVI_MODEZ_DVI_MODE ; 
 int HDMI_FC_INVIDCONF_DVI_MODEZ_HDMI_MODE ; 
 int HDMI_FC_INVIDCONF_HDCP_KEEPOUT_ACTIVE ; 
 int HDMI_FC_INVIDCONF_HDCP_KEEPOUT_INACTIVE ; 
 int HDMI_FC_INVIDCONF_HSYNC_IN_POLARITY_ACTIVE_HIGH ; 
 int HDMI_FC_INVIDCONF_HSYNC_IN_POLARITY_ACTIVE_LOW ; 
 int HDMI_FC_INVIDCONF_IN_I_P_INTERLACED ; 
 int HDMI_FC_INVIDCONF_IN_I_P_PROGRESSIVE ; 
 int HDMI_FC_INVIDCONF_R_V_BLANK_IN_OSC_ACTIVE_HIGH ; 
 int HDMI_FC_INVIDCONF_R_V_BLANK_IN_OSC_ACTIVE_LOW ; 
 int HDMI_FC_INVIDCONF_VSYNC_IN_POLARITY_ACTIVE_HIGH ; 
 int HDMI_FC_INVIDCONF_VSYNC_IN_POLARITY_ACTIVE_LOW ; 
 int /*<<< orphan*/  HDMI_FC_VSYNCINDELAY ; 
 int /*<<< orphan*/  HDMI_FC_VSYNCINWIDTH ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  hdmi_writeb (struct dw_hdmi*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hdmi_av_composer(struct dw_hdmi *hdmi,
			     const struct drm_display_mode *mode)
{
	u8 inv_val;
	struct hdmi_vmode *vmode = &hdmi->hdmi_data.video_mode;
	int hblank, vblank, h_de_hs, v_de_vs, hsync_len, vsync_len;
	unsigned int vdisplay;

	vmode->mpixelclock = mode->clock * 1000;

	dev_dbg(hdmi->dev, "final pixclk = %d\n", vmode->mpixelclock);

	/* Set up HDMI_FC_INVIDCONF */
	inv_val = (hdmi->hdmi_data.hdcp_enable ?
		HDMI_FC_INVIDCONF_HDCP_KEEPOUT_ACTIVE :
		HDMI_FC_INVIDCONF_HDCP_KEEPOUT_INACTIVE);

	inv_val |= mode->flags & DRM_MODE_FLAG_PVSYNC ?
		HDMI_FC_INVIDCONF_VSYNC_IN_POLARITY_ACTIVE_HIGH :
		HDMI_FC_INVIDCONF_VSYNC_IN_POLARITY_ACTIVE_LOW;

	inv_val |= mode->flags & DRM_MODE_FLAG_PHSYNC ?
		HDMI_FC_INVIDCONF_HSYNC_IN_POLARITY_ACTIVE_HIGH :
		HDMI_FC_INVIDCONF_HSYNC_IN_POLARITY_ACTIVE_LOW;

	inv_val |= (vmode->mdataenablepolarity ?
		HDMI_FC_INVIDCONF_DE_IN_POLARITY_ACTIVE_HIGH :
		HDMI_FC_INVIDCONF_DE_IN_POLARITY_ACTIVE_LOW);

	if (hdmi->vic == 39)
		inv_val |= HDMI_FC_INVIDCONF_R_V_BLANK_IN_OSC_ACTIVE_HIGH;
	else
		inv_val |= mode->flags & DRM_MODE_FLAG_INTERLACE ?
			HDMI_FC_INVIDCONF_R_V_BLANK_IN_OSC_ACTIVE_HIGH :
			HDMI_FC_INVIDCONF_R_V_BLANK_IN_OSC_ACTIVE_LOW;

	inv_val |= mode->flags & DRM_MODE_FLAG_INTERLACE ?
		HDMI_FC_INVIDCONF_IN_I_P_INTERLACED :
		HDMI_FC_INVIDCONF_IN_I_P_PROGRESSIVE;

	inv_val |= hdmi->sink_is_hdmi ?
		HDMI_FC_INVIDCONF_DVI_MODEZ_HDMI_MODE :
		HDMI_FC_INVIDCONF_DVI_MODEZ_DVI_MODE;

	hdmi_writeb(hdmi, inv_val, HDMI_FC_INVIDCONF);

	vdisplay = mode->vdisplay;
	vblank = mode->vtotal - mode->vdisplay;
	v_de_vs = mode->vsync_start - mode->vdisplay;
	vsync_len = mode->vsync_end - mode->vsync_start;

	/*
	 * When we're setting an interlaced mode, we need
	 * to adjust the vertical timing to suit.
	 */
	if (mode->flags & DRM_MODE_FLAG_INTERLACE) {
		vdisplay /= 2;
		vblank /= 2;
		v_de_vs /= 2;
		vsync_len /= 2;
	}

	/* Set up horizontal active pixel width */
	hdmi_writeb(hdmi, mode->hdisplay >> 8, HDMI_FC_INHACTV1);
	hdmi_writeb(hdmi, mode->hdisplay, HDMI_FC_INHACTV0);

	/* Set up vertical active lines */
	hdmi_writeb(hdmi, vdisplay >> 8, HDMI_FC_INVACTV1);
	hdmi_writeb(hdmi, vdisplay, HDMI_FC_INVACTV0);

	/* Set up horizontal blanking pixel region width */
	hblank = mode->htotal - mode->hdisplay;
	hdmi_writeb(hdmi, hblank >> 8, HDMI_FC_INHBLANK1);
	hdmi_writeb(hdmi, hblank, HDMI_FC_INHBLANK0);

	/* Set up vertical blanking pixel region width */
	hdmi_writeb(hdmi, vblank, HDMI_FC_INVBLANK);

	/* Set up HSYNC active edge delay width (in pixel clks) */
	h_de_hs = mode->hsync_start - mode->hdisplay;
	hdmi_writeb(hdmi, h_de_hs >> 8, HDMI_FC_HSYNCINDELAY1);
	hdmi_writeb(hdmi, h_de_hs, HDMI_FC_HSYNCINDELAY0);

	/* Set up VSYNC active edge delay (in lines) */
	hdmi_writeb(hdmi, v_de_vs, HDMI_FC_VSYNCINDELAY);

	/* Set up HSYNC active pulse width (in pixel clks) */
	hsync_len = mode->hsync_end - mode->hsync_start;
	hdmi_writeb(hdmi, hsync_len >> 8, HDMI_FC_HSYNCINWIDTH1);
	hdmi_writeb(hdmi, hsync_len, HDMI_FC_HSYNCINWIDTH0);

	/* Set up VSYNC active edge delay (in lines) */
	hdmi_writeb(hdmi, vsync_len, HDMI_FC_VSYNCINWIDTH);
}