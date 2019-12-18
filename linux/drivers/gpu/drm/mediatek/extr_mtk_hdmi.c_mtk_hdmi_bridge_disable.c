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
struct mtk_hdmi {int enabled; int /*<<< orphan*/ * clk; int /*<<< orphan*/  phy; } ;
struct drm_bridge {int dummy; } ;

/* Variables and functions */
 size_t MTK_HDMI_CLK_HDMI_PIXEL ; 
 size_t MTK_HDMI_CLK_HDMI_PLL ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct mtk_hdmi* hdmi_ctx_from_bridge (struct drm_bridge*) ; 
 int /*<<< orphan*/  phy_power_off (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_hdmi_bridge_disable(struct drm_bridge *bridge)
{
	struct mtk_hdmi *hdmi = hdmi_ctx_from_bridge(bridge);

	if (!hdmi->enabled)
		return;

	phy_power_off(hdmi->phy);
	clk_disable_unprepare(hdmi->clk[MTK_HDMI_CLK_HDMI_PIXEL]);
	clk_disable_unprepare(hdmi->clk[MTK_HDMI_CLK_HDMI_PLL]);

	hdmi->enabled = false;
}