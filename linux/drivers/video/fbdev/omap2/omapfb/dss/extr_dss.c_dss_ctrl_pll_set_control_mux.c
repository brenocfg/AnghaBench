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
typedef  enum omap_channel { ____Placeholder_omap_channel } omap_channel ;
typedef  enum dss_pll_id { ____Placeholder_dss_pll_id } dss_pll_id ;
struct TYPE_2__ {int /*<<< orphan*/  syscon_pll_ctrl_offset; int /*<<< orphan*/  syscon_pll_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*) ; 
#define  DSS_PLL_HDMI 133 
#define  DSS_PLL_VIDEO1 132 
#define  DSS_PLL_VIDEO2 131 
#define  OMAP_DSS_CHANNEL_LCD 130 
#define  OMAP_DSS_CHANNEL_LCD2 129 
#define  OMAP_DSS_CHANNEL_LCD3 128 
 TYPE_1__ dss ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int) ; 

void dss_ctrl_pll_set_control_mux(enum dss_pll_id pll_id,
	enum omap_channel channel)
{
	unsigned shift, val;

	if (!dss.syscon_pll_ctrl)
		return;

	switch (channel) {
	case OMAP_DSS_CHANNEL_LCD:
		shift = 3;

		switch (pll_id) {
		case DSS_PLL_VIDEO1:
			val = 0; break;
		case DSS_PLL_HDMI:
			val = 1; break;
		default:
			DSSERR("error in PLL mux config for LCD\n");
			return;
		}

		break;
	case OMAP_DSS_CHANNEL_LCD2:
		shift = 5;

		switch (pll_id) {
		case DSS_PLL_VIDEO1:
			val = 0; break;
		case DSS_PLL_VIDEO2:
			val = 1; break;
		case DSS_PLL_HDMI:
			val = 2; break;
		default:
			DSSERR("error in PLL mux config for LCD2\n");
			return;
		}

		break;
	case OMAP_DSS_CHANNEL_LCD3:
		shift = 7;

		switch (pll_id) {
		case DSS_PLL_VIDEO1:
			val = 1; break;
		case DSS_PLL_VIDEO2:
			val = 0; break;
		case DSS_PLL_HDMI:
			val = 2; break;
		default:
			DSSERR("error in PLL mux config for LCD3\n");
			return;
		}

		break;
	default:
		DSSERR("error in PLL mux config\n");
		return;
	}

	regmap_update_bits(dss.syscon_pll_ctrl, dss.syscon_pll_ctrl_offset,
		0x3 << shift, val << shift);
}