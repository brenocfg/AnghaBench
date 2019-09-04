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
struct mlxsw_sp_port {int /*<<< orphan*/  local_port; struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;
typedef  enum ethtool_phys_id_state { ____Placeholder_ethtool_phys_id_state } ethtool_phys_id_state ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  ETHTOOL_ID_ACTIVE 129 
#define  ETHTOOL_ID_INACTIVE 128 
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_MLCR_LEN ; 
 int /*<<< orphan*/  mlcr ; 
 int /*<<< orphan*/  mlxsw_reg_mlcr_pack (char*,int /*<<< orphan*/ ,int) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct mlxsw_sp_port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlxsw_sp_port_set_phys_id(struct net_device *dev,
				     enum ethtool_phys_id_state state)
{
	struct mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);
	struct mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	char mlcr_pl[MLXSW_REG_MLCR_LEN];
	bool active;

	switch (state) {
	case ETHTOOL_ID_ACTIVE:
		active = true;
		break;
	case ETHTOOL_ID_INACTIVE:
		active = false;
		break;
	default:
		return -EOPNOTSUPP;
	}

	mlxsw_reg_mlcr_pack(mlcr_pl, mlxsw_sp_port->local_port, active);
	return mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(mlcr), mlcr_pl);
}