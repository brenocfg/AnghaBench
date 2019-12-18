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
struct net_device {int dummy; } ;
struct macvlan_dev {int /*<<< orphan*/  lowerdev; } ;
struct ethtool_link_ksettings {int dummy; } ;

/* Variables and functions */
 int __ethtool_get_link_ksettings (int /*<<< orphan*/ ,struct ethtool_link_ksettings*) ; 
 struct macvlan_dev* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int macvlan_ethtool_get_link_ksettings(struct net_device *dev,
					      struct ethtool_link_ksettings *cmd)
{
	const struct macvlan_dev *vlan = netdev_priv(dev);

	return __ethtool_get_link_ksettings(vlan->lowerdev, cmd);
}