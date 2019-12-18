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
struct ti_sn_bridge {int /*<<< orphan*/  panel; int /*<<< orphan*/  regmap; int /*<<< orphan*/  aux; TYPE_1__* dsi; } ;
struct drm_bridge {int dummy; } ;
struct TYPE_2__ {scalar_t__ lanes; } ;

/* Variables and functions */
 unsigned int CHA_DSI_LANES (scalar_t__) ; 
 unsigned int CHA_DSI_LANES_MASK ; 
 unsigned int DPPLL_SRC_DP_PLL_LOCK ; 
 int /*<<< orphan*/  DP_ALTERNATE_SCRAMBLER_RESET_ENABLE ; 
 int /*<<< orphan*/  DP_EDP_CONFIGURATION_SET ; 
 unsigned int DP_NUM_LANES (scalar_t__) ; 
 unsigned int DP_NUM_LANES_MASK ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 unsigned int ML_TX_MAIN_LINK_OFF ; 
 unsigned int ML_TX_NORMAL_MODE ; 
 int /*<<< orphan*/  SN_DPPLL_SRC_REG ; 
 int /*<<< orphan*/  SN_DSI_LANES_REG ; 
 int /*<<< orphan*/  SN_ENH_FRAME_REG ; 
 int /*<<< orphan*/  SN_ML_TX_MODE_REG ; 
 int /*<<< orphan*/  SN_PLL_ENABLE_REG ; 
 int /*<<< orphan*/  SN_SSC_CONFIG_REG ; 
 unsigned int VSTREAM_ENABLE ; 
 struct ti_sn_bridge* bridge_to_ti_sn_bridge (struct drm_bridge*) ; 
 int /*<<< orphan*/  drm_dp_dpcd_writeb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_panel_enable (int /*<<< orphan*/ ) ; 
 int regmap_read_poll_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int,int,int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ti_sn_bridge_set_dsi_dp_rate (struct ti_sn_bridge*) ; 
 int /*<<< orphan*/  ti_sn_bridge_set_video_timings (struct ti_sn_bridge*) ; 

__attribute__((used)) static void ti_sn_bridge_enable(struct drm_bridge *bridge)
{
	struct ti_sn_bridge *pdata = bridge_to_ti_sn_bridge(bridge);
	unsigned int val;
	int ret;

	/* DSI_A lane config */
	val = CHA_DSI_LANES(4 - pdata->dsi->lanes);
	regmap_update_bits(pdata->regmap, SN_DSI_LANES_REG,
			   CHA_DSI_LANES_MASK, val);

	/* DP lane config */
	val = DP_NUM_LANES(pdata->dsi->lanes - 1);
	regmap_update_bits(pdata->regmap, SN_SSC_CONFIG_REG, DP_NUM_LANES_MASK,
			   val);

	/* set dsi/dp clk frequency value */
	ti_sn_bridge_set_dsi_dp_rate(pdata);

	/* enable DP PLL */
	regmap_write(pdata->regmap, SN_PLL_ENABLE_REG, 1);

	ret = regmap_read_poll_timeout(pdata->regmap, SN_DPPLL_SRC_REG, val,
				       val & DPPLL_SRC_DP_PLL_LOCK, 1000,
				       50 * 1000);
	if (ret) {
		DRM_ERROR("DP_PLL_LOCK polling failed (%d)\n", ret);
		return;
	}

	/**
	 * The SN65DSI86 only supports ASSR Display Authentication method and
	 * this method is enabled by default. An eDP panel must support this
	 * authentication method. We need to enable this method in the eDP panel
	 * at DisplayPort address 0x0010A prior to link training.
	 */
	drm_dp_dpcd_writeb(&pdata->aux, DP_EDP_CONFIGURATION_SET,
			   DP_ALTERNATE_SCRAMBLER_RESET_ENABLE);

	/* Semi auto link training mode */
	regmap_write(pdata->regmap, SN_ML_TX_MODE_REG, 0x0A);
	ret = regmap_read_poll_timeout(pdata->regmap, SN_ML_TX_MODE_REG, val,
				       val == ML_TX_MAIN_LINK_OFF ||
				       val == ML_TX_NORMAL_MODE, 1000,
				       500 * 1000);
	if (ret) {
		DRM_ERROR("Training complete polling failed (%d)\n", ret);
		return;
	} else if (val == ML_TX_MAIN_LINK_OFF) {
		DRM_ERROR("Link training failed, link is off\n");
		return;
	}

	/* config video parameters */
	ti_sn_bridge_set_video_timings(pdata);

	/* enable video stream */
	regmap_update_bits(pdata->regmap, SN_ENH_FRAME_REG, VSTREAM_ENABLE,
			   VSTREAM_ENABLE);

	drm_panel_enable(pdata->panel);
}