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
 int /*<<< orphan*/  mlx5e_netdev_ops_rep ; 
 int /*<<< orphan*/  mlx5e_netdev_ops_uplink_rep ; 

bool mlx5e_eswitch_rep(struct net_device *netdev)
{
	if (netdev->netdev_ops == &mlx5e_netdev_ops_rep ||
	    netdev->netdev_ops == &mlx5e_netdev_ops_uplink_rep)
		return true;

	return false;
}