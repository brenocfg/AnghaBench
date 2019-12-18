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
typedef  int /*<<< orphan*/  u32 ;
struct sun8i_hdmi_phy {TYPE_1__* variant; int /*<<< orphan*/  clk_phy; int /*<<< orphan*/  regs; } ;
struct dw_hdmi {int dummy; } ;
struct drm_display_mode {int flags; int crtc_clock; } ;
struct TYPE_2__ {int (* phy_config ) (struct dw_hdmi*,struct sun8i_hdmi_phy*,int) ;scalar_t__ has_phy_clk; } ;

/* Variables and functions */
 int DRM_MODE_FLAG_NHSYNC ; 
 int DRM_MODE_FLAG_NVSYNC ; 
 int /*<<< orphan*/  SUN8I_HDMI_PHY_DBG_CTRL_POL_MASK ; 
 int /*<<< orphan*/  SUN8I_HDMI_PHY_DBG_CTRL_POL_NHSYNC ; 
 int /*<<< orphan*/  SUN8I_HDMI_PHY_DBG_CTRL_POL_NVSYNC ; 
 int /*<<< orphan*/  SUN8I_HDMI_PHY_DBG_CTRL_REG ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct dw_hdmi*,struct sun8i_hdmi_phy*,int) ; 

__attribute__((used)) static int sun8i_hdmi_phy_config(struct dw_hdmi *hdmi, void *data,
				 struct drm_display_mode *mode)
{
	struct sun8i_hdmi_phy *phy = (struct sun8i_hdmi_phy *)data;
	u32 val = 0;

	if (mode->flags & DRM_MODE_FLAG_NHSYNC)
		val |= SUN8I_HDMI_PHY_DBG_CTRL_POL_NHSYNC;

	if (mode->flags & DRM_MODE_FLAG_NVSYNC)
		val |= SUN8I_HDMI_PHY_DBG_CTRL_POL_NVSYNC;

	regmap_update_bits(phy->regs, SUN8I_HDMI_PHY_DBG_CTRL_REG,
			   SUN8I_HDMI_PHY_DBG_CTRL_POL_MASK, val);

	if (phy->variant->has_phy_clk)
		clk_set_rate(phy->clk_phy, mode->crtc_clock * 1000);

	return phy->variant->phy_config(hdmi, phy, mode->crtc_clock * 1000);
}