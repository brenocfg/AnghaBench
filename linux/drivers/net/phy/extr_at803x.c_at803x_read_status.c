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
struct phy_device {int link; scalar_t__ autoneg; scalar_t__ autoneg_complete; int /*<<< orphan*/  mdix; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; scalar_t__ asym_pause; scalar_t__ pause; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT803X_SPECIFIC_STATUS ; 
 int AT803X_SS_DUPLEX ; 
 int AT803X_SS_MDIX ; 
#define  AT803X_SS_SPEED_10 130 
#define  AT803X_SS_SPEED_100 129 
#define  AT803X_SS_SPEED_1000 128 
 int AT803X_SS_SPEED_DUPLEX_RESOLVED ; 
 int AT803X_SS_SPEED_MASK ; 
 scalar_t__ AUTONEG_ENABLE ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_HALF ; 
 int /*<<< orphan*/  DUPLEX_UNKNOWN ; 
 int /*<<< orphan*/  ETH_TP_MDI ; 
 int /*<<< orphan*/  ETH_TP_MDI_X ; 
 int /*<<< orphan*/  SPEED_10 ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 int /*<<< orphan*/  SPEED_UNKNOWN ; 
 int genphy_read_lpa (struct phy_device*) ; 
 int genphy_update_link (struct phy_device*) ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_resolve_aneg_pause (struct phy_device*) ; 

__attribute__((used)) static int at803x_read_status(struct phy_device *phydev)
{
	int ss, err, old_link = phydev->link;

	/* Update the link, but return if there was an error */
	err = genphy_update_link(phydev);
	if (err)
		return err;

	/* why bother the PHY if nothing can have changed */
	if (phydev->autoneg == AUTONEG_ENABLE && old_link && phydev->link)
		return 0;

	phydev->speed = SPEED_UNKNOWN;
	phydev->duplex = DUPLEX_UNKNOWN;
	phydev->pause = 0;
	phydev->asym_pause = 0;

	err = genphy_read_lpa(phydev);
	if (err < 0)
		return err;

	/* Read the AT8035 PHY-Specific Status register, which indicates the
	 * speed and duplex that the PHY is actually using, irrespective of
	 * whether we are in autoneg mode or not.
	 */
	ss = phy_read(phydev, AT803X_SPECIFIC_STATUS);
	if (ss < 0)
		return ss;

	if (ss & AT803X_SS_SPEED_DUPLEX_RESOLVED) {
		switch (ss & AT803X_SS_SPEED_MASK) {
		case AT803X_SS_SPEED_10:
			phydev->speed = SPEED_10;
			break;
		case AT803X_SS_SPEED_100:
			phydev->speed = SPEED_100;
			break;
		case AT803X_SS_SPEED_1000:
			phydev->speed = SPEED_1000;
			break;
		}
		if (ss & AT803X_SS_DUPLEX)
			phydev->duplex = DUPLEX_FULL;
		else
			phydev->duplex = DUPLEX_HALF;
		if (ss & AT803X_SS_MDIX)
			phydev->mdix = ETH_TP_MDI_X;
		else
			phydev->mdix = ETH_TP_MDI;
	}

	if (phydev->autoneg == AUTONEG_ENABLE && phydev->autoneg_complete)
		phy_resolve_aneg_pause(phydev);

	return 0;
}