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
struct phy_device {scalar_t__ duplex; int pause; int asym_pause; int /*<<< orphan*/  lp_advertising; int /*<<< orphan*/  speed; } ;

/* Variables and functions */
 scalar_t__ DUPLEX_FULL ; 
 scalar_t__ DUPLEX_HALF ; 
 int LPA_PAUSE_ASYM ; 
 int LPA_PAUSE_ASYM_FIBER ; 
 int LPA_PAUSE_CAP ; 
 int LPA_PAUSE_FIBER ; 
 int /*<<< orphan*/  MII_LPA ; 
 int /*<<< orphan*/  MII_M1011_PHY_STATUS ; 
#define  MII_M1011_PHY_STATUS_100 129 
#define  MII_M1011_PHY_STATUS_1000 128 
 int MII_M1011_PHY_STATUS_FULLDUPLEX ; 
 int MII_M1011_PHY_STATUS_SPD_MASK ; 
 int /*<<< orphan*/  MII_STAT1000 ; 
 int /*<<< orphan*/  SPEED_10 ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 int /*<<< orphan*/  fiber_lpa_mod_linkmode_lpa_t (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mii_lpa_to_linkmode_lpa_t (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mii_stat1000_mod_linkmode_lpa_t (int /*<<< orphan*/ ,int) ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int marvell_read_status_page_an(struct phy_device *phydev,
				       int fiber)
{
	int status;
	int lpa;
	int lpagb;

	status = phy_read(phydev, MII_M1011_PHY_STATUS);
	if (status < 0)
		return status;

	lpa = phy_read(phydev, MII_LPA);
	if (lpa < 0)
		return lpa;

	lpagb = phy_read(phydev, MII_STAT1000);
	if (lpagb < 0)
		return lpagb;

	if (status & MII_M1011_PHY_STATUS_FULLDUPLEX)
		phydev->duplex = DUPLEX_FULL;
	else
		phydev->duplex = DUPLEX_HALF;

	status = status & MII_M1011_PHY_STATUS_SPD_MASK;
	phydev->pause = 0;
	phydev->asym_pause = 0;

	switch (status) {
	case MII_M1011_PHY_STATUS_1000:
		phydev->speed = SPEED_1000;
		break;

	case MII_M1011_PHY_STATUS_100:
		phydev->speed = SPEED_100;
		break;

	default:
		phydev->speed = SPEED_10;
		break;
	}

	if (!fiber) {
		mii_lpa_to_linkmode_lpa_t(phydev->lp_advertising, lpa);
		mii_stat1000_mod_linkmode_lpa_t(phydev->lp_advertising, lpagb);

		if (phydev->duplex == DUPLEX_FULL) {
			phydev->pause = lpa & LPA_PAUSE_CAP ? 1 : 0;
			phydev->asym_pause = lpa & LPA_PAUSE_ASYM ? 1 : 0;
		}
	} else {
		/* The fiber link is only 1000M capable */
		fiber_lpa_mod_linkmode_lpa_t(phydev->lp_advertising, lpa);

		if (phydev->duplex == DUPLEX_FULL) {
			if (!(lpa & LPA_PAUSE_FIBER)) {
				phydev->pause = 0;
				phydev->asym_pause = 0;
			} else if ((lpa & LPA_PAUSE_ASYM_FIBER)) {
				phydev->pause = 1;
				phydev->asym_pause = 1;
			} else {
				phydev->pause = 1;
				phydev->asym_pause = 0;
			}
		}
	}
	return 0;
}