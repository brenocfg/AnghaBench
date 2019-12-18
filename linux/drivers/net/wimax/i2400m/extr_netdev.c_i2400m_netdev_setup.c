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
struct net_device {int features; int flags; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  watchdog_timeo; int /*<<< orphan*/  tx_queue_len; void* max_mtu; scalar_t__ min_mtu; void* mtu; } ;

/* Variables and functions */
 void* I2400M_MAX_MTU ; 
 int /*<<< orphan*/  I2400M_TX_QLEN ; 
 int /*<<< orphan*/  I2400M_TX_TIMEOUT ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int IFF_NOARP ; 
 int NETIF_F_HIGHDMA ; 
 int NETIF_F_VLAN_CHALLENGED ; 
 int /*<<< orphan*/  d_fnend (int,int /*<<< orphan*/ *,char*,struct net_device*) ; 
 int /*<<< orphan*/  d_fnstart (int,int /*<<< orphan*/ *,char*,struct net_device*) ; 
 int /*<<< orphan*/  ether_setup (struct net_device*) ; 
 int /*<<< orphan*/  i2400m_ethtool_ops ; 
 int /*<<< orphan*/  i2400m_netdev_ops ; 

void i2400m_netdev_setup(struct net_device *net_dev)
{
	d_fnstart(3, NULL, "(net_dev %p)\n", net_dev);
	ether_setup(net_dev);
	net_dev->mtu = I2400M_MAX_MTU;
	net_dev->min_mtu = 0;
	net_dev->max_mtu = I2400M_MAX_MTU;
	net_dev->tx_queue_len = I2400M_TX_QLEN;
	net_dev->features =
		  NETIF_F_VLAN_CHALLENGED
		| NETIF_F_HIGHDMA;
	net_dev->flags =
		IFF_NOARP		/* i2400m is apure IP device */
		& (~IFF_BROADCAST	/* i2400m is P2P */
		   & ~IFF_MULTICAST);
	net_dev->watchdog_timeo = I2400M_TX_TIMEOUT;
	net_dev->netdev_ops = &i2400m_netdev_ops;
	net_dev->ethtool_ops = &i2400m_ethtool_ops;
	d_fnend(3, NULL, "(net_dev %p) = void\n", net_dev);
}