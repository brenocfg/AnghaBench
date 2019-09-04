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
struct net_device {int flags; int tx_queue_len; int features; int needs_free_netdev; int /*<<< orphan*/  broadcast; int /*<<< orphan*/  type; int /*<<< orphan*/  addr_len; int /*<<< orphan*/  hard_header_len; int /*<<< orphan*/  watchdog_timeo; int /*<<< orphan*/ * header_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_INFINIBAND ; 
 int /*<<< orphan*/  HZ ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int /*<<< orphan*/  INFINIBAND_ALEN ; 
 int /*<<< orphan*/  IPOIB_HARD_LEN ; 
 int NETIF_F_HIGHDMA ; 
 int NETIF_F_VLAN_CHALLENGED ; 
 int /*<<< orphan*/  ipoib_header_ops ; 
 int ipoib_sendq_size ; 
 int /*<<< orphan*/  ipoib_set_ethtool_ops (struct net_device*) ; 
 int /*<<< orphan*/  ipv4_bcast_addr ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_keep_dst (struct net_device*) ; 

void ipoib_setup_common(struct net_device *dev)
{
	dev->header_ops		 = &ipoib_header_ops;

	ipoib_set_ethtool_ops(dev);

	dev->watchdog_timeo	 = HZ;

	dev->flags		|= IFF_BROADCAST | IFF_MULTICAST;

	dev->hard_header_len	 = IPOIB_HARD_LEN;
	dev->addr_len		 = INFINIBAND_ALEN;
	dev->type		 = ARPHRD_INFINIBAND;
	dev->tx_queue_len	 = ipoib_sendq_size * 2;
	dev->features		 = (NETIF_F_VLAN_CHALLENGED	|
				    NETIF_F_HIGHDMA);
	netif_keep_dst(dev);

	memcpy(dev->broadcast, ipv4_bcast_addr, INFINIBAND_ALEN);

	/*
	 * unregister_netdev always frees the netdev, we use this mode
	 * consistently to unify all the various unregister paths, including
	 * those connected to rtnl_link_ops which require it.
	 */
	dev->needs_free_netdev = true;
}