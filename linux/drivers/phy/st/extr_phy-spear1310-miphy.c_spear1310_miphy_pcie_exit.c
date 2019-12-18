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
struct spear1310_miphy_priv {int /*<<< orphan*/  misc; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPEAR1310_PCIE_CFG_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPEAR1310_PCIE_MIPHY_CFG_1 ; 
 int /*<<< orphan*/  SPEAR1310_PCIE_SATA_CFG ; 
 int /*<<< orphan*/  SPEAR1310_PCIE_SATA_MIPHY_CFG_PCIE_MASK ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spear1310_miphy_pcie_exit(struct spear1310_miphy_priv *priv)
{
	regmap_update_bits(priv->misc, SPEAR1310_PCIE_SATA_CFG,
			   SPEAR1310_PCIE_CFG_MASK(priv->id), 0);

	regmap_update_bits(priv->misc, SPEAR1310_PCIE_MIPHY_CFG_1,
			   SPEAR1310_PCIE_SATA_MIPHY_CFG_PCIE_MASK, 0);

	return 0;
}