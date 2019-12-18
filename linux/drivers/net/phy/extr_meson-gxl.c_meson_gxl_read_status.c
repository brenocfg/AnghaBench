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
 int /*<<< orphan*/  BANK_WOL ; 
 int EXPANSION_NWAY ; 
 int LPA_LPACK ; 
 int /*<<< orphan*/  LPI_STATUS ; 
 int LPI_STATUS_RSV12 ; 
 int /*<<< orphan*/  MII_EXPANSION ; 
 int /*<<< orphan*/  MII_LPA ; 
 int genphy_aneg_done (struct phy_device*) ; 
 int genphy_read_status (struct phy_device*) ; 
 int genphy_restart_aneg (struct phy_device*) ; 
 int meson_gxl_read_reg (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phydev_dbg (struct phy_device*,char*) ; 

__attribute__((used)) static int meson_gxl_read_status(struct phy_device *phydev)
{
	int ret, wol, lpa, exp;

	if (phydev->autoneg == AUTONEG_ENABLE) {
		ret = genphy_aneg_done(phydev);
		if (ret < 0)
			return ret;
		else if (!ret)
			goto read_status_continue;

		/* Aneg is done, let's check everything is fine */
		wol = meson_gxl_read_reg(phydev, BANK_WOL, LPI_STATUS);
		if (wol < 0)
			return wol;

		lpa = phy_read(phydev, MII_LPA);
		if (lpa < 0)
			return lpa;

		exp = phy_read(phydev, MII_EXPANSION);
		if (exp < 0)
			return exp;

		if (!(wol & LPI_STATUS_RSV12) ||
		    ((exp & EXPANSION_NWAY) && !(lpa & LPA_LPACK))) {
			/* Looks like aneg failed after all */
			phydev_dbg(phydev, "LPA corruption - aneg restart\n");
			return genphy_restart_aneg(phydev);
		}
	}

read_status_continue:
	return genphy_read_status(phydev);
}