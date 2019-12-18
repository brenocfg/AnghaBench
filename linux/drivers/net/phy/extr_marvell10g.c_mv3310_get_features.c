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
struct phy_device {int /*<<< orphan*/  supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_2500baseT_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_5000baseT_Full_BIT ; 
 int /*<<< orphan*/  MDIO_MMD_PMAPMD ; 
 int /*<<< orphan*/  MDIO_PMA_NG_EXTABLE ; 
 int MDIO_PMA_NG_EXTABLE_2_5GBT ; 
 int MDIO_PMA_NG_EXTABLE_5GBT ; 
 int genphy_c45_pma_read_abilities (struct phy_device*) ; 
 int /*<<< orphan*/  linkmode_mod_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mv3310_has_pma_ngbaset_quirk (struct phy_device*) ; 
 int phy_read_mmd (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mv3310_get_features(struct phy_device *phydev)
{
	int ret, val;

	ret = genphy_c45_pma_read_abilities(phydev);
	if (ret)
		return ret;

	if (mv3310_has_pma_ngbaset_quirk(phydev)) {
		val = phy_read_mmd(phydev, MDIO_MMD_PMAPMD,
				   MDIO_PMA_NG_EXTABLE);
		if (val < 0)
			return val;

		linkmode_mod_bit(ETHTOOL_LINK_MODE_2500baseT_Full_BIT,
				 phydev->supported,
				 val & MDIO_PMA_NG_EXTABLE_2_5GBT);

		linkmode_mod_bit(ETHTOOL_LINK_MODE_5000baseT_Full_BIT,
				 phydev->supported,
				 val & MDIO_PMA_NG_EXTABLE_5GBT);
	}

	return 0;
}