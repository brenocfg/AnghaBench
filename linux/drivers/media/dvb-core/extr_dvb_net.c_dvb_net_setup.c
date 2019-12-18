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
struct net_device {int mtu; int max_mtu; int /*<<< orphan*/  flags; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/ * header_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_NOARP ; 
 int /*<<< orphan*/  dvb_header_ops ; 
 int /*<<< orphan*/  dvb_netdev_ops ; 
 int /*<<< orphan*/  ether_setup (struct net_device*) ; 

__attribute__((used)) static void dvb_net_setup(struct net_device *dev)
{
	ether_setup(dev);

	dev->header_ops		= &dvb_header_ops;
	dev->netdev_ops		= &dvb_netdev_ops;
	dev->mtu		= 4096;
	dev->max_mtu		= 4096;

	dev->flags |= IFF_NOARP;
}