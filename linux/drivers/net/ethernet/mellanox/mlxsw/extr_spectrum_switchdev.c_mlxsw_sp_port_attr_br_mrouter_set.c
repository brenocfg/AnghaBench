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
struct switchdev_trans {int dummy; } ;
struct net_device {int dummy; } ;
struct mlxsw_sp_port {struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp_bridge_device {int mrouter; } ;
struct mlxsw_sp {int /*<<< orphan*/  bridge; } ;

/* Variables and functions */
 struct mlxsw_sp_bridge_device* mlxsw_sp_bridge_device_find (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  mlxsw_sp_bridge_mrouter_update_mdb (struct mlxsw_sp*,struct mlxsw_sp_bridge_device*,int) ; 
 scalar_t__ switchdev_trans_ph_prepare (struct switchdev_trans*) ; 

__attribute__((used)) static int
mlxsw_sp_port_attr_br_mrouter_set(struct mlxsw_sp_port *mlxsw_sp_port,
				  struct switchdev_trans *trans,
				  struct net_device *orig_dev,
				  bool is_mrouter)
{
	struct mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	struct mlxsw_sp_bridge_device *bridge_device;

	if (switchdev_trans_ph_prepare(trans))
		return 0;

	/* It's possible we failed to enslave the port, yet this
	 * operation is executed due to it being deferred.
	 */
	bridge_device = mlxsw_sp_bridge_device_find(mlxsw_sp->bridge, orig_dev);
	if (!bridge_device)
		return 0;

	if (bridge_device->mrouter != is_mrouter)
		mlxsw_sp_bridge_mrouter_update_mdb(mlxsw_sp, bridge_device,
						   is_mrouter);
	bridge_device->mrouter = is_mrouter;
	return 0;
}