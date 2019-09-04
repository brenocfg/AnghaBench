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
struct net_device {int needs_free_netdev; int tx_queue_len; int /*<<< orphan*/  features; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; int /*<<< orphan*/  mtu; scalar_t__ addr_len; scalar_t__ hard_header_len; int /*<<< orphan*/  priv_destructor; int /*<<< orphan*/ * netdev_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_CAN ; 
 int /*<<< orphan*/  CAN_MTU ; 
 int /*<<< orphan*/  IFF_NOARP ; 
 int /*<<< orphan*/  NETIF_F_HW_CSUM ; 
 int /*<<< orphan*/  slc_free_netdev ; 
 int /*<<< orphan*/  slc_netdev_ops ; 

__attribute__((used)) static void slc_setup(struct net_device *dev)
{
	dev->netdev_ops		= &slc_netdev_ops;
	dev->needs_free_netdev	= true;
	dev->priv_destructor	= slc_free_netdev;

	dev->hard_header_len	= 0;
	dev->addr_len		= 0;
	dev->tx_queue_len	= 10;

	dev->mtu		= CAN_MTU;
	dev->type		= ARPHRD_CAN;

	/* New-style flags. */
	dev->flags		= IFF_NOARP;
	dev->features           = NETIF_F_HW_CSUM;
}