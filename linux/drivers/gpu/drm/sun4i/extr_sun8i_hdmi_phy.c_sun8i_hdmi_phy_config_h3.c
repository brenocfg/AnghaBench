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
typedef  int u32 ;
struct sun8i_hdmi_phy {int /*<<< orphan*/  regs; int /*<<< orphan*/  rcal; } ;
struct dw_hdmi {int dummy; } ;

/* Variables and functions */
 int SUN8I_HDMI_PHY_ANA_CFG1_AMPCK_OPT ; 
 int SUN8I_HDMI_PHY_ANA_CFG1_AMP_OPT ; 
 int SUN8I_HDMI_PHY_ANA_CFG1_BIASEN_TMDS0 ; 
 int SUN8I_HDMI_PHY_ANA_CFG1_BIASEN_TMDS1 ; 
 int SUN8I_HDMI_PHY_ANA_CFG1_BIASEN_TMDS2 ; 
 int SUN8I_HDMI_PHY_ANA_CFG1_BIASEN_TMDSCLK ; 
 int SUN8I_HDMI_PHY_ANA_CFG1_CKEN ; 
 int SUN8I_HDMI_PHY_ANA_CFG1_EMPCK_OPT ; 
 int SUN8I_HDMI_PHY_ANA_CFG1_EMP_OPT ; 
 int SUN8I_HDMI_PHY_ANA_CFG1_ENBI ; 
 int SUN8I_HDMI_PHY_ANA_CFG1_ENCALOG ; 
 int SUN8I_HDMI_PHY_ANA_CFG1_ENP2S_TMDS0 ; 
 int SUN8I_HDMI_PHY_ANA_CFG1_ENP2S_TMDS1 ; 
 int SUN8I_HDMI_PHY_ANA_CFG1_ENP2S_TMDS2 ; 
 int SUN8I_HDMI_PHY_ANA_CFG1_ENRCAL ; 
 int SUN8I_HDMI_PHY_ANA_CFG1_ENVBS ; 
 int SUN8I_HDMI_PHY_ANA_CFG1_LDOEN ; 
 int /*<<< orphan*/  SUN8I_HDMI_PHY_ANA_CFG1_REG ; 
 int SUN8I_HDMI_PHY_ANA_CFG1_REG_CALSW ; 
 int SUN8I_HDMI_PHY_ANA_CFG1_REG_SCKTMDS ; 
 int SUN8I_HDMI_PHY_ANA_CFG1_REG_SVBH (int) ; 
 int SUN8I_HDMI_PHY_ANA_CFG1_TMDSCLK_EN ; 
 int SUN8I_HDMI_PHY_ANA_CFG1_TXEN_ALL ; 
 int SUN8I_HDMI_PHY_ANA_CFG1_TXEN_MASK ; 
 int SUN8I_HDMI_PHY_ANA_CFG2_M_EN ; 
 int /*<<< orphan*/  SUN8I_HDMI_PHY_ANA_CFG2_REG ; 
 int SUN8I_HDMI_PHY_ANA_CFG2_REG_BIGSW ; 
 int SUN8I_HDMI_PHY_ANA_CFG2_REG_BIGSWCK ; 
 int SUN8I_HDMI_PHY_ANA_CFG2_REG_CKSS (int) ; 
 int SUN8I_HDMI_PHY_ANA_CFG2_REG_CSMPS (int) ; 
 int SUN8I_HDMI_PHY_ANA_CFG2_REG_DEN ; 
 int SUN8I_HDMI_PHY_ANA_CFG2_REG_DENCK ; 
 int SUN8I_HDMI_PHY_ANA_CFG2_REG_RESDI (int /*<<< orphan*/ ) ; 
 int SUN8I_HDMI_PHY_ANA_CFG2_REG_SLV (int) ; 
 int /*<<< orphan*/  SUN8I_HDMI_PHY_ANA_CFG3_REG ; 
 int SUN8I_HDMI_PHY_ANA_CFG3_REG_AMP (int) ; 
 int SUN8I_HDMI_PHY_ANA_CFG3_REG_AMPCK (int) ; 
 int SUN8I_HDMI_PHY_ANA_CFG3_REG_EMP (int) ; 
 int SUN8I_HDMI_PHY_ANA_CFG3_REG_WIRE (int) ; 
 int SUN8I_HDMI_PHY_ANA_CFG3_SCLEN ; 
 int SUN8I_HDMI_PHY_ANA_CFG3_SDAEN ; 
 int SUN8I_HDMI_PHY_ANA_STS_B_OUT_MSK ; 
 int SUN8I_HDMI_PHY_ANA_STS_B_OUT_SHIFT ; 
 int /*<<< orphan*/  SUN8I_HDMI_PHY_ANA_STS_REG ; 
 int SUN8I_HDMI_PHY_PLL_CFG1_BWS ; 
 int SUN8I_HDMI_PHY_PLL_CFG1_B_IN_MSK ; 
 int SUN8I_HDMI_PHY_PLL_CFG1_B_IN_SHIFT ; 
 scalar_t__ SUN8I_HDMI_PHY_PLL_CFG1_CKIN_SEL_MSK ; 
 int SUN8I_HDMI_PHY_PLL_CFG1_CNT_INT (int) ; 
 int SUN8I_HDMI_PHY_PLL_CFG1_CP_S (int) ; 
 int SUN8I_HDMI_PHY_PLL_CFG1_CS ; 
 int SUN8I_HDMI_PHY_PLL_CFG1_HV_IS_33 ; 
 int SUN8I_HDMI_PHY_PLL_CFG1_LDO1_EN ; 
 int SUN8I_HDMI_PHY_PLL_CFG1_LDO2_EN ; 
 int SUN8I_HDMI_PHY_PLL_CFG1_LDO_VSET (int) ; 
 int SUN8I_HDMI_PHY_PLL_CFG1_PLLDBEN ; 
 int SUN8I_HDMI_PHY_PLL_CFG1_PLLEN ; 
 int /*<<< orphan*/  SUN8I_HDMI_PHY_PLL_CFG1_REG ; 
 int SUN8I_HDMI_PHY_PLL_CFG1_REG_OD ; 
 int SUN8I_HDMI_PHY_PLL_CFG1_REG_OD1 ; 
 int SUN8I_HDMI_PHY_PLL_CFG1_UNKNOWN (int) ; 
 scalar_t__ SUN8I_HDMI_PHY_PLL_CFG2_PREDIV_MSK ; 
 int /*<<< orphan*/  SUN8I_HDMI_PHY_PLL_CFG2_REG ; 
 int SUN8I_HDMI_PHY_PLL_CFG2_S (int) ; 
 int SUN8I_HDMI_PHY_PLL_CFG2_SDIV2 ; 
 int SUN8I_HDMI_PHY_PLL_CFG2_SV_H ; 
 int SUN8I_HDMI_PHY_PLL_CFG2_VCOGAIN_EN ; 
 int SUN8I_HDMI_PHY_PLL_CFG2_VCO_S (int) ; 
 int /*<<< orphan*/  SUN8I_HDMI_PHY_PLL_CFG3_REG ; 
 int SUN8I_HDMI_PHY_PLL_CFG3_SOUT_DIV2 ; 
 int min (int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int sun8i_hdmi_phy_config_h3(struct dw_hdmi *hdmi,
				    struct sun8i_hdmi_phy *phy,
				    unsigned int clk_rate)
{
	u32 pll_cfg1_init;
	u32 pll_cfg2_init;
	u32 ana_cfg1_end;
	u32 ana_cfg2_init;
	u32 ana_cfg3_init;
	u32 b_offset = 0;
	u32 val;

	/* bandwidth / frequency independent settings */

	pll_cfg1_init = SUN8I_HDMI_PHY_PLL_CFG1_LDO2_EN |
			SUN8I_HDMI_PHY_PLL_CFG1_LDO1_EN |
			SUN8I_HDMI_PHY_PLL_CFG1_LDO_VSET(7) |
			SUN8I_HDMI_PHY_PLL_CFG1_UNKNOWN(1) |
			SUN8I_HDMI_PHY_PLL_CFG1_PLLDBEN |
			SUN8I_HDMI_PHY_PLL_CFG1_CS |
			SUN8I_HDMI_PHY_PLL_CFG1_CP_S(2) |
			SUN8I_HDMI_PHY_PLL_CFG1_CNT_INT(63) |
			SUN8I_HDMI_PHY_PLL_CFG1_BWS;

	pll_cfg2_init = SUN8I_HDMI_PHY_PLL_CFG2_SV_H |
			SUN8I_HDMI_PHY_PLL_CFG2_VCOGAIN_EN |
			SUN8I_HDMI_PHY_PLL_CFG2_SDIV2;

	ana_cfg1_end = SUN8I_HDMI_PHY_ANA_CFG1_REG_SVBH(1) |
		       SUN8I_HDMI_PHY_ANA_CFG1_AMP_OPT |
		       SUN8I_HDMI_PHY_ANA_CFG1_EMP_OPT |
		       SUN8I_HDMI_PHY_ANA_CFG1_AMPCK_OPT |
		       SUN8I_HDMI_PHY_ANA_CFG1_EMPCK_OPT |
		       SUN8I_HDMI_PHY_ANA_CFG1_ENRCAL |
		       SUN8I_HDMI_PHY_ANA_CFG1_ENCALOG |
		       SUN8I_HDMI_PHY_ANA_CFG1_REG_SCKTMDS |
		       SUN8I_HDMI_PHY_ANA_CFG1_TMDSCLK_EN |
		       SUN8I_HDMI_PHY_ANA_CFG1_TXEN_MASK |
		       SUN8I_HDMI_PHY_ANA_CFG1_TXEN_ALL |
		       SUN8I_HDMI_PHY_ANA_CFG1_BIASEN_TMDSCLK |
		       SUN8I_HDMI_PHY_ANA_CFG1_BIASEN_TMDS2 |
		       SUN8I_HDMI_PHY_ANA_CFG1_BIASEN_TMDS1 |
		       SUN8I_HDMI_PHY_ANA_CFG1_BIASEN_TMDS0 |
		       SUN8I_HDMI_PHY_ANA_CFG1_ENP2S_TMDS2 |
		       SUN8I_HDMI_PHY_ANA_CFG1_ENP2S_TMDS1 |
		       SUN8I_HDMI_PHY_ANA_CFG1_ENP2S_TMDS0 |
		       SUN8I_HDMI_PHY_ANA_CFG1_CKEN |
		       SUN8I_HDMI_PHY_ANA_CFG1_LDOEN |
		       SUN8I_HDMI_PHY_ANA_CFG1_ENVBS |
		       SUN8I_HDMI_PHY_ANA_CFG1_ENBI;

	ana_cfg2_init = SUN8I_HDMI_PHY_ANA_CFG2_M_EN |
			SUN8I_HDMI_PHY_ANA_CFG2_REG_DENCK |
			SUN8I_HDMI_PHY_ANA_CFG2_REG_DEN |
			SUN8I_HDMI_PHY_ANA_CFG2_REG_CKSS(1) |
			SUN8I_HDMI_PHY_ANA_CFG2_REG_CSMPS(1);

	ana_cfg3_init = SUN8I_HDMI_PHY_ANA_CFG3_REG_WIRE(0x3e0) |
			SUN8I_HDMI_PHY_ANA_CFG3_SDAEN |
			SUN8I_HDMI_PHY_ANA_CFG3_SCLEN;

	/* bandwidth / frequency dependent settings */
	if (clk_rate <= 27000000) {
		pll_cfg1_init |= SUN8I_HDMI_PHY_PLL_CFG1_HV_IS_33 |
				 SUN8I_HDMI_PHY_PLL_CFG1_CNT_INT(32);
		pll_cfg2_init |= SUN8I_HDMI_PHY_PLL_CFG2_VCO_S(4) |
				 SUN8I_HDMI_PHY_PLL_CFG2_S(4);
		ana_cfg1_end |= SUN8I_HDMI_PHY_ANA_CFG1_REG_CALSW;
		ana_cfg2_init |= SUN8I_HDMI_PHY_ANA_CFG2_REG_SLV(4) |
				 SUN8I_HDMI_PHY_ANA_CFG2_REG_RESDI(phy->rcal);
		ana_cfg3_init |= SUN8I_HDMI_PHY_ANA_CFG3_REG_AMPCK(3) |
				 SUN8I_HDMI_PHY_ANA_CFG3_REG_AMP(5);
	} else if (clk_rate <= 74250000) {
		pll_cfg1_init |= SUN8I_HDMI_PHY_PLL_CFG1_HV_IS_33 |
				 SUN8I_HDMI_PHY_PLL_CFG1_CNT_INT(32);
		pll_cfg2_init |= SUN8I_HDMI_PHY_PLL_CFG2_VCO_S(4) |
				 SUN8I_HDMI_PHY_PLL_CFG2_S(5);
		ana_cfg1_end |= SUN8I_HDMI_PHY_ANA_CFG1_REG_CALSW;
		ana_cfg2_init |= SUN8I_HDMI_PHY_ANA_CFG2_REG_SLV(4) |
				 SUN8I_HDMI_PHY_ANA_CFG2_REG_RESDI(phy->rcal);
		ana_cfg3_init |= SUN8I_HDMI_PHY_ANA_CFG3_REG_AMPCK(5) |
				 SUN8I_HDMI_PHY_ANA_CFG3_REG_AMP(7);
	} else if (clk_rate <= 148500000) {
		pll_cfg1_init |= SUN8I_HDMI_PHY_PLL_CFG1_HV_IS_33 |
				 SUN8I_HDMI_PHY_PLL_CFG1_CNT_INT(32);
		pll_cfg2_init |= SUN8I_HDMI_PHY_PLL_CFG2_VCO_S(4) |
				 SUN8I_HDMI_PHY_PLL_CFG2_S(6);
		ana_cfg2_init |= SUN8I_HDMI_PHY_ANA_CFG2_REG_BIGSWCK |
				 SUN8I_HDMI_PHY_ANA_CFG2_REG_BIGSW |
				 SUN8I_HDMI_PHY_ANA_CFG2_REG_SLV(2);
		ana_cfg3_init |= SUN8I_HDMI_PHY_ANA_CFG3_REG_AMPCK(7) |
				 SUN8I_HDMI_PHY_ANA_CFG3_REG_AMP(9);
	} else {
		b_offset = 2;
		pll_cfg1_init |= SUN8I_HDMI_PHY_PLL_CFG1_CNT_INT(63);
		pll_cfg2_init |= SUN8I_HDMI_PHY_PLL_CFG2_VCO_S(6) |
				 SUN8I_HDMI_PHY_PLL_CFG2_S(7);
		ana_cfg2_init |= SUN8I_HDMI_PHY_ANA_CFG2_REG_BIGSWCK |
				 SUN8I_HDMI_PHY_ANA_CFG2_REG_BIGSW |
				 SUN8I_HDMI_PHY_ANA_CFG2_REG_SLV(4);
		ana_cfg3_init |= SUN8I_HDMI_PHY_ANA_CFG3_REG_AMPCK(9) |
				 SUN8I_HDMI_PHY_ANA_CFG3_REG_AMP(13) |
				 SUN8I_HDMI_PHY_ANA_CFG3_REG_EMP(3);
	}

	regmap_update_bits(phy->regs, SUN8I_HDMI_PHY_ANA_CFG1_REG,
			   SUN8I_HDMI_PHY_ANA_CFG1_TXEN_MASK, 0);

	/*
	 * NOTE: We have to be careful not to overwrite PHY parent
	 * clock selection bit and clock divider.
	 */
	regmap_update_bits(phy->regs, SUN8I_HDMI_PHY_PLL_CFG1_REG,
			   (u32)~SUN8I_HDMI_PHY_PLL_CFG1_CKIN_SEL_MSK,
			   pll_cfg1_init);
	regmap_update_bits(phy->regs, SUN8I_HDMI_PHY_PLL_CFG2_REG,
			   (u32)~SUN8I_HDMI_PHY_PLL_CFG2_PREDIV_MSK,
			   pll_cfg2_init);
	usleep_range(10000, 15000);
	regmap_write(phy->regs, SUN8I_HDMI_PHY_PLL_CFG3_REG,
		     SUN8I_HDMI_PHY_PLL_CFG3_SOUT_DIV2);
	regmap_update_bits(phy->regs, SUN8I_HDMI_PHY_PLL_CFG1_REG,
			   SUN8I_HDMI_PHY_PLL_CFG1_PLLEN,
			   SUN8I_HDMI_PHY_PLL_CFG1_PLLEN);
	msleep(100);

	/* get B value */
	regmap_read(phy->regs, SUN8I_HDMI_PHY_ANA_STS_REG, &val);
	val = (val & SUN8I_HDMI_PHY_ANA_STS_B_OUT_MSK) >>
		SUN8I_HDMI_PHY_ANA_STS_B_OUT_SHIFT;
	val = min(val + b_offset, (u32)0x3f);

	regmap_update_bits(phy->regs, SUN8I_HDMI_PHY_PLL_CFG1_REG,
			   SUN8I_HDMI_PHY_PLL_CFG1_REG_OD1 |
			   SUN8I_HDMI_PHY_PLL_CFG1_REG_OD,
			   SUN8I_HDMI_PHY_PLL_CFG1_REG_OD1 |
			   SUN8I_HDMI_PHY_PLL_CFG1_REG_OD);
	regmap_update_bits(phy->regs, SUN8I_HDMI_PHY_PLL_CFG1_REG,
			   SUN8I_HDMI_PHY_PLL_CFG1_B_IN_MSK,
			   val << SUN8I_HDMI_PHY_PLL_CFG1_B_IN_SHIFT);
	msleep(100);
	regmap_write(phy->regs, SUN8I_HDMI_PHY_ANA_CFG1_REG, ana_cfg1_end);
	regmap_write(phy->regs, SUN8I_HDMI_PHY_ANA_CFG2_REG, ana_cfg2_init);
	regmap_write(phy->regs, SUN8I_HDMI_PHY_ANA_CFG3_REG, ana_cfg3_init);

	return 0;
}