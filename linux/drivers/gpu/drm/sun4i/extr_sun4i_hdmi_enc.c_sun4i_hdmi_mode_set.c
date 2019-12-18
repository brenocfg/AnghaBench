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
typedef  int u32 ;
struct sun4i_hdmi {scalar_t__ base; TYPE_1__* variant; int /*<<< orphan*/  tmds_clk; int /*<<< orphan*/  mod_clk; } ;
struct drm_encoder {int dummy; } ;
struct drm_display_mode {int crtc_clock; unsigned int hdisplay; unsigned int vdisplay; unsigned int htotal; unsigned int hsync_start; unsigned int vtotal; unsigned int vsync_start; unsigned int hsync_end; unsigned int vsync_end; int flags; } ;
struct TYPE_2__ {int pad_ctrl1_init_val; } ;

/* Variables and functions */
 int DRM_MODE_FLAG_PHSYNC ; 
 int DRM_MODE_FLAG_PVSYNC ; 
 int SUN4I_HDMI_PAD_CTRL1_HALVE_CLK ; 
 scalar_t__ SUN4I_HDMI_PAD_CTRL1_REG ; 
 int SUN4I_HDMI_UNKNOWN_INPUT_SYNC ; 
 scalar_t__ SUN4I_HDMI_UNKNOWN_REG ; 
 scalar_t__ SUN4I_HDMI_VID_TIMING_ACT_REG ; 
 scalar_t__ SUN4I_HDMI_VID_TIMING_BP_REG ; 
 scalar_t__ SUN4I_HDMI_VID_TIMING_FP_REG ; 
 int SUN4I_HDMI_VID_TIMING_POL_HSYNC ; 
 scalar_t__ SUN4I_HDMI_VID_TIMING_POL_REG ; 
 int SUN4I_HDMI_VID_TIMING_POL_TX_CLK ; 
 int SUN4I_HDMI_VID_TIMING_POL_VSYNC ; 
 scalar_t__ SUN4I_HDMI_VID_TIMING_SPW_REG ; 
 int SUN4I_HDMI_VID_TIMING_X (unsigned int) ; 
 int SUN4I_HDMI_VID_TIMING_Y (unsigned int) ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,int) ; 
 struct sun4i_hdmi* drm_encoder_to_sun4i_hdmi (struct drm_encoder*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void sun4i_hdmi_mode_set(struct drm_encoder *encoder,
				struct drm_display_mode *mode,
				struct drm_display_mode *adjusted_mode)
{
	struct sun4i_hdmi *hdmi = drm_encoder_to_sun4i_hdmi(encoder);
	unsigned int x, y;
	u32 val;

	clk_set_rate(hdmi->mod_clk, mode->crtc_clock * 1000);
	clk_set_rate(hdmi->tmds_clk, mode->crtc_clock * 1000);

	/* Set input sync enable */
	writel(SUN4I_HDMI_UNKNOWN_INPUT_SYNC,
	       hdmi->base + SUN4I_HDMI_UNKNOWN_REG);

	/*
	 * Setup output pad (?) controls
	 *
	 * This is done here instead of at probe/bind time because
	 * the controller seems to toggle some of the bits on its own.
	 *
	 * We can't just initialize the register there, we need to
	 * protect the clock bits that have already been read out and
	 * cached by the clock framework.
	 */
	val = readl(hdmi->base + SUN4I_HDMI_PAD_CTRL1_REG);
	val &= SUN4I_HDMI_PAD_CTRL1_HALVE_CLK;
	val |= hdmi->variant->pad_ctrl1_init_val;
	writel(val, hdmi->base + SUN4I_HDMI_PAD_CTRL1_REG);
	val = readl(hdmi->base + SUN4I_HDMI_PAD_CTRL1_REG);

	/* Setup timing registers */
	writel(SUN4I_HDMI_VID_TIMING_X(mode->hdisplay) |
	       SUN4I_HDMI_VID_TIMING_Y(mode->vdisplay),
	       hdmi->base + SUN4I_HDMI_VID_TIMING_ACT_REG);

	x = mode->htotal - mode->hsync_start;
	y = mode->vtotal - mode->vsync_start;
	writel(SUN4I_HDMI_VID_TIMING_X(x) | SUN4I_HDMI_VID_TIMING_Y(y),
	       hdmi->base + SUN4I_HDMI_VID_TIMING_BP_REG);

	x = mode->hsync_start - mode->hdisplay;
	y = mode->vsync_start - mode->vdisplay;
	writel(SUN4I_HDMI_VID_TIMING_X(x) | SUN4I_HDMI_VID_TIMING_Y(y),
	       hdmi->base + SUN4I_HDMI_VID_TIMING_FP_REG);

	x = mode->hsync_end - mode->hsync_start;
	y = mode->vsync_end - mode->vsync_start;
	writel(SUN4I_HDMI_VID_TIMING_X(x) | SUN4I_HDMI_VID_TIMING_Y(y),
	       hdmi->base + SUN4I_HDMI_VID_TIMING_SPW_REG);

	val = SUN4I_HDMI_VID_TIMING_POL_TX_CLK;
	if (mode->flags & DRM_MODE_FLAG_PHSYNC)
		val |= SUN4I_HDMI_VID_TIMING_POL_HSYNC;

	if (mode->flags & DRM_MODE_FLAG_PVSYNC)
		val |= SUN4I_HDMI_VID_TIMING_POL_VSYNC;

	writel(val, hdmi->base + SUN4I_HDMI_VID_TIMING_POL_REG);
}