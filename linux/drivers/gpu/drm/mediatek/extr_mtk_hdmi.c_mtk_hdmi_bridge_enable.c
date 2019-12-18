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
struct mtk_hdmi {int enabled; int /*<<< orphan*/  mode; int /*<<< orphan*/  phy; int /*<<< orphan*/ * clk; } ;
struct drm_bridge {int dummy; } ;

/* Variables and functions */
 size_t MTK_HDMI_CLK_HDMI_PIXEL ; 
 size_t MTK_HDMI_CLK_HDMI_PLL ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 struct mtk_hdmi* hdmi_ctx_from_bridge (struct drm_bridge*) ; 
 int /*<<< orphan*/  mtk_hdmi_output_set_display_mode (struct mtk_hdmi*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtk_hdmi_send_infoframe (struct mtk_hdmi*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phy_power_on (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_hdmi_bridge_enable(struct drm_bridge *bridge)
{
	struct mtk_hdmi *hdmi = hdmi_ctx_from_bridge(bridge);

	mtk_hdmi_output_set_display_mode(hdmi, &hdmi->mode);
	clk_prepare_enable(hdmi->clk[MTK_HDMI_CLK_HDMI_PLL]);
	clk_prepare_enable(hdmi->clk[MTK_HDMI_CLK_HDMI_PIXEL]);
	phy_power_on(hdmi->phy);
	mtk_hdmi_send_infoframe(hdmi, &hdmi->mode);

	hdmi->enabled = true;
}