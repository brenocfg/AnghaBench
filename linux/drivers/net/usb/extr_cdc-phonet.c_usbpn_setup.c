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
struct net_device {int flags; int hard_header_len; int addr_len; int tx_queue_len; int needs_free_netdev; int /*<<< orphan*/ * dev_addr; void* max_mtu; int /*<<< orphan*/  min_mtu; void* mtu; int /*<<< orphan*/  type; int /*<<< orphan*/ * header_ops; int /*<<< orphan*/ * netdev_ops; scalar_t__ features; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_PHONET ; 
 int IFF_NOARP ; 
 int IFF_POINTOPOINT ; 
 void* PHONET_MAX_MTU ; 
 int /*<<< orphan*/  PHONET_MIN_MTU ; 
 int /*<<< orphan*/  PN_MEDIA_USB ; 
 int /*<<< orphan*/  phonet_header_ops ; 
 int /*<<< orphan*/  usbpn_ops ; 

__attribute__((used)) static void usbpn_setup(struct net_device *dev)
{
	dev->features		= 0;
	dev->netdev_ops		= &usbpn_ops,
	dev->header_ops		= &phonet_header_ops;
	dev->type		= ARPHRD_PHONET;
	dev->flags		= IFF_POINTOPOINT | IFF_NOARP;
	dev->mtu		= PHONET_MAX_MTU;
	dev->min_mtu		= PHONET_MIN_MTU;
	dev->max_mtu		= PHONET_MAX_MTU;
	dev->hard_header_len	= 1;
	dev->dev_addr[0]	= PN_MEDIA_USB;
	dev->addr_len		= 1;
	dev->tx_queue_len	= 3;

	dev->needs_free_netdev	= true;
}