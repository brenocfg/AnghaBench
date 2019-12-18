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
struct reg_default {int def; int /*<<< orphan*/  reg; } ;
struct phy {int dummy; } ;
struct ltq_vrx200_pcie_phy_priv {int /*<<< orphan*/  phy_regmap; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct reg_default const*) ; 
#define  PCIE_PHY_RX1_CTRL1 133 
#define  PCIE_PHY_RX1_CTRL1_LOAD_EN 132 
#define  PCIE_PHY_TX1_CTRL1 131 
#define  PCIE_PHY_TX1_CTRL1_LOAD_EN 130 
 int /*<<< orphan*/  PCIE_PHY_TX1_MOD1 ; 
 int /*<<< orphan*/  PCIE_PHY_TX1_MOD2 ; 
 int /*<<< orphan*/  PCIE_PHY_TX1_MOD3 ; 
#define  PCIE_PHY_TX2_CTRL1 129 
#define  PCIE_PHY_TX2_CTRL1_LOAD_EN 128 
 int /*<<< orphan*/  PCIE_PHY_TX2_MOD1 ; 
 int /*<<< orphan*/  PCIE_PHY_TX2_MOD2 ; 
 int /*<<< orphan*/  PCIE_PHY_TX2_MOD3 ; 
 struct ltq_vrx200_pcie_phy_priv* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void ltq_vrx200_pcie_phy_apply_workarounds(struct phy *phy)
{
	struct ltq_vrx200_pcie_phy_priv *priv = phy_get_drvdata(phy);
	static const struct reg_default slices[] =  {
		{
			.reg = PCIE_PHY_TX1_CTRL1,
			.def = PCIE_PHY_TX1_CTRL1_LOAD_EN,
		},
		{
			.reg = PCIE_PHY_TX2_CTRL1,
			.def = PCIE_PHY_TX2_CTRL1_LOAD_EN,
		},
		{
			.reg = PCIE_PHY_RX1_CTRL1,
			.def = PCIE_PHY_RX1_CTRL1_LOAD_EN,
		}
	};
	int i;

	for (i = 0; i < ARRAY_SIZE(slices); i++) {
		/* enable load_en */
		regmap_update_bits(priv->phy_regmap, slices[i].reg,
				   slices[i].def, slices[i].def);

		udelay(1);

		/* disable load_en */
		regmap_update_bits(priv->phy_regmap, slices[i].reg,
				   slices[i].def, 0x0);
	}

	for (i = 0; i < 5; i++) {
		/* TX2 modulation */
		regmap_write(priv->phy_regmap, PCIE_PHY_TX2_MOD1, 0x1ffe);
		regmap_write(priv->phy_regmap, PCIE_PHY_TX2_MOD2, 0xfffe);
		regmap_write(priv->phy_regmap, PCIE_PHY_TX2_MOD3, 0x0601);
		usleep_range(1000, 2000);
		regmap_write(priv->phy_regmap, PCIE_PHY_TX2_MOD3, 0x0001);

		/* TX1 modulation */
		regmap_write(priv->phy_regmap, PCIE_PHY_TX1_MOD1, 0x1ffe);
		regmap_write(priv->phy_regmap, PCIE_PHY_TX1_MOD2, 0xfffe);
		regmap_write(priv->phy_regmap, PCIE_PHY_TX1_MOD3, 0x0601);
		usleep_range(1000, 2000);
		regmap_write(priv->phy_regmap, PCIE_PHY_TX1_MOD3, 0x0001);
	}
}