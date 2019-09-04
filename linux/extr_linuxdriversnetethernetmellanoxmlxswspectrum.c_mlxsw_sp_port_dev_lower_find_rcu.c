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
struct net_device {int dummy; } ;
struct mlxsw_sp_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp_lower_dev_walk ; 
 scalar_t__ mlxsw_sp_port_dev_check (struct net_device*) ; 
 struct mlxsw_sp_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_walk_all_lower_dev_rcu (struct net_device*,int /*<<< orphan*/ ,struct mlxsw_sp_port**) ; 

struct mlxsw_sp_port *mlxsw_sp_port_dev_lower_find_rcu(struct net_device *dev)
{
	struct mlxsw_sp_port *mlxsw_sp_port;

	if (mlxsw_sp_port_dev_check(dev))
		return netdev_priv(dev);

	mlxsw_sp_port = NULL;
	netdev_walk_all_lower_dev_rcu(dev, mlxsw_sp_lower_dev_walk,
				      &mlxsw_sp_port);

	return mlxsw_sp_port;
}