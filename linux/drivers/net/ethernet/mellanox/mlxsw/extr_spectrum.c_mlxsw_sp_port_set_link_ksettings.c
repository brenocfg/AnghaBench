#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct net_device {int dummy; } ;
struct mlxsw_sp_port_type_speed_ops {int (* to_ptys_advert_link ) (struct mlxsw_sp*,int /*<<< orphan*/ ,struct ethtool_link_ksettings const*) ;int (* to_ptys_speed ) (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* reg_ptys_eth_pack ) (struct mlxsw_sp*,char*,int /*<<< orphan*/ ,int,int) ;int /*<<< orphan*/  (* reg_ptys_eth_unpack ) (struct mlxsw_sp*,char*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct TYPE_6__ {int autoneg; } ;
struct TYPE_4__ {int /*<<< orphan*/  width; } ;
struct mlxsw_sp_port {TYPE_3__ link; int /*<<< orphan*/  local_port; TYPE_1__ mapping; struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; struct mlxsw_sp_port_type_speed_ops* port_type_speed_ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  speed; int /*<<< orphan*/  autoneg; } ;
struct ethtool_link_ksettings {TYPE_2__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int EINVAL ; 
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_PTYS_LEN ; 
 int mlxsw_reg_query (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_sp_port_admin_status_set (struct mlxsw_sp_port*,int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct mlxsw_sp_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  ptys ; 
 int /*<<< orphan*/  stub1 (struct mlxsw_sp*,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub2 (struct mlxsw_sp*,char*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int stub3 (struct mlxsw_sp*,int /*<<< orphan*/ ,struct ethtool_link_ksettings const*) ; 
 int stub4 (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (struct mlxsw_sp*,char*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
mlxsw_sp_port_set_link_ksettings(struct net_device *dev,
				 const struct ethtool_link_ksettings *cmd)
{
	struct mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);
	struct mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	const struct mlxsw_sp_port_type_speed_ops *ops;
	char ptys_pl[MLXSW_REG_PTYS_LEN];
	u32 eth_proto_cap, eth_proto_new;
	bool autoneg;
	int err;

	ops = mlxsw_sp->port_type_speed_ops;

	ops->reg_ptys_eth_pack(mlxsw_sp, ptys_pl, mlxsw_sp_port->local_port,
			       0, false);
	err = mlxsw_reg_query(mlxsw_sp->core, MLXSW_REG(ptys), ptys_pl);
	if (err)
		return err;
	ops->reg_ptys_eth_unpack(mlxsw_sp, ptys_pl, &eth_proto_cap, NULL, NULL);

	autoneg = cmd->base.autoneg == AUTONEG_ENABLE;
	eth_proto_new = autoneg ?
		ops->to_ptys_advert_link(mlxsw_sp, mlxsw_sp_port->mapping.width,
					 cmd) :
		ops->to_ptys_speed(mlxsw_sp, mlxsw_sp_port->mapping.width,
				   cmd->base.speed);

	eth_proto_new = eth_proto_new & eth_proto_cap;
	if (!eth_proto_new) {
		netdev_err(dev, "No supported speed requested\n");
		return -EINVAL;
	}

	ops->reg_ptys_eth_pack(mlxsw_sp, ptys_pl, mlxsw_sp_port->local_port,
			       eth_proto_new, autoneg);
	err = mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(ptys), ptys_pl);
	if (err)
		return err;

	mlxsw_sp_port->link.autoneg = autoneg;

	if (!netif_running(dev))
		return 0;

	mlxsw_sp_port_admin_status_set(mlxsw_sp_port, false);
	mlxsw_sp_port_admin_status_set(mlxsw_sp_port, true);

	return 0;
}