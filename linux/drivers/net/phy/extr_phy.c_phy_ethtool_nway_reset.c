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
struct phy_device {int /*<<< orphan*/  drv; } ;
struct net_device {struct phy_device* phydev; } ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 int phy_restart_aneg (struct phy_device*) ; 

int phy_ethtool_nway_reset(struct net_device *ndev)
{
	struct phy_device *phydev = ndev->phydev;

	if (!phydev)
		return -ENODEV;

	if (!phydev->drv)
		return -EIO;

	return phy_restart_aneg(phydev);
}