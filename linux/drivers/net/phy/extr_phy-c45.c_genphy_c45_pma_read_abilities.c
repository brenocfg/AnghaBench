#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int devices_in_package; } ;
struct phy_device {int /*<<< orphan*/  supported; TYPE_1__ c45_ids; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_10000baseER_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_10000baseKR_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_10000baseKX4_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_10000baseLRM_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_10000baseLR_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_10000baseSR_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_10000baseT_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_1000baseKX_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_1000baseT_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_100baseT_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_100baseT_Half_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_10baseT_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_10baseT_Half_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_2500baseT_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_5000baseT_Full_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_Autoneg_BIT ; 
 int MDIO_AN_STAT1_ABLE ; 
 int MDIO_DEVS_AN ; 
 int /*<<< orphan*/  MDIO_MMD_AN ; 
 int /*<<< orphan*/  MDIO_MMD_PMAPMD ; 
 int /*<<< orphan*/  MDIO_PMA_EXTABLE ; 
 int MDIO_PMA_EXTABLE_1000BKX ; 
 int MDIO_PMA_EXTABLE_1000BT ; 
 int MDIO_PMA_EXTABLE_100BTX ; 
 int MDIO_PMA_EXTABLE_10BT ; 
 int MDIO_PMA_EXTABLE_10GBKR ; 
 int MDIO_PMA_EXTABLE_10GBKX4 ; 
 int MDIO_PMA_EXTABLE_10GBLRM ; 
 int MDIO_PMA_EXTABLE_10GBT ; 
 int MDIO_PMA_EXTABLE_NBT ; 
 int /*<<< orphan*/  MDIO_PMA_NG_EXTABLE ; 
 int MDIO_PMA_NG_EXTABLE_2_5GBT ; 
 int MDIO_PMA_NG_EXTABLE_5GBT ; 
 int MDIO_PMA_STAT2_10GBER ; 
 int MDIO_PMA_STAT2_10GBLR ; 
 int MDIO_PMA_STAT2_10GBSR ; 
 int MDIO_PMA_STAT2_EXTABLE ; 
 int /*<<< orphan*/  MDIO_STAT1 ; 
 int /*<<< orphan*/  MDIO_STAT2 ; 
 int /*<<< orphan*/  linkmode_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linkmode_mod_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  linkmode_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int phy_read_mmd (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int genphy_c45_pma_read_abilities(struct phy_device *phydev)
{
	int val;

	linkmode_clear_bit(ETHTOOL_LINK_MODE_Autoneg_BIT, phydev->supported);
	if (phydev->c45_ids.devices_in_package & MDIO_DEVS_AN) {
		val = phy_read_mmd(phydev, MDIO_MMD_AN, MDIO_STAT1);
		if (val < 0)
			return val;

		if (val & MDIO_AN_STAT1_ABLE)
			linkmode_set_bit(ETHTOOL_LINK_MODE_Autoneg_BIT,
					 phydev->supported);
	}

	val = phy_read_mmd(phydev, MDIO_MMD_PMAPMD, MDIO_STAT2);
	if (val < 0)
		return val;

	linkmode_mod_bit(ETHTOOL_LINK_MODE_10000baseSR_Full_BIT,
			 phydev->supported,
			 val & MDIO_PMA_STAT2_10GBSR);

	linkmode_mod_bit(ETHTOOL_LINK_MODE_10000baseLR_Full_BIT,
			 phydev->supported,
			 val & MDIO_PMA_STAT2_10GBLR);

	linkmode_mod_bit(ETHTOOL_LINK_MODE_10000baseER_Full_BIT,
			 phydev->supported,
			 val & MDIO_PMA_STAT2_10GBER);

	if (val & MDIO_PMA_STAT2_EXTABLE) {
		val = phy_read_mmd(phydev, MDIO_MMD_PMAPMD, MDIO_PMA_EXTABLE);
		if (val < 0)
			return val;

		linkmode_mod_bit(ETHTOOL_LINK_MODE_10000baseLRM_Full_BIT,
				 phydev->supported,
				 val & MDIO_PMA_EXTABLE_10GBLRM);
		linkmode_mod_bit(ETHTOOL_LINK_MODE_10000baseT_Full_BIT,
				 phydev->supported,
				 val & MDIO_PMA_EXTABLE_10GBT);
		linkmode_mod_bit(ETHTOOL_LINK_MODE_10000baseKX4_Full_BIT,
				 phydev->supported,
				 val & MDIO_PMA_EXTABLE_10GBKX4);
		linkmode_mod_bit(ETHTOOL_LINK_MODE_10000baseKR_Full_BIT,
				 phydev->supported,
				 val & MDIO_PMA_EXTABLE_10GBKR);
		linkmode_mod_bit(ETHTOOL_LINK_MODE_1000baseT_Full_BIT,
				 phydev->supported,
				 val & MDIO_PMA_EXTABLE_1000BT);
		linkmode_mod_bit(ETHTOOL_LINK_MODE_1000baseKX_Full_BIT,
				 phydev->supported,
				 val & MDIO_PMA_EXTABLE_1000BKX);

		linkmode_mod_bit(ETHTOOL_LINK_MODE_100baseT_Full_BIT,
				 phydev->supported,
				 val & MDIO_PMA_EXTABLE_100BTX);
		linkmode_mod_bit(ETHTOOL_LINK_MODE_100baseT_Half_BIT,
				 phydev->supported,
				 val & MDIO_PMA_EXTABLE_100BTX);

		linkmode_mod_bit(ETHTOOL_LINK_MODE_10baseT_Full_BIT,
				 phydev->supported,
				 val & MDIO_PMA_EXTABLE_10BT);
		linkmode_mod_bit(ETHTOOL_LINK_MODE_10baseT_Half_BIT,
				 phydev->supported,
				 val & MDIO_PMA_EXTABLE_10BT);

		if (val & MDIO_PMA_EXTABLE_NBT) {
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
	}

	return 0;
}