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
struct net_device {int min_mtu; int needs_free_netdev; int flags; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  tx_queue_len; int /*<<< orphan*/  type; scalar_t__ addr_len; int /*<<< orphan*/  hard_header_len; int /*<<< orphan*/  priv_destructor; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_SLIP ; 
 int IFF_NOARP ; 
 int IFF_POINTOPOINT ; 
 int /*<<< orphan*/  NETIUCV_HDRLEN ; 
 int /*<<< orphan*/  NETIUCV_MTU_DEFAULT ; 
 int /*<<< orphan*/  NETIUCV_MTU_MAX ; 
 int /*<<< orphan*/  NETIUCV_QUEUELEN_DEFAULT ; 
 int /*<<< orphan*/  netiucv_free_netdevice ; 
 int /*<<< orphan*/  netiucv_netdev_ops ; 

__attribute__((used)) static void netiucv_setup_netdevice(struct net_device *dev)
{
	dev->mtu	         = NETIUCV_MTU_DEFAULT;
	dev->min_mtu		 = 576;
	dev->max_mtu		 = NETIUCV_MTU_MAX;
	dev->needs_free_netdev   = true;
	dev->priv_destructor     = netiucv_free_netdevice;
	dev->hard_header_len     = NETIUCV_HDRLEN;
	dev->addr_len            = 0;
	dev->type                = ARPHRD_SLIP;
	dev->tx_queue_len        = NETIUCV_QUEUELEN_DEFAULT;
	dev->flags	         = IFF_POINTOPOINT | IFF_NOARP;
	dev->netdev_ops		 = &netiucv_netdev_ops;
}