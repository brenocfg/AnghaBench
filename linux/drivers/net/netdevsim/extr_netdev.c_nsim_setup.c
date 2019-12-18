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
struct net_device {int priv_flags; int features; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  hw_features; int /*<<< orphan*/  flags; scalar_t__ tx_queue_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_MAX_MTU ; 
 int IFF_LIVE_ADDR_CHANGE ; 
 int /*<<< orphan*/  IFF_MULTICAST ; 
 int /*<<< orphan*/  IFF_NOARP ; 
 int IFF_NO_QUEUE ; 
 int NETIF_F_FRAGLIST ; 
 int NETIF_F_HIGHDMA ; 
 int NETIF_F_HW_CSUM ; 
 int /*<<< orphan*/  NETIF_F_HW_TC ; 
 int NETIF_F_SG ; 
 int NETIF_F_TSO ; 
 int /*<<< orphan*/  eth_hw_addr_random (struct net_device*) ; 
 int /*<<< orphan*/  ether_setup (struct net_device*) ; 

__attribute__((used)) static void nsim_setup(struct net_device *dev)
{
	ether_setup(dev);
	eth_hw_addr_random(dev);

	dev->tx_queue_len = 0;
	dev->flags |= IFF_NOARP;
	dev->flags &= ~IFF_MULTICAST;
	dev->priv_flags |= IFF_LIVE_ADDR_CHANGE |
			   IFF_NO_QUEUE;
	dev->features |= NETIF_F_HIGHDMA |
			 NETIF_F_SG |
			 NETIF_F_FRAGLIST |
			 NETIF_F_HW_CSUM |
			 NETIF_F_TSO;
	dev->hw_features |= NETIF_F_HW_TC;
	dev->max_mtu = ETH_MAX_MTU;
}