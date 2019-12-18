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
struct chan_info_nphy_2055 {int RF_pll_ref; int RF_rf_pll_mod0; int RF_rf_pll_mod1; int RF_vco_cap_tail; int RF_vco_cal1; int RF_vco_cal2; int RF_pll_lf_c1; int RF_pll_lf_r1; int RF_pll_lf_c2; int RF_lgbuf_cen_buf; int RF_lgen_tune1; int RF_lgen_tune2; int RF_core1_lgbuf_a_tune; int RF_core1_lgbuf_g_tune; int RF_core1_rxrf_reg1; int RF_core1_tx_pga_pad_tn; int RF_core1_tx_mx_bgtrim; int RF_core2_lgbuf_a_tune; int RF_core2_lgbuf_g_tune; int RF_core2_rxrf_reg1; int RF_core2_tx_pga_pad_tn; int RF_core2_tx_mx_bgtrim; } ;
struct brcms_phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMS_PHY_WAR_PR51571 (struct brcms_phy*) ; 
 int /*<<< orphan*/  RADIO_2055_CORE1_LGBUF_A_TUNE ; 
 int /*<<< orphan*/  RADIO_2055_CORE1_LGBUF_G_TUNE ; 
 int /*<<< orphan*/  RADIO_2055_CORE1_RXRF_REG1 ; 
 int /*<<< orphan*/  RADIO_2055_CORE1_TX_MX_BGTRIM ; 
 int /*<<< orphan*/  RADIO_2055_CORE1_TX_PGA_PAD_TN ; 
 int /*<<< orphan*/  RADIO_2055_CORE2_LGBUF_A_TUNE ; 
 int /*<<< orphan*/  RADIO_2055_CORE2_LGBUF_G_TUNE ; 
 int /*<<< orphan*/  RADIO_2055_CORE2_RXRF_REG1 ; 
 int /*<<< orphan*/  RADIO_2055_CORE2_TX_MX_BGTRIM ; 
 int /*<<< orphan*/  RADIO_2055_CORE2_TX_PGA_PAD_TN ; 
 int /*<<< orphan*/  RADIO_2055_LGBUF_CEN_BUF ; 
 int /*<<< orphan*/  RADIO_2055_LGEN_TUNE1 ; 
 int /*<<< orphan*/  RADIO_2055_LGEN_TUNE2 ; 
 int /*<<< orphan*/  RADIO_2055_PLL_LF_C1 ; 
 int /*<<< orphan*/  RADIO_2055_PLL_LF_C2 ; 
 int /*<<< orphan*/  RADIO_2055_PLL_LF_R1 ; 
 int /*<<< orphan*/  RADIO_2055_PLL_REF ; 
 int /*<<< orphan*/  RADIO_2055_RF_PLL_MOD0 ; 
 int /*<<< orphan*/  RADIO_2055_RF_PLL_MOD1 ; 
 int /*<<< orphan*/  RADIO_2055_VCO_CAL1 ; 
 int /*<<< orphan*/  RADIO_2055_VCO_CAL10 ; 
 int /*<<< orphan*/  RADIO_2055_VCO_CAL2 ; 
 int /*<<< orphan*/  RADIO_2055_VCO_CAP_TAIL ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  write_radio_reg (struct brcms_phy*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
wlc_phy_chanspec_radio2055_setup(struct brcms_phy *pi,
				 const struct chan_info_nphy_2055 *ci)
{

	write_radio_reg(pi, RADIO_2055_PLL_REF, ci->RF_pll_ref);
	write_radio_reg(pi, RADIO_2055_RF_PLL_MOD0, ci->RF_rf_pll_mod0);
	write_radio_reg(pi, RADIO_2055_RF_PLL_MOD1, ci->RF_rf_pll_mod1);
	write_radio_reg(pi, RADIO_2055_VCO_CAP_TAIL, ci->RF_vco_cap_tail);

	BRCMS_PHY_WAR_PR51571(pi);

	write_radio_reg(pi, RADIO_2055_VCO_CAL1, ci->RF_vco_cal1);
	write_radio_reg(pi, RADIO_2055_VCO_CAL2, ci->RF_vco_cal2);
	write_radio_reg(pi, RADIO_2055_PLL_LF_C1, ci->RF_pll_lf_c1);
	write_radio_reg(pi, RADIO_2055_PLL_LF_R1, ci->RF_pll_lf_r1);

	BRCMS_PHY_WAR_PR51571(pi);

	write_radio_reg(pi, RADIO_2055_PLL_LF_C2, ci->RF_pll_lf_c2);
	write_radio_reg(pi, RADIO_2055_LGBUF_CEN_BUF, ci->RF_lgbuf_cen_buf);
	write_radio_reg(pi, RADIO_2055_LGEN_TUNE1, ci->RF_lgen_tune1);
	write_radio_reg(pi, RADIO_2055_LGEN_TUNE2, ci->RF_lgen_tune2);

	BRCMS_PHY_WAR_PR51571(pi);

	write_radio_reg(pi, RADIO_2055_CORE1_LGBUF_A_TUNE,
			ci->RF_core1_lgbuf_a_tune);
	write_radio_reg(pi, RADIO_2055_CORE1_LGBUF_G_TUNE,
			ci->RF_core1_lgbuf_g_tune);
	write_radio_reg(pi, RADIO_2055_CORE1_RXRF_REG1, ci->RF_core1_rxrf_reg1);
	write_radio_reg(pi, RADIO_2055_CORE1_TX_PGA_PAD_TN,
			ci->RF_core1_tx_pga_pad_tn);

	BRCMS_PHY_WAR_PR51571(pi);

	write_radio_reg(pi, RADIO_2055_CORE1_TX_MX_BGTRIM,
			ci->RF_core1_tx_mx_bgtrim);
	write_radio_reg(pi, RADIO_2055_CORE2_LGBUF_A_TUNE,
			ci->RF_core2_lgbuf_a_tune);
	write_radio_reg(pi, RADIO_2055_CORE2_LGBUF_G_TUNE,
			ci->RF_core2_lgbuf_g_tune);
	write_radio_reg(pi, RADIO_2055_CORE2_RXRF_REG1, ci->RF_core2_rxrf_reg1);

	BRCMS_PHY_WAR_PR51571(pi);

	write_radio_reg(pi, RADIO_2055_CORE2_TX_PGA_PAD_TN,
			ci->RF_core2_tx_pga_pad_tn);
	write_radio_reg(pi, RADIO_2055_CORE2_TX_MX_BGTRIM,
			ci->RF_core2_tx_mx_bgtrim);

	udelay(50);

	write_radio_reg(pi, RADIO_2055_VCO_CAL10, 0x05);
	write_radio_reg(pi, RADIO_2055_VCO_CAL10, 0x45);

	BRCMS_PHY_WAR_PR51571(pi);

	write_radio_reg(pi, RADIO_2055_VCO_CAL10, 0x65);

	udelay(300);
}