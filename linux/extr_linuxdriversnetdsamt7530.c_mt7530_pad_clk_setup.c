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
typedef  scalar_t__ u32 ;
struct mt7530_priv {int /*<<< orphan*/  dev; } ;
struct dsa_switch {struct mt7530_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CORE_GSWPLL_GRP1 ; 
 int /*<<< orphan*/  CORE_GSWPLL_GRP2 ; 
 int /*<<< orphan*/  CORE_PLL_GROUP10 ; 
 int /*<<< orphan*/  CORE_PLL_GROUP11 ; 
 int /*<<< orphan*/  CORE_PLL_GROUP2 ; 
 int /*<<< orphan*/  CORE_PLL_GROUP4 ; 
 int /*<<< orphan*/  CORE_PLL_GROUP5 ; 
 int /*<<< orphan*/  CORE_PLL_GROUP6 ; 
 int /*<<< orphan*/  CORE_PLL_GROUP7 ; 
 int /*<<< orphan*/  CORE_TRGMII_GSW_CLK_CG ; 
 int EINVAL ; 
 int /*<<< orphan*/  GSW_INTF_MODE ; 
 int /*<<< orphan*/  INTF_MODE_TRGMII ; 
 int /*<<< orphan*/  MDIO_MMD_VEND2 ; 
 int /*<<< orphan*/  MT7530_P6ECR ; 
 int /*<<< orphan*/  MT7530_TRGMII_RD (scalar_t__) ; 
 int /*<<< orphan*/  MT7530_TRGMII_TD_ODT (scalar_t__) ; 
 scalar_t__ NUM_TRGMII_CTRL ; 
 int /*<<< orphan*/  P6_INTF_MODE (scalar_t__) ; 
 int /*<<< orphan*/  P6_INTF_MODE_MASK ; 
#define  PHY_INTERFACE_MODE_RGMII 129 
#define  PHY_INTERFACE_MODE_TRGMII 128 
 int /*<<< orphan*/  RD_TAP (int) ; 
 int /*<<< orphan*/  RD_TAP_MASK ; 
 int REG_GSWCK_EN ; 
 int REG_TRGMIICK_EN ; 
 int RG_GSWPLL_EN_PRE ; 
 int RG_GSWPLL_FBKDIV_200M (int) ; 
 int RG_GSWPLL_FBKDIV_500M (int) ; 
 int RG_GSWPLL_POSDIV_200M (int) ; 
 int RG_GSWPLL_POSDIV_500M (int) ; 
 int RG_LCCDS_C (int) ; 
 int RG_LCDDS_ISO_EN ; 
 int RG_LCDDS_PCW_NCPO0 (int /*<<< orphan*/ ) ; 
 int RG_LCDDS_PCW_NCPO1 (scalar_t__) ; 
 int RG_LCDDS_PCW_NCPO_CHG ; 
 int RG_LCDDS_PWDB ; 
 int RG_LCDDS_SSC_DELTA (scalar_t__) ; 
 int RG_LCDDS_SSC_DELTA1 (scalar_t__) ; 
 int RG_SYSPLL_BIAS_EN ; 
 int RG_SYSPLL_BIAS_LPF_EN ; 
 int RG_SYSPLL_DDSFBK_EN ; 
 int RG_SYSPLL_EN_NORMAL ; 
 int RG_SYSPLL_POSDIV (int) ; 
 int RG_SYSPLL_VODEN ; 
 int TD_DM_DRVN (int) ; 
 int TD_DM_DRVP (int) ; 
 int /*<<< orphan*/  core_clear (struct mt7530_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  core_set (struct mt7530_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  core_write (struct mt7530_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  core_write_mmd_indirect (struct mt7530_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mt7530_rmw (struct mt7530_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt7530_write (struct mt7530_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt7623_trgmii_set (struct mt7530_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mt7530_pad_clk_setup(struct dsa_switch *ds, int mode)
{
	struct mt7530_priv *priv = ds->priv;
	u32 ncpo1, ssc_delta, trgint, i;

	switch (mode) {
	case PHY_INTERFACE_MODE_RGMII:
		trgint = 0;
		ncpo1 = 0x0c80;
		ssc_delta = 0x87;
		break;
	case PHY_INTERFACE_MODE_TRGMII:
		trgint = 1;
		ncpo1 = 0x1400;
		ssc_delta = 0x57;
		break;
	default:
		dev_err(priv->dev, "xMII mode %d not supported\n", mode);
		return -EINVAL;
	}

	mt7530_rmw(priv, MT7530_P6ECR, P6_INTF_MODE_MASK,
		   P6_INTF_MODE(trgint));

	/* Lower Tx Driving for TRGMII path */
	for (i = 0 ; i < NUM_TRGMII_CTRL ; i++)
		mt7530_write(priv, MT7530_TRGMII_TD_ODT(i),
			     TD_DM_DRVP(8) | TD_DM_DRVN(8));

	/* Setup core clock for MT7530 */
	if (!trgint) {
		/* Disable MT7530 core clock */
		core_clear(priv, CORE_TRGMII_GSW_CLK_CG, REG_GSWCK_EN);

		/* Disable PLL, since phy_device has not yet been created
		 * provided for phy_[read,write]_mmd_indirect is called, we
		 * provide our own core_write_mmd_indirect to complete this
		 * function.
		 */
		core_write_mmd_indirect(priv,
					CORE_GSWPLL_GRP1,
					MDIO_MMD_VEND2,
					0);

		/* Set core clock into 500Mhz */
		core_write(priv, CORE_GSWPLL_GRP2,
			   RG_GSWPLL_POSDIV_500M(1) |
			   RG_GSWPLL_FBKDIV_500M(25));

		/* Enable PLL */
		core_write(priv, CORE_GSWPLL_GRP1,
			   RG_GSWPLL_EN_PRE |
			   RG_GSWPLL_POSDIV_200M(2) |
			   RG_GSWPLL_FBKDIV_200M(32));

		/* Enable MT7530 core clock */
		core_set(priv, CORE_TRGMII_GSW_CLK_CG, REG_GSWCK_EN);
	}

	/* Setup the MT7530 TRGMII Tx Clock */
	core_set(priv, CORE_TRGMII_GSW_CLK_CG, REG_GSWCK_EN);
	core_write(priv, CORE_PLL_GROUP5, RG_LCDDS_PCW_NCPO1(ncpo1));
	core_write(priv, CORE_PLL_GROUP6, RG_LCDDS_PCW_NCPO0(0));
	core_write(priv, CORE_PLL_GROUP10, RG_LCDDS_SSC_DELTA(ssc_delta));
	core_write(priv, CORE_PLL_GROUP11, RG_LCDDS_SSC_DELTA1(ssc_delta));
	core_write(priv, CORE_PLL_GROUP4,
		   RG_SYSPLL_DDSFBK_EN | RG_SYSPLL_BIAS_EN |
		   RG_SYSPLL_BIAS_LPF_EN);
	core_write(priv, CORE_PLL_GROUP2,
		   RG_SYSPLL_EN_NORMAL | RG_SYSPLL_VODEN |
		   RG_SYSPLL_POSDIV(1));
	core_write(priv, CORE_PLL_GROUP7,
		   RG_LCDDS_PCW_NCPO_CHG | RG_LCCDS_C(3) |
		   RG_LCDDS_PWDB | RG_LCDDS_ISO_EN);
	core_set(priv, CORE_TRGMII_GSW_CLK_CG,
		 REG_GSWCK_EN | REG_TRGMIICK_EN);

	if (!trgint)
		for (i = 0 ; i < NUM_TRGMII_CTRL; i++)
			mt7530_rmw(priv, MT7530_TRGMII_RD(i),
				   RD_TAP_MASK, RD_TAP(16));
	else
		mt7623_trgmii_set(priv, GSW_INTF_MODE, INTF_MODE_TRGMII);

	return 0;
}