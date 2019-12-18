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
struct sun8i_hdmi_phy {unsigned int rcal; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int SUN8I_HDMI_PHY_ANA_CFG1_BIASEN_TMDS0 ; 
 int SUN8I_HDMI_PHY_ANA_CFG1_BIASEN_TMDS1 ; 
 int SUN8I_HDMI_PHY_ANA_CFG1_BIASEN_TMDS2 ; 
 int SUN8I_HDMI_PHY_ANA_CFG1_BIASEN_TMDSCLK ; 
 int SUN8I_HDMI_PHY_ANA_CFG1_CKEN ; 
 int SUN8I_HDMI_PHY_ANA_CFG1_ENBI ; 
 int SUN8I_HDMI_PHY_ANA_CFG1_ENCALOG ; 
 int SUN8I_HDMI_PHY_ANA_CFG1_ENP2S_TMDS0 ; 
 int SUN8I_HDMI_PHY_ANA_CFG1_ENP2S_TMDS1 ; 
 int SUN8I_HDMI_PHY_ANA_CFG1_ENP2S_TMDS2 ; 
 int SUN8I_HDMI_PHY_ANA_CFG1_ENP2S_TMDSCLK ; 
 int SUN8I_HDMI_PHY_ANA_CFG1_ENRCAL ; 
 int SUN8I_HDMI_PHY_ANA_CFG1_ENVBS ; 
 int SUN8I_HDMI_PHY_ANA_CFG1_LDOEN ; 
 int /*<<< orphan*/  SUN8I_HDMI_PHY_ANA_CFG1_REG ; 
 int SUN8I_HDMI_PHY_ANA_CFG1_TMDSCLK_EN ; 
 int /*<<< orphan*/  SUN8I_HDMI_PHY_ANA_CFG3_REG ; 
 int SUN8I_HDMI_PHY_ANA_CFG3_SCLEN ; 
 int SUN8I_HDMI_PHY_ANA_CFG3_SDAEN ; 
 unsigned int SUN8I_HDMI_PHY_ANA_STS_RCALEND2D ; 
 unsigned int SUN8I_HDMI_PHY_ANA_STS_RCAL_MASK ; 
 int /*<<< orphan*/  SUN8I_HDMI_PHY_ANA_STS_REG ; 
 int /*<<< orphan*/  SUN8I_HDMI_PHY_CEC_REG ; 
 int SUN8I_HDMI_PHY_PLL_CFG1_CKIN_SEL_MSK ; 
 int /*<<< orphan*/  SUN8I_HDMI_PHY_PLL_CFG1_REG ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_read_poll_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,int,int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sun8i_hdmi_phy_unlock (struct sun8i_hdmi_phy*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void sun8i_hdmi_phy_init_h3(struct sun8i_hdmi_phy *phy)
{
	unsigned int val;

	sun8i_hdmi_phy_unlock(phy);

	regmap_write(phy->regs, SUN8I_HDMI_PHY_ANA_CFG1_REG, 0);
	regmap_update_bits(phy->regs, SUN8I_HDMI_PHY_ANA_CFG1_REG,
			   SUN8I_HDMI_PHY_ANA_CFG1_ENBI,
			   SUN8I_HDMI_PHY_ANA_CFG1_ENBI);
	udelay(5);
	regmap_update_bits(phy->regs, SUN8I_HDMI_PHY_ANA_CFG1_REG,
			   SUN8I_HDMI_PHY_ANA_CFG1_TMDSCLK_EN,
			   SUN8I_HDMI_PHY_ANA_CFG1_TMDSCLK_EN);
	regmap_update_bits(phy->regs, SUN8I_HDMI_PHY_ANA_CFG1_REG,
			   SUN8I_HDMI_PHY_ANA_CFG1_ENVBS,
			   SUN8I_HDMI_PHY_ANA_CFG1_ENVBS);
	usleep_range(10, 20);
	regmap_update_bits(phy->regs, SUN8I_HDMI_PHY_ANA_CFG1_REG,
			   SUN8I_HDMI_PHY_ANA_CFG1_LDOEN,
			   SUN8I_HDMI_PHY_ANA_CFG1_LDOEN);
	udelay(5);
	regmap_update_bits(phy->regs, SUN8I_HDMI_PHY_ANA_CFG1_REG,
			   SUN8I_HDMI_PHY_ANA_CFG1_CKEN,
			   SUN8I_HDMI_PHY_ANA_CFG1_CKEN);
	usleep_range(40, 100);
	regmap_update_bits(phy->regs, SUN8I_HDMI_PHY_ANA_CFG1_REG,
			   SUN8I_HDMI_PHY_ANA_CFG1_ENRCAL,
			   SUN8I_HDMI_PHY_ANA_CFG1_ENRCAL);
	usleep_range(100, 200);
	regmap_update_bits(phy->regs, SUN8I_HDMI_PHY_ANA_CFG1_REG,
			   SUN8I_HDMI_PHY_ANA_CFG1_ENCALOG,
			   SUN8I_HDMI_PHY_ANA_CFG1_ENCALOG);
	regmap_update_bits(phy->regs, SUN8I_HDMI_PHY_ANA_CFG1_REG,
			   SUN8I_HDMI_PHY_ANA_CFG1_ENP2S_TMDS0 |
			   SUN8I_HDMI_PHY_ANA_CFG1_ENP2S_TMDS1 |
			   SUN8I_HDMI_PHY_ANA_CFG1_ENP2S_TMDS2,
			   SUN8I_HDMI_PHY_ANA_CFG1_ENP2S_TMDS0 |
			   SUN8I_HDMI_PHY_ANA_CFG1_ENP2S_TMDS1 |
			   SUN8I_HDMI_PHY_ANA_CFG1_ENP2S_TMDS2);

	/* wait for calibration to finish */
	regmap_read_poll_timeout(phy->regs, SUN8I_HDMI_PHY_ANA_STS_REG, val,
				 (val & SUN8I_HDMI_PHY_ANA_STS_RCALEND2D),
				 100, 2000);

	regmap_update_bits(phy->regs, SUN8I_HDMI_PHY_ANA_CFG1_REG,
			   SUN8I_HDMI_PHY_ANA_CFG1_ENP2S_TMDSCLK,
			   SUN8I_HDMI_PHY_ANA_CFG1_ENP2S_TMDSCLK);
	regmap_update_bits(phy->regs, SUN8I_HDMI_PHY_ANA_CFG1_REG,
			   SUN8I_HDMI_PHY_ANA_CFG1_BIASEN_TMDS0 |
			   SUN8I_HDMI_PHY_ANA_CFG1_BIASEN_TMDS1 |
			   SUN8I_HDMI_PHY_ANA_CFG1_BIASEN_TMDS2 |
			   SUN8I_HDMI_PHY_ANA_CFG1_BIASEN_TMDSCLK,
			   SUN8I_HDMI_PHY_ANA_CFG1_BIASEN_TMDS0 |
			   SUN8I_HDMI_PHY_ANA_CFG1_BIASEN_TMDS1 |
			   SUN8I_HDMI_PHY_ANA_CFG1_BIASEN_TMDS2 |
			   SUN8I_HDMI_PHY_ANA_CFG1_BIASEN_TMDSCLK);

	/* enable DDC communication */
	regmap_update_bits(phy->regs, SUN8I_HDMI_PHY_ANA_CFG3_REG,
			   SUN8I_HDMI_PHY_ANA_CFG3_SCLEN |
			   SUN8I_HDMI_PHY_ANA_CFG3_SDAEN,
			   SUN8I_HDMI_PHY_ANA_CFG3_SCLEN |
			   SUN8I_HDMI_PHY_ANA_CFG3_SDAEN);

	/* reset PHY PLL clock parent */
	regmap_update_bits(phy->regs, SUN8I_HDMI_PHY_PLL_CFG1_REG,
			   SUN8I_HDMI_PHY_PLL_CFG1_CKIN_SEL_MSK, 0);

	/* set HW control of CEC pins */
	regmap_write(phy->regs, SUN8I_HDMI_PHY_CEC_REG, 0);

	/* read calibration data */
	regmap_read(phy->regs, SUN8I_HDMI_PHY_ANA_STS_REG, &val);
	phy->rcal = (val & SUN8I_HDMI_PHY_ANA_STS_RCAL_MASK) >> 2;
}