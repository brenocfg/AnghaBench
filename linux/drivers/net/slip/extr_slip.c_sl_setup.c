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
struct net_device {int needs_free_netdev; int tx_queue_len; int min_mtu; int max_mtu; int flags; scalar_t__ addr_len; scalar_t__ hard_header_len; int /*<<< orphan*/  priv_destructor; int /*<<< orphan*/ * netdev_ops; } ;

/* Variables and functions */
 int IFF_MULTICAST ; 
 int IFF_NOARP ; 
 int IFF_POINTOPOINT ; 
 int /*<<< orphan*/  sl_free_netdev ; 
 int /*<<< orphan*/  sl_netdev_ops ; 

__attribute__((used)) static void sl_setup(struct net_device *dev)
{
	dev->netdev_ops		= &sl_netdev_ops;
	dev->needs_free_netdev	= true;
	dev->priv_destructor	= sl_free_netdev;

	dev->hard_header_len	= 0;
	dev->addr_len		= 0;
	dev->tx_queue_len	= 10;

	/* MTU range: 68 - 65534 */
	dev->min_mtu = 68;
	dev->max_mtu = 65534;

	/* New-style flags. */
	dev->flags		= IFF_NOARP|IFF_POINTOPOINT|IFF_MULTICAST;
}