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
struct ucc_geth_private {struct phy_device* phydev; } ;
struct phy_device {int dummy; } ;
struct net_device {int dummy; } ;
struct ethtool_link_ksettings {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 struct ucc_geth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_ethtool_ksettings_get (struct phy_device*,struct ethtool_link_ksettings*) ; 

__attribute__((used)) static int
uec_get_ksettings(struct net_device *netdev, struct ethtool_link_ksettings *cmd)
{
	struct ucc_geth_private *ugeth = netdev_priv(netdev);
	struct phy_device *phydev = ugeth->phydev;

	if (!phydev)
		return -ENODEV;

	phy_ethtool_ksettings_get(phydev, cmd);

	return 0;
}