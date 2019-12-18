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
typedef  int /*<<< orphan*/  u32 ;
struct sun4i_hdmi {scalar_t__ base; scalar_t__ hdmi_monitor; int /*<<< orphan*/  tmds_clk; } ;
struct drm_encoder {TYPE_2__* crtc; } ;
struct drm_display_mode {int dummy; } ;
struct TYPE_4__ {TYPE_1__* state; } ;
struct TYPE_3__ {struct drm_display_mode adjusted_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  SUN4I_HDMI_PKT_AVI ; 
 scalar_t__ SUN4I_HDMI_PKT_CTRL_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUN4I_HDMI_PKT_CTRL_TYPE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUN4I_HDMI_PKT_END ; 
 int /*<<< orphan*/  SUN4I_HDMI_VID_CTRL_ENABLE ; 
 int /*<<< orphan*/  SUN4I_HDMI_VID_CTRL_HDMI_MODE ; 
 scalar_t__ SUN4I_HDMI_VID_CTRL_REG ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 struct sun4i_hdmi* drm_encoder_to_sun4i_hdmi (struct drm_encoder*) ; 
 int /*<<< orphan*/  sun4i_hdmi_setup_avi_infoframes (struct sun4i_hdmi*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void sun4i_hdmi_enable(struct drm_encoder *encoder)
{
	struct drm_display_mode *mode = &encoder->crtc->state->adjusted_mode;
	struct sun4i_hdmi *hdmi = drm_encoder_to_sun4i_hdmi(encoder);
	u32 val = 0;

	DRM_DEBUG_DRIVER("Enabling the HDMI Output\n");

	clk_prepare_enable(hdmi->tmds_clk);

	sun4i_hdmi_setup_avi_infoframes(hdmi, mode);
	val |= SUN4I_HDMI_PKT_CTRL_TYPE(0, SUN4I_HDMI_PKT_AVI);
	val |= SUN4I_HDMI_PKT_CTRL_TYPE(1, SUN4I_HDMI_PKT_END);
	writel(val, hdmi->base + SUN4I_HDMI_PKT_CTRL_REG(0));

	val = SUN4I_HDMI_VID_CTRL_ENABLE;
	if (hdmi->hdmi_monitor)
		val |= SUN4I_HDMI_VID_CTRL_HDMI_MODE;

	writel(val, hdmi->base + SUN4I_HDMI_VID_CTRL_REG);
}