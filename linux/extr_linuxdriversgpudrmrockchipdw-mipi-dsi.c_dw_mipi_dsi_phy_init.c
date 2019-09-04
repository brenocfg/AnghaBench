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
struct dw_mipi_dsi {int lane_mbps; int /*<<< orphan*/  phy_cfg_clk; int /*<<< orphan*/  dev; scalar_t__ base; int /*<<< orphan*/  feedback_div; int /*<<< orphan*/  input_div; } ;

/* Variables and functions */
 int /*<<< orphan*/  BANDGAP_96_10 ; 
 int BANDGAP_ON ; 
 int BANDGAP_SEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIASEXTR_127_7 ; 
 int BIASEXTR_SEL (int /*<<< orphan*/ ) ; 
 int BIAS_BLOCK_ON ; 
 int BIT (int) ; 
 int BYPASS_VCO_RANGE ; 
 int CP_CURRENT_3MA ; 
 int CP_PROGRAM_EN ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  DSI_PHY_RSTZ ; 
 scalar_t__ DSI_PHY_STATUS ; 
 int /*<<< orphan*/  DSI_PHY_TST_CTRL0 ; 
 int HIGH_PROGRAM_EN ; 
 int HSFREQRANGE_SEL (int) ; 
 int INPUT_DIVIDER (int /*<<< orphan*/ ) ; 
 int INTERNAL_REG_CURRENT ; 
 int LEVEL_SHIFTERS_ON ; 
 int LOCK ; 
 int LOOP_DIV_HIGH_SEL (int /*<<< orphan*/ ) ; 
 int LOOP_DIV_LOW_SEL (int /*<<< orphan*/ ) ; 
 int LOW_PROGRAM_EN ; 
 int LPF_PROGRAM_EN ; 
 int LPF_RESISTORS_20_KOHM ; 
 int PHY_ENABLECLK ; 
 int PHY_ENFORCEPLL ; 
 int /*<<< orphan*/  PHY_STATUS_TIMEOUT_US ; 
 int PHY_TESTCLR ; 
 int PHY_UNRSTZ ; 
 int PHY_UNSHUTDOWNZ ; 
 int PHY_UNTESTCLR ; 
 int PLL_INPUT_DIV_EN ; 
 int PLL_LOOP_DIV_EN ; 
 int POWER_CONTROL ; 
 int POWER_MANAGE ; 
 int REF_BIAS_CUR_SEL ; 
 int SETRD_MAX ; 
 int STOP_STATE_CLK_LANE ; 
 int TER_CAL_DONE ; 
 int TER_RESISTORS_ON ; 
 int TER_RESISTOR_HIGH ; 
 int TER_RESISTOR_LOW ; 
 int THS_PRE_PROGRAM_EN ; 
 int THS_ZERO_PROGRAM_EN ; 
 int TLP_PROGRAM_EN ; 
 int VCO_IN_CAP_CON_LOW ; 
 int VCO_RANGE_CON_SEL (int) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_write (struct dw_mipi_dsi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dw_mipi_dsi_phy_write (struct dw_mipi_dsi*,int,int) ; 
 int max_mbps_to_testdin (int) ; 
 int ns2bc (struct dw_mipi_dsi*,int) ; 
 int ns2ui (struct dw_mipi_dsi*,int) ; 
 int readl_poll_timeout (scalar_t__,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dw_mipi_dsi_phy_init(struct dw_mipi_dsi *dsi)
{
	int ret, testdin, vco, val;

	vco = (dsi->lane_mbps < 200) ? 0 : (dsi->lane_mbps + 100) / 200;

	testdin = max_mbps_to_testdin(dsi->lane_mbps);
	if (testdin < 0) {
		DRM_DEV_ERROR(dsi->dev,
			      "failed to get testdin for %dmbps lane clock\n",
			      dsi->lane_mbps);
		return testdin;
	}

	/* Start by clearing PHY state */
	dsi_write(dsi, DSI_PHY_TST_CTRL0, PHY_UNTESTCLR);
	dsi_write(dsi, DSI_PHY_TST_CTRL0, PHY_TESTCLR);
	dsi_write(dsi, DSI_PHY_TST_CTRL0, PHY_UNTESTCLR);

	ret = clk_prepare_enable(dsi->phy_cfg_clk);
	if (ret) {
		DRM_DEV_ERROR(dsi->dev, "Failed to enable phy_cfg_clk\n");
		return ret;
	}

	dw_mipi_dsi_phy_write(dsi, 0x10, BYPASS_VCO_RANGE |
					 VCO_RANGE_CON_SEL(vco) |
					 VCO_IN_CAP_CON_LOW |
					 REF_BIAS_CUR_SEL);

	dw_mipi_dsi_phy_write(dsi, 0x11, CP_CURRENT_3MA);
	dw_mipi_dsi_phy_write(dsi, 0x12, CP_PROGRAM_EN | LPF_PROGRAM_EN |
					 LPF_RESISTORS_20_KOHM);

	dw_mipi_dsi_phy_write(dsi, 0x44, HSFREQRANGE_SEL(testdin));

	dw_mipi_dsi_phy_write(dsi, 0x17, INPUT_DIVIDER(dsi->input_div));
	dw_mipi_dsi_phy_write(dsi, 0x18, LOOP_DIV_LOW_SEL(dsi->feedback_div) |
					 LOW_PROGRAM_EN);
	dw_mipi_dsi_phy_write(dsi, 0x18, LOOP_DIV_HIGH_SEL(dsi->feedback_div) |
					 HIGH_PROGRAM_EN);
	dw_mipi_dsi_phy_write(dsi, 0x19, PLL_LOOP_DIV_EN | PLL_INPUT_DIV_EN);

	dw_mipi_dsi_phy_write(dsi, 0x22, LOW_PROGRAM_EN |
					 BIASEXTR_SEL(BIASEXTR_127_7));
	dw_mipi_dsi_phy_write(dsi, 0x22, HIGH_PROGRAM_EN |
					 BANDGAP_SEL(BANDGAP_96_10));

	dw_mipi_dsi_phy_write(dsi, 0x20, POWER_CONTROL | INTERNAL_REG_CURRENT |
					 BIAS_BLOCK_ON | BANDGAP_ON);

	dw_mipi_dsi_phy_write(dsi, 0x21, TER_RESISTOR_LOW | TER_CAL_DONE |
					 SETRD_MAX | TER_RESISTORS_ON);
	dw_mipi_dsi_phy_write(dsi, 0x21, TER_RESISTOR_HIGH | LEVEL_SHIFTERS_ON |
					 SETRD_MAX | POWER_MANAGE |
					 TER_RESISTORS_ON);

	dw_mipi_dsi_phy_write(dsi, 0x60, TLP_PROGRAM_EN | ns2bc(dsi, 500));
	dw_mipi_dsi_phy_write(dsi, 0x61, THS_PRE_PROGRAM_EN | ns2ui(dsi, 40));
	dw_mipi_dsi_phy_write(dsi, 0x62, THS_ZERO_PROGRAM_EN | ns2bc(dsi, 300));
	dw_mipi_dsi_phy_write(dsi, 0x63, THS_PRE_PROGRAM_EN | ns2ui(dsi, 100));
	dw_mipi_dsi_phy_write(dsi, 0x64, BIT(5) | ns2bc(dsi, 100));
	dw_mipi_dsi_phy_write(dsi, 0x65, BIT(5) | (ns2bc(dsi, 60) + 7));

	dw_mipi_dsi_phy_write(dsi, 0x70, TLP_PROGRAM_EN | ns2bc(dsi, 500));
	dw_mipi_dsi_phy_write(dsi, 0x71,
			      THS_PRE_PROGRAM_EN | (ns2ui(dsi, 50) + 5));
	dw_mipi_dsi_phy_write(dsi, 0x72,
			      THS_ZERO_PROGRAM_EN | (ns2bc(dsi, 140) + 2));
	dw_mipi_dsi_phy_write(dsi, 0x73,
			      THS_PRE_PROGRAM_EN | (ns2ui(dsi, 60) + 8));
	dw_mipi_dsi_phy_write(dsi, 0x74, BIT(5) | ns2bc(dsi, 100));

	dsi_write(dsi, DSI_PHY_RSTZ, PHY_ENFORCEPLL | PHY_ENABLECLK |
				     PHY_UNRSTZ | PHY_UNSHUTDOWNZ);

	ret = readl_poll_timeout(dsi->base + DSI_PHY_STATUS,
				 val, val & LOCK, 1000, PHY_STATUS_TIMEOUT_US);
	if (ret < 0) {
		DRM_DEV_ERROR(dsi->dev, "failed to wait for phy lock state\n");
		goto phy_init_end;
	}

	ret = readl_poll_timeout(dsi->base + DSI_PHY_STATUS,
				 val, val & STOP_STATE_CLK_LANE, 1000,
				 PHY_STATUS_TIMEOUT_US);
	if (ret < 0)
		DRM_DEV_ERROR(dsi->dev,
			      "failed to wait for phy clk lane stop state\n");

phy_init_end:
	clk_disable_unprepare(dsi->phy_cfg_clk);

	return ret;
}