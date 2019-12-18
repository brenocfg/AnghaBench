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
struct phy_device {int link; int autoneg_complete; scalar_t__ autoneg; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int BMCR_ANRESTART ; 
 int BMSR_ANEGCOMPLETE ; 
 int BMSR_LSTATUS ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  MII_BMSR ; 
 int /*<<< orphan*/  phy_polling_mode (struct phy_device*) ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 

int genphy_update_link(struct phy_device *phydev)
{
	int status = 0, bmcr;

	bmcr = phy_read(phydev, MII_BMCR);
	if (bmcr < 0)
		return bmcr;

	/* Autoneg is being started, therefore disregard BMSR value and
	 * report link as down.
	 */
	if (bmcr & BMCR_ANRESTART)
		goto done;

	/* The link state is latched low so that momentary link
	 * drops can be detected. Do not double-read the status
	 * in polling mode to detect such short link drops.
	 */
	if (!phy_polling_mode(phydev)) {
		status = phy_read(phydev, MII_BMSR);
		if (status < 0)
			return status;
		else if (status & BMSR_LSTATUS)
			goto done;
	}

	/* Read link and autonegotiation status */
	status = phy_read(phydev, MII_BMSR);
	if (status < 0)
		return status;
done:
	phydev->link = status & BMSR_LSTATUS ? 1 : 0;
	phydev->autoneg_complete = status & BMSR_ANEGCOMPLETE ? 1 : 0;

	/* Consider the case that autoneg was started and "aneg complete"
	 * bit has been reset, but "link up" bit not yet.
	 */
	if (phydev->autoneg == AUTONEG_ENABLE && !phydev->autoneg_complete)
		phydev->link = 0;

	return 0;
}