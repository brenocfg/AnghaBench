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
struct phy_device {int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; } ;

/* Variables and functions */
 int ADVERTISE_1000FULL ; 
 int ADVERTISE_1000HALF ; 
 int ADVERTISE_100BASE4 ; 
 int ADVERTISE_ALL ; 
 int ADVERTISE_PAUSE_ASYM ; 
 int ADVERTISE_PAUSE_CAP ; 
 int BMSR_ESTATEN ; 
 int /*<<< orphan*/  MII_ADVERTISE ; 
 int /*<<< orphan*/  MII_BMSR ; 
 int /*<<< orphan*/  MII_CTRL1000 ; 
 int /*<<< orphan*/  linkmode_adv_to_mii_adv_t (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linkmode_adv_to_mii_ctrl1000_t (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linkmode_and (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int phy_modify_changed (struct phy_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int genphy_config_advert(struct phy_device *phydev)
{
	int err, bmsr, changed = 0;
	u32 adv;

	/* Only allow advertising what this PHY supports */
	linkmode_and(phydev->advertising, phydev->advertising,
		     phydev->supported);

	adv = linkmode_adv_to_mii_adv_t(phydev->advertising);

	/* Setup standard advertisement */
	err = phy_modify_changed(phydev, MII_ADVERTISE,
				 ADVERTISE_ALL | ADVERTISE_100BASE4 |
				 ADVERTISE_PAUSE_CAP | ADVERTISE_PAUSE_ASYM,
				 adv);
	if (err < 0)
		return err;
	if (err > 0)
		changed = 1;

	bmsr = phy_read(phydev, MII_BMSR);
	if (bmsr < 0)
		return bmsr;

	/* Per 802.3-2008, Section 22.2.4.2.16 Extended status all
	 * 1000Mbits/sec capable PHYs shall have the BMSR_ESTATEN bit set to a
	 * logical 1.
	 */
	if (!(bmsr & BMSR_ESTATEN))
		return changed;

	adv = linkmode_adv_to_mii_ctrl1000_t(phydev->advertising);

	err = phy_modify_changed(phydev, MII_CTRL1000,
				 ADVERTISE_1000FULL | ADVERTISE_1000HALF,
				 adv);
	if (err < 0)
		return err;
	if (err > 0)
		changed = 1;

	return changed;
}