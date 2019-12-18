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
struct ethtool_wolinfo {scalar_t__ wolopts; scalar_t__ supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  phy_ethtool_get_wol (scalar_t__,struct ethtool_wolinfo*) ; 

void phylink_ethtool_get_wol(struct phylink *pl, struct ethtool_wolinfo *wol)
{
	ASSERT_RTNL();

	wol->supported = 0;
	wol->wolopts = 0;

	if (pl->phydev)
		phy_ethtool_get_wol(pl->phydev, wol);
}