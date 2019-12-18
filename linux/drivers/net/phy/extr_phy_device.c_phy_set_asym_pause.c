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
struct phy_device {scalar_t__ autoneg; int /*<<< orphan*/  advertising; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_Asym_Pause_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_Pause_BIT ; 
 int /*<<< orphan*/  __ETHTOOL_DECLARE_LINK_MODE_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linkmode_change_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linkmode_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linkmode_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linkmode_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linkmode_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oldadv ; 
 int /*<<< orphan*/  phy_start_aneg (struct phy_device*) ; 

void phy_set_asym_pause(struct phy_device *phydev, bool rx, bool tx)
{
	__ETHTOOL_DECLARE_LINK_MODE_MASK(oldadv);

	linkmode_copy(oldadv, phydev->advertising);

	linkmode_clear_bit(ETHTOOL_LINK_MODE_Pause_BIT,
			   phydev->advertising);
	linkmode_clear_bit(ETHTOOL_LINK_MODE_Asym_Pause_BIT,
			   phydev->advertising);

	if (rx) {
		linkmode_set_bit(ETHTOOL_LINK_MODE_Pause_BIT,
				 phydev->advertising);
		linkmode_set_bit(ETHTOOL_LINK_MODE_Asym_Pause_BIT,
				 phydev->advertising);
	}

	if (tx)
		linkmode_change_bit(ETHTOOL_LINK_MODE_Asym_Pause_BIT,
				    phydev->advertising);

	if (!linkmode_equal(oldadv, phydev->advertising) &&
	    phydev->autoneg)
		phy_start_aneg(phydev);
}