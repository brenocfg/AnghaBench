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
struct net_device {int needs_free_netdev; int hard_header_len; int mtu; scalar_t__ addr_len; int /*<<< orphan*/  type; int /*<<< orphan*/ * netdev_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_X25 ; 
 int /*<<< orphan*/  lapbeth_netdev_ops ; 

__attribute__((used)) static void lapbeth_setup(struct net_device *dev)
{
	dev->netdev_ops	     = &lapbeth_netdev_ops;
	dev->needs_free_netdev = true;
	dev->type            = ARPHRD_X25;
	dev->hard_header_len = 3;
	dev->mtu             = 1000;
	dev->addr_len        = 0;
}