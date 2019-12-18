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
struct phy_device {scalar_t__ autoneg; int /*<<< orphan*/  lp_advertising; scalar_t__ is_gigabit_capable; int /*<<< orphan*/  autoneg_complete; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int CTL1000_ENABLE_MASTER ; 
 int ENOLINK ; 
 int LPA_1000MSFAIL ; 
 int /*<<< orphan*/  MII_CTRL1000 ; 
 int /*<<< orphan*/  MII_LPA ; 
 int /*<<< orphan*/  MII_STAT1000 ; 
 int /*<<< orphan*/  linkmode_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mii_lpa_mod_linkmode_lpa_t (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mii_stat1000_mod_linkmode_lpa_t (int /*<<< orphan*/ ,int) ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phydev_err (struct phy_device*,char*) ; 

int genphy_read_lpa(struct phy_device *phydev)
{
	int lpa, lpagb;

	if (phydev->autoneg == AUTONEG_ENABLE) {
		if (!phydev->autoneg_complete) {
			mii_stat1000_mod_linkmode_lpa_t(phydev->lp_advertising,
							0);
			mii_lpa_mod_linkmode_lpa_t(phydev->lp_advertising, 0);
			return 0;
		}

		if (phydev->is_gigabit_capable) {
			lpagb = phy_read(phydev, MII_STAT1000);
			if (lpagb < 0)
				return lpagb;

			if (lpagb & LPA_1000MSFAIL) {
				int adv = phy_read(phydev, MII_CTRL1000);

				if (adv < 0)
					return adv;

				if (adv & CTL1000_ENABLE_MASTER)
					phydev_err(phydev, "Master/Slave resolution failed, maybe conflicting manual settings?\n");
				else
					phydev_err(phydev, "Master/Slave resolution failed\n");
				return -ENOLINK;
			}

			mii_stat1000_mod_linkmode_lpa_t(phydev->lp_advertising,
							lpagb);
		}

		lpa = phy_read(phydev, MII_LPA);
		if (lpa < 0)
			return lpa;

		mii_lpa_mod_linkmode_lpa_t(phydev->lp_advertising, lpa);
	} else {
		linkmode_zero(phydev->lp_advertising);
	}

	return 0;
}