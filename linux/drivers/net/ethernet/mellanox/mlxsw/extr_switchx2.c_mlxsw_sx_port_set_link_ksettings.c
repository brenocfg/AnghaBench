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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct mlxsw_sx_port {int /*<<< orphan*/  local_port; struct mlxsw_sx* mlxsw_sx; } ;
struct mlxsw_sx {int /*<<< orphan*/  core; } ;
struct TYPE_4__ {int speed; scalar_t__ autoneg; } ;
struct TYPE_3__ {int /*<<< orphan*/  advertising; } ;
struct ethtool_link_ksettings {TYPE_2__ base; TYPE_1__ link_modes; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int EINVAL ; 
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_PTYS_LEN ; 
 int /*<<< orphan*/  ethtool_convert_link_mode_to_legacy_u32 (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_ptys_eth_pack (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mlxsw_reg_ptys_eth_unpack (char*,int*,int*,int /*<<< orphan*/ *) ; 
 int mlxsw_reg_query (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int mlxsw_sx_port_admin_status_set (struct mlxsw_sx_port*,int) ; 
 int mlxsw_sx_port_oper_status_get (struct mlxsw_sx_port*,int*) ; 
 int mlxsw_sx_to_ptys_advert_link (int) ; 
 int mlxsw_sx_to_ptys_speed (int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct mlxsw_sx_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ptys ; 

__attribute__((used)) static int
mlxsw_sx_port_set_link_ksettings(struct net_device *dev,
				 const struct ethtool_link_ksettings *cmd)
{
	struct mlxsw_sx_port *mlxsw_sx_port = netdev_priv(dev);
	struct mlxsw_sx *mlxsw_sx = mlxsw_sx_port->mlxsw_sx;
	char ptys_pl[MLXSW_REG_PTYS_LEN];
	u32 speed;
	u32 eth_proto_new;
	u32 eth_proto_cap;
	u32 eth_proto_admin;
	u32 advertising;
	bool is_up;
	int err;

	speed = cmd->base.speed;

	ethtool_convert_link_mode_to_legacy_u32(&advertising,
						cmd->link_modes.advertising);

	eth_proto_new = cmd->base.autoneg == AUTONEG_ENABLE ?
		mlxsw_sx_to_ptys_advert_link(advertising) :
		mlxsw_sx_to_ptys_speed(speed);

	mlxsw_reg_ptys_eth_pack(ptys_pl, mlxsw_sx_port->local_port, 0, false);
	err = mlxsw_reg_query(mlxsw_sx->core, MLXSW_REG(ptys), ptys_pl);
	if (err) {
		netdev_err(dev, "Failed to get proto");
		return err;
	}
	mlxsw_reg_ptys_eth_unpack(ptys_pl, &eth_proto_cap, &eth_proto_admin,
				  NULL);

	eth_proto_new = eth_proto_new & eth_proto_cap;
	if (!eth_proto_new) {
		netdev_err(dev, "Not supported proto admin requested");
		return -EINVAL;
	}
	if (eth_proto_new == eth_proto_admin)
		return 0;

	mlxsw_reg_ptys_eth_pack(ptys_pl, mlxsw_sx_port->local_port,
				eth_proto_new, true);
	err = mlxsw_reg_write(mlxsw_sx->core, MLXSW_REG(ptys), ptys_pl);
	if (err) {
		netdev_err(dev, "Failed to set proto admin");
		return err;
	}

	err = mlxsw_sx_port_oper_status_get(mlxsw_sx_port, &is_up);
	if (err) {
		netdev_err(dev, "Failed to get oper status");
		return err;
	}
	if (!is_up)
		return 0;

	err = mlxsw_sx_port_admin_status_set(mlxsw_sx_port, false);
	if (err) {
		netdev_err(dev, "Failed to set admin status");
		return err;
	}

	err = mlxsw_sx_port_admin_status_set(mlxsw_sx_port, true);
	if (err) {
		netdev_err(dev, "Failed to set admin status");
		return err;
	}

	return 0;
}