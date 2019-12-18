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
struct net_device {int needs_free_netdev; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * header_ops; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  priv_flags; int /*<<< orphan*/  max_mtu; scalar_t__ min_mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_MAX_MTU ; 
 int /*<<< orphan*/  IFF_TX_SKB_SHARING ; 
 int /*<<< orphan*/  IFF_UNICAST_FLT ; 
 int /*<<< orphan*/  ether_setup (struct net_device*) ; 
 int /*<<< orphan*/  macvlan_ethtool_ops ; 
 int /*<<< orphan*/  macvlan_hard_header_ops ; 
 int /*<<< orphan*/  macvlan_netdev_ops ; 
 int /*<<< orphan*/  netif_keep_dst (struct net_device*) ; 

void macvlan_common_setup(struct net_device *dev)
{
	ether_setup(dev);

	dev->min_mtu		= 0;
	dev->max_mtu		= ETH_MAX_MTU;
	dev->priv_flags	       &= ~IFF_TX_SKB_SHARING;
	netif_keep_dst(dev);
	dev->priv_flags	       |= IFF_UNICAST_FLT;
	dev->netdev_ops		= &macvlan_netdev_ops;
	dev->needs_free_netdev	= true;
	dev->header_ops		= &macvlan_hard_header_ops;
	dev->ethtool_ops	= &macvlan_ethtool_ops;
}