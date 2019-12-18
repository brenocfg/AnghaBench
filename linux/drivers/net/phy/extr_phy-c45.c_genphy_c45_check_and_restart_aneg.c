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
struct phy_device {int dummy; } ;

/* Variables and functions */
 int MDIO_AN_CTRL1_ENABLE ; 
 int /*<<< orphan*/  MDIO_CTRL1 ; 
 int /*<<< orphan*/  MDIO_MMD_AN ; 
 int genphy_c45_restart_aneg (struct phy_device*) ; 
 int phy_read_mmd (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int genphy_c45_check_and_restart_aneg(struct phy_device *phydev, bool restart)
{
	int ret = 0;

	if (!restart) {
		/* Configure and restart aneg if it wasn't set before */
		ret = phy_read_mmd(phydev, MDIO_MMD_AN, MDIO_CTRL1);
		if (ret < 0)
			return ret;

		if (!(ret & MDIO_AN_CTRL1_ENABLE))
			restart = true;
	}

	if (restart)
		ret = genphy_c45_restart_aneg(phydev);

	return ret;
}