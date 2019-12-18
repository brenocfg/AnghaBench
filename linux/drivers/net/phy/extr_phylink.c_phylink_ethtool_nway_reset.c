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
struct phylink {scalar_t__ phydev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int phy_restart_aneg (scalar_t__) ; 
 int /*<<< orphan*/  phylink_mac_an_restart (struct phylink*) ; 

int phylink_ethtool_nway_reset(struct phylink *pl)
{
	int ret = 0;

	ASSERT_RTNL();

	if (pl->phydev)
		ret = phy_restart_aneg(pl->phydev);
	phylink_mac_an_restart(pl);

	return ret;
}