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
struct dss_device {int /*<<< orphan*/  syscon_pll_ctrl_offset; int /*<<< orphan*/  syscon_pll_ctrl; } ;
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;
typedef  enum dss_clk_source { ____Placeholder_dss_clk_source } dss_clk_source ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*) ; 
#define  DSS_CLK_SRC_HDMI_PLL 135 
#define  DSS_CLK_SRC_PLL1_1 134 
#define  DSS_CLK_SRC_PLL1_3 133 
#define  DSS_CLK_SRC_PLL2_1 132 
#define  DSS_CLK_SRC_PLL2_3 131 
 int EINVAL ; 
#define  OMAP_DSS_CHANNEL_LCD 130 
#define  OMAP_DSS_CHANNEL_LCD2 129 
#define  OMAP_DSS_CHANNEL_LCD3 128 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int) ; 

__attribute__((used)) static int dss_ctrl_pll_set_control_mux(struct dss_device *dss,
					enum dss_clk_source clk_src,
					enum omap_channel channel)
{
	unsigned int shift, val;

	if (!dss->syscon_pll_ctrl)
		return -EINVAL;

	switch (channel) {
	case OMAP_DSS_CHANNEL_LCD:
		shift = 3;

		switch (clk_src) {
		case DSS_CLK_SRC_PLL1_1:
			val = 0; break;
		case DSS_CLK_SRC_HDMI_PLL:
			val = 1; break;
		default:
			DSSERR("error in PLL mux config for LCD\n");
			return -EINVAL;
		}

		break;
	case OMAP_DSS_CHANNEL_LCD2:
		shift = 5;

		switch (clk_src) {
		case DSS_CLK_SRC_PLL1_3:
			val = 0; break;
		case DSS_CLK_SRC_PLL2_3:
			val = 1; break;
		case DSS_CLK_SRC_HDMI_PLL:
			val = 2; break;
		default:
			DSSERR("error in PLL mux config for LCD2\n");
			return -EINVAL;
		}

		break;
	case OMAP_DSS_CHANNEL_LCD3:
		shift = 7;

		switch (clk_src) {
		case DSS_CLK_SRC_PLL2_1:
			val = 0; break;
		case DSS_CLK_SRC_PLL1_3:
			val = 1; break;
		case DSS_CLK_SRC_HDMI_PLL:
			val = 2; break;
		default:
			DSSERR("error in PLL mux config for LCD3\n");
			return -EINVAL;
		}

		break;
	default:
		DSSERR("error in PLL mux config\n");
		return -EINVAL;
	}

	regmap_update_bits(dss->syscon_pll_ctrl, dss->syscon_pll_ctrl_offset,
		0x3 << shift, val << shift);

	return 0;
}