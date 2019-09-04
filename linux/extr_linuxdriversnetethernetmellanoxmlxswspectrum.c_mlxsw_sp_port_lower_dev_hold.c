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
struct mlxsw_sp_port {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_hold (int /*<<< orphan*/ ) ; 
 struct mlxsw_sp_port* mlxsw_sp_port_dev_lower_find_rcu (struct net_device*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

struct mlxsw_sp_port *mlxsw_sp_port_lower_dev_hold(struct net_device *dev)
{
	struct mlxsw_sp_port *mlxsw_sp_port;

	rcu_read_lock();
	mlxsw_sp_port = mlxsw_sp_port_dev_lower_find_rcu(dev);
	if (mlxsw_sp_port)
		dev_hold(mlxsw_sp_port->dev);
	rcu_read_unlock();
	return mlxsw_sp_port;
}