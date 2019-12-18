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
struct phy_device {scalar_t__ autoneg; scalar_t__ asym_pause; scalar_t__ pause; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int /*<<< orphan*/  DUPLEX_UNKNOWN ; 
 int /*<<< orphan*/  SPEED_UNKNOWN ; 
 int genphy_c45_read_link (struct phy_device*) ; 
 int genphy_c45_read_lpa (struct phy_device*) ; 
 int genphy_c45_read_pma (struct phy_device*) ; 
 int /*<<< orphan*/  phy_resolve_aneg_linkmode (struct phy_device*) ; 

int genphy_c45_read_status(struct phy_device *phydev)
{
	int ret;

	ret = genphy_c45_read_link(phydev);
	if (ret)
		return ret;

	phydev->speed = SPEED_UNKNOWN;
	phydev->duplex = DUPLEX_UNKNOWN;
	phydev->pause = 0;
	phydev->asym_pause = 0;

	if (phydev->autoneg == AUTONEG_ENABLE) {
		ret = genphy_c45_read_lpa(phydev);
		if (ret)
			return ret;

		phy_resolve_aneg_linkmode(phydev);
	} else {
		ret = genphy_c45_read_pma(phydev);
	}

	return ret;
}