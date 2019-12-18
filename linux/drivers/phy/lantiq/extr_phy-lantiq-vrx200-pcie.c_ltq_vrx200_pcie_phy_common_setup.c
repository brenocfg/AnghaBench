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
 int /*<<< orphan*/  PCIE_PHY_PLL_A_CTRL1 ; 
 int /*<<< orphan*/  PCIE_PHY_PLL_A_CTRL2 ; 
 int /*<<< orphan*/  PCIE_PHY_PLL_A_CTRL3 ; 
 int /*<<< orphan*/  PCIE_PHY_RX1_A_CTRL ; 
 int /*<<< orphan*/  PCIE_PHY_RX1_CDR ; 
 int /*<<< orphan*/  PCIE_PHY_RX1_EI ; 
 int /*<<< orphan*/  PCIE_PHY_TX1_A_CTRL1 ; 
 int /*<<< orphan*/  PCIE_PHY_TX1_A_CTRL2 ; 
 int /*<<< orphan*/  PCIE_PHY_TX1_CTRL1 ; 
 int PCIE_PHY_TX1_CTRL1_FORCE_EN ; 
 int /*<<< orphan*/  PCIE_PHY_TX1_CTRL2 ; 
 int /*<<< orphan*/  PCIE_PHY_TX1_CTRL3 ; 
 int /*<<< orphan*/  PCIE_PHY_TX2_A_CTRL2 ; 
 int /*<<< orphan*/  PCIE_PHY_TX2_CTRL2 ; 
 struct ltq_vrx200_pcie_phy_priv* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ltq_vrx200_pcie_phy_common_setup(struct phy *phy)
{
	struct ltq_vrx200_pcie_phy_priv *priv = phy_get_drvdata(phy);

	/* PLL Setting */
	regmap_write(priv->phy_regmap, PCIE_PHY_PLL_A_CTRL1, 0x120e);

	/* increase the bias reference voltage */
	regmap_write(priv->phy_regmap, PCIE_PHY_PLL_A_CTRL2, 0x39d7);
	regmap_write(priv->phy_regmap, PCIE_PHY_PLL_A_CTRL3, 0x0900);

	/* Endcnt */
	regmap_write(priv->phy_regmap, PCIE_PHY_RX1_EI, 0x0004);
	regmap_write(priv->phy_regmap, PCIE_PHY_RX1_A_CTRL, 0x6803);

	regmap_update_bits(priv->phy_regmap, PCIE_PHY_TX1_CTRL1,
			   PCIE_PHY_TX1_CTRL1_FORCE_EN,
			   PCIE_PHY_TX1_CTRL1_FORCE_EN);

	/* predrv_ser_en */
	regmap_write(priv->phy_regmap, PCIE_PHY_TX1_A_CTRL2, 0x0706);

	/* ctrl_lim */
	regmap_write(priv->phy_regmap, PCIE_PHY_TX1_CTRL3, 0x1fff);

	/* ctrl */
	regmap_write(priv->phy_regmap, PCIE_PHY_TX1_A_CTRL1, 0x0810);

	/* predrv_ser_en */
	regmap_update_bits(priv->phy_regmap, PCIE_PHY_TX2_A_CTRL2, 0x7f00,
			   0x4700);

	/* RTERM */
	regmap_write(priv->phy_regmap, PCIE_PHY_TX1_CTRL2, 0x2e00);

	/* Improved 100MHz clock output  */
	regmap_write(priv->phy_regmap, PCIE_PHY_TX2_CTRL2, 0x3096);
	regmap_write(priv->phy_regmap, PCIE_PHY_TX2_A_CTRL2, 0x4707);

	/* Reduced CDR BW to avoid glitches */
	regmap_write(priv->phy_regmap, PCIE_PHY_RX1_CDR, 0x0235);
}