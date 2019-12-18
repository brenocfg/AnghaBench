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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct mlxsw_sp_port_type_speed_ops {int /*<<< orphan*/  (* from_ptys_speed_duplex ) (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ethtool_link_ksettings*) ;int /*<<< orphan*/  (* reg_ptys_eth_unpack ) (struct mlxsw_sp*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* reg_ptys_eth_pack ) (struct mlxsw_sp*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  width; } ;
struct TYPE_4__ {int autoneg; } ;
struct mlxsw_sp_port {TYPE_2__ mapping; int /*<<< orphan*/  local_port; TYPE_1__ link; struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; struct mlxsw_sp_port_type_speed_ops* port_type_speed_ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  port; int /*<<< orphan*/  autoneg; } ;
struct ethtool_link_ksettings {TYPE_3__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_PTYS_LEN ; 
 int /*<<< orphan*/  mlxsw_reg_ptys_connector_type_get (char*) ; 
 int mlxsw_reg_query (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_sp_port_connector_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_port_get_link_advertise (struct mlxsw_sp*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct ethtool_link_ksettings*) ; 
 int /*<<< orphan*/  mlxsw_sp_port_get_link_supported (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ethtool_link_ksettings*) ; 
 struct mlxsw_sp_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  ptys ; 
 int /*<<< orphan*/  stub1 (struct mlxsw_sp*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct mlxsw_sp*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ethtool_link_ksettings*) ; 

__attribute__((used)) static int mlxsw_sp_port_get_link_ksettings(struct net_device *dev,
					    struct ethtool_link_ksettings *cmd)
{
	u32 eth_proto_cap, eth_proto_admin, eth_proto_oper;
	struct mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);
	struct mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	const struct mlxsw_sp_port_type_speed_ops *ops;
	char ptys_pl[MLXSW_REG_PTYS_LEN];
	u8 connector_type;
	bool autoneg;
	int err;

	ops = mlxsw_sp->port_type_speed_ops;

	autoneg = mlxsw_sp_port->link.autoneg;
	ops->reg_ptys_eth_pack(mlxsw_sp, ptys_pl, mlxsw_sp_port->local_port,
			       0, false);
	err = mlxsw_reg_query(mlxsw_sp->core, MLXSW_REG(ptys), ptys_pl);
	if (err)
		return err;
	ops->reg_ptys_eth_unpack(mlxsw_sp, ptys_pl, &eth_proto_cap,
				 &eth_proto_admin, &eth_proto_oper);

	mlxsw_sp_port_get_link_supported(mlxsw_sp, eth_proto_cap,
					 mlxsw_sp_port->mapping.width, cmd);

	mlxsw_sp_port_get_link_advertise(mlxsw_sp, eth_proto_admin, autoneg,
					 mlxsw_sp_port->mapping.width, cmd);

	cmd->base.autoneg = autoneg ? AUTONEG_ENABLE : AUTONEG_DISABLE;
	connector_type = mlxsw_reg_ptys_connector_type_get(ptys_pl);
	cmd->base.port = mlxsw_sp_port_connector_port(connector_type);
	ops->from_ptys_speed_duplex(mlxsw_sp, netif_carrier_ok(dev),
				    eth_proto_oper, cmd);

	return 0;
}