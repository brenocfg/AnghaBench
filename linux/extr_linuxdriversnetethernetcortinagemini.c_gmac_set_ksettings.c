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
struct net_device {int /*<<< orphan*/  phydev; } ;
struct ethtool_link_ksettings {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int phy_ethtool_ksettings_set (int /*<<< orphan*/ ,struct ethtool_link_ksettings const*) ; 

__attribute__((used)) static int gmac_set_ksettings(struct net_device *netdev,
			      const struct ethtool_link_ksettings *cmd)
{
	if (!netdev->phydev)
		return -ENXIO;
	return phy_ethtool_ksettings_set(netdev->phydev, cmd);
}