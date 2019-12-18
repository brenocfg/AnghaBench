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
struct phy_device {scalar_t__ autoneg; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int BMCR_ANENABLE ; 
 int BMCR_ISOLATE ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int genphy_config_advert (struct phy_device*) ; 
 scalar_t__ genphy_config_eee_advert (struct phy_device*) ; 
 int genphy_restart_aneg (struct phy_device*) ; 
 int genphy_setup_forced (struct phy_device*) ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 

int __genphy_config_aneg(struct phy_device *phydev, bool changed)
{
	int err;

	if (genphy_config_eee_advert(phydev))
		changed = true;

	if (AUTONEG_ENABLE != phydev->autoneg)
		return genphy_setup_forced(phydev);

	err = genphy_config_advert(phydev);
	if (err < 0) /* error */
		return err;
	else if (err)
		changed = true;

	if (!changed) {
		/* Advertisement hasn't changed, but maybe aneg was never on to
		 * begin with?  Or maybe phy was isolated?
		 */
		int ctl = phy_read(phydev, MII_BMCR);

		if (ctl < 0)
			return ctl;

		if (!(ctl & BMCR_ANENABLE) || (ctl & BMCR_ISOLATE))
			changed = true; /* do restart aneg */
	}

	/* Only restart aneg if we are advertising something different
	 * than we were before.
	 */
	return changed ? genphy_restart_aneg(phydev) : 0;
}