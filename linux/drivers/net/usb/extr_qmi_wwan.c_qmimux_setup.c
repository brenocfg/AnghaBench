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
struct net_device {int flags; int mtu; int needs_free_netdev; int /*<<< orphan*/ * netdev_ops; scalar_t__ addr_len; scalar_t__ hard_header_len; int /*<<< orphan*/  type; int /*<<< orphan*/ * header_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_NONE ; 
 int IFF_MULTICAST ; 
 int IFF_NOARP ; 
 int IFF_POINTOPOINT ; 
 int /*<<< orphan*/  qmimux_netdev_ops ; 

__attribute__((used)) static void qmimux_setup(struct net_device *dev)
{
	dev->header_ops      = NULL;  /* No header */
	dev->type            = ARPHRD_NONE;
	dev->hard_header_len = 0;
	dev->addr_len        = 0;
	dev->flags           = IFF_POINTOPOINT | IFF_NOARP | IFF_MULTICAST;
	dev->netdev_ops      = &qmimux_netdev_ops;
	dev->mtu             = 1500;
	dev->needs_free_netdev = true;
}