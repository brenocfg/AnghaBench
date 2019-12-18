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
struct net_device {int tx_queue_len; int flags; int /*<<< orphan*/  priv_destructor; int /*<<< orphan*/  type; scalar_t__ addr_len; int /*<<< orphan*/  mtu; int /*<<< orphan*/  hard_header_len; int /*<<< orphan*/  features; int /*<<< orphan*/ * netdev_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_PPP ; 
 int IFF_MULTICAST ; 
 int IFF_NOARP ; 
 int IFF_POINTOPOINT ; 
 int /*<<< orphan*/  NETIF_F_LLTX ; 
 int /*<<< orphan*/  PPP_HDRLEN ; 
 int /*<<< orphan*/  PPP_MRU ; 
 int /*<<< orphan*/  SET_NETDEV_DEVTYPE (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_keep_dst (struct net_device*) ; 
 int /*<<< orphan*/  ppp_dev_priv_destructor ; 
 int /*<<< orphan*/  ppp_netdev_ops ; 
 int /*<<< orphan*/  ppp_type ; 

__attribute__((used)) static void ppp_setup(struct net_device *dev)
{
	dev->netdev_ops = &ppp_netdev_ops;
	SET_NETDEV_DEVTYPE(dev, &ppp_type);

	dev->features |= NETIF_F_LLTX;

	dev->hard_header_len = PPP_HDRLEN;
	dev->mtu = PPP_MRU;
	dev->addr_len = 0;
	dev->tx_queue_len = 3;
	dev->type = ARPHRD_PPP;
	dev->flags = IFF_POINTOPOINT | IFF_NOARP | IFF_MULTICAST;
	dev->priv_destructor = ppp_dev_priv_destructor;
	netif_keep_dst(dev);
}