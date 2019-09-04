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
typedef  int /*<<< orphan*/  u32 ;
struct sun4i_hdmi {int /*<<< orphan*/  tmds_clk; scalar_t__ base; } ;
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  SUN4I_HDMI_VID_CTRL_ENABLE ; 
 scalar_t__ SUN4I_HDMI_VID_CTRL_REG ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct sun4i_hdmi* drm_encoder_to_sun4i_hdmi (struct drm_encoder*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void sun4i_hdmi_disable(struct drm_encoder *encoder)
{
	struct sun4i_hdmi *hdmi = drm_encoder_to_sun4i_hdmi(encoder);
	u32 val;

	DRM_DEBUG_DRIVER("Disabling the HDMI Output\n");

	val = readl(hdmi->base + SUN4I_HDMI_VID_CTRL_REG);
	val &= ~SUN4I_HDMI_VID_CTRL_ENABLE;
	writel(val, hdmi->base + SUN4I_HDMI_VID_CTRL_REG);

	clk_disable_unprepare(hdmi->tmds_clk);
}