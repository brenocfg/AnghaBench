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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int autoneg; } ;
struct mlxsw_sp_port {int /*<<< orphan*/  local_port; TYPE_1__ link; struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;
struct TYPE_4__ {int /*<<< orphan*/  port; int /*<<< orphan*/  autoneg; } ;
struct ethtool_link_ksettings {TYPE_2__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_PTYS_LEN ; 
 int /*<<< orphan*/  mlxsw_reg_ptys_an_status_get (char*) ; 
 int /*<<< orphan*/  mlxsw_reg_ptys_eth_pack (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlxsw_reg_ptys_eth_proto_lp_advertise_get (char*) ; 
 int /*<<< orphan*/  mlxsw_reg_ptys_eth_unpack (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mlxsw_reg_query (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_sp_from_ptys_speed_duplex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ethtool_link_ksettings*) ; 
 int /*<<< orphan*/  mlxsw_sp_port_connector_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_port_get_link_advertise (int /*<<< orphan*/ ,int,struct ethtool_link_ksettings*) ; 
 int /*<<< orphan*/  mlxsw_sp_port_get_link_lp_advertise (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ethtool_link_ksettings*) ; 
 int /*<<< orphan*/  mlxsw_sp_port_get_link_supported (int /*<<< orphan*/ ,struct ethtool_link_ksettings*) ; 
 struct mlxsw_sp_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  ptys ; 

__attribute__((used)) static int mlxsw_sp_port_get_link_ksettings(struct net_device *dev,
					    struct ethtool_link_ksettings *cmd)
{
	u32 eth_proto_cap, eth_proto_admin, eth_proto_oper, eth_proto_lp;
	struct mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);
	struct mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	char ptys_pl[MLXSW_REG_PTYS_LEN];
	u8 autoneg_status;
	bool autoneg;
	int err;

	autoneg = mlxsw_sp_port->link.autoneg;
	mlxsw_reg_ptys_eth_pack(ptys_pl, mlxsw_sp_port->local_port, 0, false);
	err = mlxsw_reg_query(mlxsw_sp->core, MLXSW_REG(ptys), ptys_pl);
	if (err)
		return err;
	mlxsw_reg_ptys_eth_unpack(ptys_pl, &eth_proto_cap, &eth_proto_admin,
				  &eth_proto_oper);

	mlxsw_sp_port_get_link_supported(eth_proto_cap, cmd);

	mlxsw_sp_port_get_link_advertise(eth_proto_admin, autoneg, cmd);

	eth_proto_lp = mlxsw_reg_ptys_eth_proto_lp_advertise_get(ptys_pl);
	autoneg_status = mlxsw_reg_ptys_an_status_get(ptys_pl);
	mlxsw_sp_port_get_link_lp_advertise(eth_proto_lp, autoneg_status, cmd);

	cmd->base.autoneg = autoneg ? AUTONEG_ENABLE : AUTONEG_DISABLE;
	cmd->base.port = mlxsw_sp_port_connector_port(eth_proto_oper);
	mlxsw_sp_from_ptys_speed_duplex(netif_carrier_ok(dev), eth_proto_oper,
					cmd);

	return 0;
}