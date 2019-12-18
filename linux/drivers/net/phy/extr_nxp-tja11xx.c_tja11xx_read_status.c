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
struct phy_device {scalar_t__ link; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_COMMSTAT ; 
 int MII_COMMSTAT_LINK_UP ; 
 int genphy_update_link (struct phy_device*) ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tja11xx_read_status(struct phy_device *phydev)
{
	int ret;

	ret = genphy_update_link(phydev);
	if (ret)
		return ret;

	if (phydev->link) {
		ret = phy_read(phydev, MII_COMMSTAT);
		if (ret < 0)
			return ret;

		if (!(ret & MII_COMMSTAT_LINK_UP))
			phydev->link = 0;
	}

	return 0;
}