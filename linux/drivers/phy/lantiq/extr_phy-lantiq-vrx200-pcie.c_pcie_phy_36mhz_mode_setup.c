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
struct phy {int dummy; } ;
struct ltq_vrx200_pcie_phy_priv {int /*<<< orphan*/  phy_regmap; } ;

/* Variables and functions */
 int FIELD_PREP (int,int) ; 
 int /*<<< orphan*/  PCIE_PHY_PLL_A_CTRL2 ; 
 int PCIE_PHY_PLL_A_CTRL2_LF_MODE_EN ; 
 int /*<<< orphan*/  PCIE_PHY_PLL_A_CTRL3 ; 
 int PCIE_PHY_PLL_A_CTRL3_MMD_MASK ; 
 int /*<<< orphan*/  PCIE_PHY_PLL_CTRL1 ; 
 int /*<<< orphan*/  PCIE_PHY_PLL_CTRL2 ; 
 int PCIE_PHY_PLL_CTRL2_CONST_SDM_EN ; 
 int PCIE_PHY_PLL_CTRL2_CONST_SDM_MASK ; 
 int PCIE_PHY_PLL_CTRL2_PLL_SDM_EN ; 
 int /*<<< orphan*/  PCIE_PHY_PLL_CTRL3 ; 
 int PCIE_PHY_PLL_CTRL3_EXT_MMD_DIV_RATIO_EN ; 
 int PCIE_PHY_PLL_CTRL3_EXT_MMD_DIV_RATIO_MASK ; 
 int /*<<< orphan*/  PCIE_PHY_PLL_CTRL4 ; 
 int /*<<< orphan*/  PCIE_PHY_PLL_CTRL5 ; 
 int /*<<< orphan*/  PCIE_PHY_PLL_CTRL6 ; 
 int /*<<< orphan*/  PCIE_PHY_PLL_CTRL7 ; 
 struct ltq_vrx200_pcie_phy_priv* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pcie_phy_36mhz_mode_setup(struct phy *phy)
{
	struct ltq_vrx200_pcie_phy_priv *priv = phy_get_drvdata(phy);

	regmap_update_bits(priv->phy_regmap, PCIE_PHY_PLL_CTRL3,
			   PCIE_PHY_PLL_CTRL3_EXT_MMD_DIV_RATIO_EN, 0x0000);

	regmap_update_bits(priv->phy_regmap, PCIE_PHY_PLL_CTRL3,
			   PCIE_PHY_PLL_CTRL3_EXT_MMD_DIV_RATIO_MASK, 0x0000);

	regmap_update_bits(priv->phy_regmap, PCIE_PHY_PLL_CTRL2,
			   PCIE_PHY_PLL_CTRL2_PLL_SDM_EN,
			   PCIE_PHY_PLL_CTRL2_PLL_SDM_EN);

	regmap_update_bits(priv->phy_regmap, PCIE_PHY_PLL_CTRL2,
			   PCIE_PHY_PLL_CTRL2_CONST_SDM_EN,
			   PCIE_PHY_PLL_CTRL2_CONST_SDM_EN);

	regmap_update_bits(priv->phy_regmap, PCIE_PHY_PLL_A_CTRL3,
			   PCIE_PHY_PLL_A_CTRL3_MMD_MASK,
			   FIELD_PREP(PCIE_PHY_PLL_A_CTRL3_MMD_MASK, 0x1));

	regmap_update_bits(priv->phy_regmap, PCIE_PHY_PLL_A_CTRL2,
			   PCIE_PHY_PLL_A_CTRL2_LF_MODE_EN, 0x0000);

	/* const_sdm */
	regmap_write(priv->phy_regmap, PCIE_PHY_PLL_CTRL1, 0x38e4);

	regmap_update_bits(priv->phy_regmap, PCIE_PHY_PLL_CTRL2,
			   PCIE_PHY_PLL_CTRL2_CONST_SDM_MASK,
			   FIELD_PREP(PCIE_PHY_PLL_CTRL2_CONST_SDM_MASK,
				      0xee));

	/* pllmod */
	regmap_write(priv->phy_regmap, PCIE_PHY_PLL_CTRL7, 0x0002);
	regmap_write(priv->phy_regmap, PCIE_PHY_PLL_CTRL6, 0x3a04);
	regmap_write(priv->phy_regmap, PCIE_PHY_PLL_CTRL5, 0xfae3);
	regmap_write(priv->phy_regmap, PCIE_PHY_PLL_CTRL4, 0x1b72);
}