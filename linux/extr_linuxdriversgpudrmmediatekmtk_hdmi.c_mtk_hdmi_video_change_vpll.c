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
typedef  unsigned long u32 ;
struct mtk_hdmi {int /*<<< orphan*/  dev; int /*<<< orphan*/ * clk; } ;

/* Variables and functions */
 scalar_t__ DIV_ROUND_CLOSEST (unsigned long,int) ; 
 size_t MTK_HDMI_CLK_HDMI_PLL ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned long,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  mtk_hdmi_hw_config_sys (struct mtk_hdmi*) ; 
 int /*<<< orphan*/  mtk_hdmi_hw_set_deep_color_mode (struct mtk_hdmi*) ; 

__attribute__((used)) static int mtk_hdmi_video_change_vpll(struct mtk_hdmi *hdmi, u32 clock)
{
	unsigned long rate;
	int ret;

	/* The DPI driver already should have set TVDPLL to the correct rate */
	ret = clk_set_rate(hdmi->clk[MTK_HDMI_CLK_HDMI_PLL], clock);
	if (ret) {
		dev_err(hdmi->dev, "Failed to set PLL to %u Hz: %d\n", clock,
			ret);
		return ret;
	}

	rate = clk_get_rate(hdmi->clk[MTK_HDMI_CLK_HDMI_PLL]);

	if (DIV_ROUND_CLOSEST(rate, 1000) != DIV_ROUND_CLOSEST(clock, 1000))
		dev_warn(hdmi->dev, "Want PLL %u Hz, got %lu Hz\n", clock,
			 rate);
	else
		dev_dbg(hdmi->dev, "Want PLL %u Hz, got %lu Hz\n", clock, rate);

	mtk_hdmi_hw_config_sys(hdmi);
	mtk_hdmi_hw_set_deep_color_mode(hdmi);
	return 0;
}