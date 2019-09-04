#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct mlxsw_sp_port {struct net_device* dev; } ;
struct mlxsw_sp_mid {int /*<<< orphan*/  mid; } ;
struct mlxsw_sp_bridge_port {int /*<<< orphan*/  mrouter; TYPE_1__* bridge_device; } ;
struct TYPE_2__ {scalar_t__ multicast_enabled; } ;

/* Variables and functions */
 int mlxsw_sp_port_remove_from_mid (struct mlxsw_sp_port*,struct mlxsw_sp_mid*) ; 
 int mlxsw_sp_port_smid_set (struct mlxsw_sp_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 

__attribute__((used)) static int
__mlxsw_sp_port_mdb_del(struct mlxsw_sp_port *mlxsw_sp_port,
			struct mlxsw_sp_bridge_port *bridge_port,
			struct mlxsw_sp_mid *mid)
{
	struct net_device *dev = mlxsw_sp_port->dev;
	int err;

	if (bridge_port->bridge_device->multicast_enabled &&
	    !bridge_port->mrouter) {
		err = mlxsw_sp_port_smid_set(mlxsw_sp_port, mid->mid, false);
		if (err)
			netdev_err(dev, "Unable to remove port from SMID\n");
	}

	err = mlxsw_sp_port_remove_from_mid(mlxsw_sp_port, mid);
	if (err)
		netdev_err(dev, "Unable to remove MC SFD\n");

	return err;
}