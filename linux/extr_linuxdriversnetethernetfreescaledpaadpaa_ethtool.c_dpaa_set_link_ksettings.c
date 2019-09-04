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
 int ENODEV ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,...) ; 
 int phy_ethtool_ksettings_set (int /*<<< orphan*/ ,struct ethtool_link_ksettings const*) ; 

__attribute__((used)) static int dpaa_set_link_ksettings(struct net_device *net_dev,
				   const struct ethtool_link_ksettings *cmd)
{
	int err;

	if (!net_dev->phydev) {
		netdev_err(net_dev, "phy device not initialized\n");
		return -ENODEV;
	}

	err = phy_ethtool_ksettings_set(net_dev->phydev, cmd);
	if (err < 0)
		netdev_err(net_dev, "phy_ethtool_ksettings_set() = %d\n", err);

	return err;
}