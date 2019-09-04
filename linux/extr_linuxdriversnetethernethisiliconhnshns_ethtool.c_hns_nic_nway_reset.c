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
struct net_device {struct phy_device* phydev; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int genphy_restart_aneg (struct phy_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 

__attribute__((used)) static int hns_nic_nway_reset(struct net_device *netdev)
{
	struct phy_device *phy = netdev->phydev;

	if (!netif_running(netdev))
		return 0;

	if (!phy)
		return -EOPNOTSUPP;

	if (phy->autoneg != AUTONEG_ENABLE)
		return -EINVAL;

	return genphy_restart_aneg(phy);
}