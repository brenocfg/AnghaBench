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
struct phy_device {scalar_t__ autoneg; int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; } ;

/* Variables and functions */
 int ADVERTISE_FIBER_1000FULL ; 
 int ADVERTISE_FIBER_1000HALF ; 
 scalar_t__ AUTONEG_ENABLE ; 
 int BMCR_ANENABLE ; 
 int BMCR_ISOLATE ; 
 int LPA_PAUSE_FIBER ; 
 int /*<<< orphan*/  MII_ADVERTISE ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int genphy_restart_aneg (struct phy_device*) ; 
 int genphy_setup_forced (struct phy_device*) ; 
 int linkmode_adv_to_fiber_adv_t (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linkmode_and (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int marvell_config_aneg_fiber(struct phy_device *phydev)
{
	int changed = 0;
	int err;
	int adv, oldadv;

	if (phydev->autoneg != AUTONEG_ENABLE)
		return genphy_setup_forced(phydev);

	/* Only allow advertising what this PHY supports */
	linkmode_and(phydev->advertising, phydev->advertising,
		     phydev->supported);

	/* Setup fiber advertisement */
	adv = phy_read(phydev, MII_ADVERTISE);
	if (adv < 0)
		return adv;

	oldadv = adv;
	adv &= ~(ADVERTISE_FIBER_1000HALF | ADVERTISE_FIBER_1000FULL
		| LPA_PAUSE_FIBER);
	adv |= linkmode_adv_to_fiber_adv_t(phydev->advertising);

	if (adv != oldadv) {
		err = phy_write(phydev, MII_ADVERTISE, adv);
		if (err < 0)
			return err;

		changed = 1;
	}

	if (changed == 0) {
		/* Advertisement hasn't changed, but maybe aneg was never on to
		 * begin with?	Or maybe phy was isolated?
		 */
		int ctl = phy_read(phydev, MII_BMCR);

		if (ctl < 0)
			return ctl;

		if (!(ctl & BMCR_ANENABLE) || (ctl & BMCR_ISOLATE))
			changed = 1; /* do restart aneg */
	}

	/* Only restart aneg if we are advertising something different
	 * than we were before.
	 */
	if (changed > 0)
		changed = genphy_restart_aneg(phydev);

	return changed;
}