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
struct w90p910_ether {int /*<<< orphan*/  mii; } ;
struct net_device {int dummy; } ;
struct ethtool_link_ksettings {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mii_ethtool_get_link_ksettings (int /*<<< orphan*/ *,struct ethtool_link_ksettings*) ; 
 struct w90p910_ether* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int w90p910_get_link_ksettings(struct net_device *dev,
				      struct ethtool_link_ksettings *cmd)
{
	struct w90p910_ether *ether = netdev_priv(dev);

	mii_ethtool_get_link_ksettings(&ether->mii, cmd);

	return 0;
}