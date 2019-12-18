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
struct phy_device {scalar_t__ autoneg; int /*<<< orphan*/  advertising; int /*<<< orphan*/  adv_old; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int /*<<< orphan*/  __ETHTOOL_DECLARE_LINK_MODE_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adv_tmp ; 
 int /*<<< orphan*/  linkmode_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ linkmode_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int phy_config_aneg (struct phy_device*) ; 
 int phy_poll_aneg_done (struct phy_device*) ; 
 int phy_speed_down_core (struct phy_device*) ; 

int phy_speed_down(struct phy_device *phydev, bool sync)
{
	__ETHTOOL_DECLARE_LINK_MODE_MASK(adv_tmp);
	int ret;

	if (phydev->autoneg != AUTONEG_ENABLE)
		return 0;

	linkmode_copy(adv_tmp, phydev->advertising);

	ret = phy_speed_down_core(phydev);
	if (ret)
		return ret;

	linkmode_copy(phydev->adv_old, adv_tmp);

	if (linkmode_equal(phydev->advertising, adv_tmp))
		return 0;

	ret = phy_config_aneg(phydev);
	if (ret)
		return ret;

	return sync ? phy_poll_aneg_done(phydev) : 0;
}