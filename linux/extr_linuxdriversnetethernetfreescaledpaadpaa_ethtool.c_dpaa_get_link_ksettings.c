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
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*) ; 
 int /*<<< orphan*/  phy_ethtool_ksettings_get (int /*<<< orphan*/ ,struct ethtool_link_ksettings*) ; 

__attribute__((used)) static int dpaa_get_link_ksettings(struct net_device *net_dev,
				   struct ethtool_link_ksettings *cmd)
{
	if (!net_dev->phydev) {
		netdev_dbg(net_dev, "phy device not initialized\n");
		return 0;
	}

	phy_ethtool_ksettings_get(net_dev->phydev, cmd);

	return 0;
}