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
struct net_device {int /*<<< orphan*/ * netdev_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipvlan_netdev_ops ; 

__attribute__((used)) static bool netif_is_ipvlan(const struct net_device *dev)
{
	/* both ipvlan and ipvtap devices use the same netdev_ops */
	return dev->netdev_ops == &ipvlan_netdev_ops;
}