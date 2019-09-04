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
struct net_device {scalar_t__ phydev; } ;
struct ethtool_link_ksettings {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int phy_ethtool_ksettings_set (scalar_t__,struct ethtool_link_ksettings const*) ; 

__attribute__((used)) static int hns3_set_link_ksettings(struct net_device *netdev,
				   const struct ethtool_link_ksettings *cmd)
{
	/* Only support ksettings_set for netdev with phy attached for now */
	if (netdev->phydev)
		return phy_ethtool_ksettings_set(netdev->phydev, cmd);

	return -EOPNOTSUPP;
}