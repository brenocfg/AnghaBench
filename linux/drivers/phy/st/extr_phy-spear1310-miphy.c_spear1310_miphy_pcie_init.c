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
typedef  int /*<<< orphan*/  u32 ;
struct spear1310_miphy_priv {int id; int /*<<< orphan*/  misc; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SPEAR1310_PCIE_CFG_MASK (int) ; 
 int /*<<< orphan*/  SPEAR1310_PCIE_CFG_VAL (int) ; 
 int /*<<< orphan*/  SPEAR1310_PCIE_MIPHY_CFG_1 ; 
 int /*<<< orphan*/  SPEAR1310_PCIE_SATA_CFG ; 
 int /*<<< orphan*/  SPEAR1310_PCIE_SATA_MIPHY_CFG_PCIE ; 
 int /*<<< orphan*/  SPEAR1310_PCIE_SATA_MIPHY_CFG_PCIE_MASK ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spear1310_miphy_pcie_init(struct spear1310_miphy_priv *priv)
{
	u32 val;

	regmap_update_bits(priv->misc, SPEAR1310_PCIE_MIPHY_CFG_1,
			   SPEAR1310_PCIE_SATA_MIPHY_CFG_PCIE_MASK,
			   SPEAR1310_PCIE_SATA_MIPHY_CFG_PCIE);

	switch (priv->id) {
	case 0:
		val = SPEAR1310_PCIE_CFG_VAL(0);
		break;
	case 1:
		val = SPEAR1310_PCIE_CFG_VAL(1);
		break;
	case 2:
		val = SPEAR1310_PCIE_CFG_VAL(2);
		break;
	default:
		return -EINVAL;
	}

	regmap_update_bits(priv->misc, SPEAR1310_PCIE_SATA_CFG,
			   SPEAR1310_PCIE_CFG_MASK(priv->id), val);

	return 0;
}