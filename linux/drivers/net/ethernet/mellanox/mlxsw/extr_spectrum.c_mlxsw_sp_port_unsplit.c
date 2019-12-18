#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct netlink_ext_ack {int dummy; } ;
struct TYPE_4__ {size_t width; } ;
struct mlxsw_sp_port {TYPE_2__ mapping; int /*<<< orphan*/  dev; int /*<<< orphan*/  split; } ;
struct mlxsw_sp {TYPE_1__* bus_info; struct mlxsw_sp_port** ports; } ;
struct mlxsw_core {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  LOCAL_PORTS_IN_1X ; 
 int /*<<< orphan*/  LOCAL_PORTS_IN_2X ; 
 size_t MLXSW_CORE_RES_GET (struct mlxsw_core*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLXSW_CORE_RES_VALID (struct mlxsw_core*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,size_t) ; 
 struct mlxsw_sp* mlxsw_core_driver_priv (struct mlxsw_core*) ; 
 size_t mlxsw_sp_cluster_base_port_get (size_t) ; 
 scalar_t__ mlxsw_sp_port_created (struct mlxsw_sp*,size_t) ; 
 int /*<<< orphan*/  mlxsw_sp_port_remove (struct mlxsw_sp*,size_t) ; 
 int /*<<< orphan*/  mlxsw_sp_port_unsplit_create (struct mlxsw_sp*,size_t,unsigned int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int mlxsw_sp_port_unsplit(struct mlxsw_core *mlxsw_core, u8 local_port,
				 struct netlink_ext_ack *extack)
{
	struct mlxsw_sp *mlxsw_sp = mlxsw_core_driver_priv(mlxsw_core);
	u8 local_ports_in_1x, local_ports_in_2x, offset;
	struct mlxsw_sp_port *mlxsw_sp_port;
	u8 cur_width, base_port;
	unsigned int count;
	int i;

	if (!MLXSW_CORE_RES_VALID(mlxsw_core, LOCAL_PORTS_IN_1X) ||
	    !MLXSW_CORE_RES_VALID(mlxsw_core, LOCAL_PORTS_IN_2X))
		return -EIO;

	local_ports_in_1x = MLXSW_CORE_RES_GET(mlxsw_core, LOCAL_PORTS_IN_1X);
	local_ports_in_2x = MLXSW_CORE_RES_GET(mlxsw_core, LOCAL_PORTS_IN_2X);

	mlxsw_sp_port = mlxsw_sp->ports[local_port];
	if (!mlxsw_sp_port) {
		dev_err(mlxsw_sp->bus_info->dev, "Port number \"%d\" does not exist\n",
			local_port);
		NL_SET_ERR_MSG_MOD(extack, "Port number does not exist");
		return -EINVAL;
	}

	if (!mlxsw_sp_port->split) {
		netdev_err(mlxsw_sp_port->dev, "Port was not split\n");
		NL_SET_ERR_MSG_MOD(extack, "Port was not split");
		return -EINVAL;
	}

	cur_width = mlxsw_sp_port->mapping.width;
	count = cur_width == 1 ? 4 : 2;

	if (count == 2)
		offset = local_ports_in_2x;
	else
		offset = local_ports_in_1x;

	base_port = mlxsw_sp_cluster_base_port_get(local_port);

	/* Determine which ports to remove. */
	if (count == 2 && local_port >= base_port + 2)
		base_port = base_port + 2;

	for (i = 0; i < count; i++)
		if (mlxsw_sp_port_created(mlxsw_sp, base_port + i * offset))
			mlxsw_sp_port_remove(mlxsw_sp, base_port + i * offset);

	mlxsw_sp_port_unsplit_create(mlxsw_sp, base_port, count);

	return 0;
}