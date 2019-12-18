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
 int /*<<< orphan*/  SPEAR1340_PCM_CFG ; 
 int /*<<< orphan*/  SPEAR1340_PCM_CFG_SATA_POWER_EN ; 
 int /*<<< orphan*/  SPEAR1340_PERIP1_SW_RSATA ; 
 int /*<<< orphan*/  SPEAR1340_PERIP1_SW_RST ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spear1340_miphy_sata_exit(struct spear1340_miphy_priv *priv)
{
	regmap_update_bits(priv->misc, SPEAR1340_PCIE_SATA_CFG,
			   SPEAR1340_PCIE_SATA_CFG_MASK, 0);
	regmap_update_bits(priv->misc, SPEAR1340_PCIE_MIPHY_CFG,
			   SPEAR1340_PCIE_MIPHY_CFG_MASK, 0);

	/* Enable PCIE SATA Controller reset */
	regmap_update_bits(priv->misc, SPEAR1340_PERIP1_SW_RST,
			   SPEAR1340_PERIP1_SW_RSATA,
			   SPEAR1340_PERIP1_SW_RSATA);
	/* Wait for SATA power domain off */
	msleep(20);
	/* Switch off sata power domain */
	regmap_update_bits(priv->misc, SPEAR1340_PCM_CFG,
			   SPEAR1340_PCM_CFG_SATA_POWER_EN, 0);
	/* Wait for SATA reset assert completion */
	msleep(20);

	return 0;
}