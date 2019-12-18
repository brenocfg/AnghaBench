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
struct spear1340_miphy_priv {int /*<<< orphan*/  misc; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPEAR1340_PCIE_MIPHY_CFG ; 
 int /*<<< orphan*/  SPEAR1340_PCIE_MIPHY_CFG_MASK ; 
 int /*<<< orphan*/  SPEAR1340_PCIE_SATA_CFG ; 
 int /*<<< orphan*/  SPEAR1340_PCIE_SATA_CFG_MASK ; 
 int /*<<< orphan*/  SPEAR1340_PCIE_SATA_MIPHY_CFG_SATA_25M_CRYSTAL_CLK ; 
 int /*<<< orphan*/  SPEAR1340_PCM_CFG ; 
 int /*<<< orphan*/  SPEAR1340_PCM_CFG_SATA_POWER_EN ; 
 int /*<<< orphan*/  SPEAR1340_PERIP1_SW_RSATA ; 
 int /*<<< orphan*/  SPEAR1340_PERIP1_SW_RST ; 
 int /*<<< orphan*/  SPEAR1340_SATA_CFG_VAL ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spear1340_miphy_sata_init(struct spear1340_miphy_priv *priv)
{
	regmap_update_bits(priv->misc, SPEAR1340_PCIE_SATA_CFG,
			   SPEAR1340_PCIE_SATA_CFG_MASK,
			   SPEAR1340_SATA_CFG_VAL);
	regmap_update_bits(priv->misc, SPEAR1340_PCIE_MIPHY_CFG,
			   SPEAR1340_PCIE_MIPHY_CFG_MASK,
			   SPEAR1340_PCIE_SATA_MIPHY_CFG_SATA_25M_CRYSTAL_CLK);
	/* Switch on sata power domain */
	regmap_update_bits(priv->misc, SPEAR1340_PCM_CFG,
			   SPEAR1340_PCM_CFG_SATA_POWER_EN,
			   SPEAR1340_PCM_CFG_SATA_POWER_EN);
	/* Wait for SATA power domain on */
	msleep(20);

	/* Disable PCIE SATA Controller reset */
	regmap_update_bits(priv->misc, SPEAR1340_PERIP1_SW_RST,
			   SPEAR1340_PERIP1_SW_RSATA, 0);
	/* Wait for SATA reset de-assert completion */
	msleep(20);

	return 0;
}