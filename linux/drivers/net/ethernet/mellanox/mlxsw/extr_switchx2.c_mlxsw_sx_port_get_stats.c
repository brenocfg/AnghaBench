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
typedef  int /*<<< orphan*/  u64 ;
struct net_device {int dummy; } ;
struct mlxsw_sx_port {int /*<<< orphan*/  local_port; struct mlxsw_sx* mlxsw_sx; } ;
struct mlxsw_sx {int /*<<< orphan*/  core; } ;
struct ethtool_stats {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* getter ) (char*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLXSW_REG_PPCNT_IEEE_8023_CNT ; 
 int MLXSW_REG_PPCNT_LEN ; 
 int MLXSW_SX_PORT_HW_STATS_LEN ; 
 int /*<<< orphan*/  mlxsw_reg_ppcnt_pack (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_query (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* mlxsw_sx_port_hw_stats ; 
 struct mlxsw_sx_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ppcnt ; 
 int /*<<< orphan*/  stub1 (char*) ; 

__attribute__((used)) static void mlxsw_sx_port_get_stats(struct net_device *dev,
				    struct ethtool_stats *stats, u64 *data)
{
	struct mlxsw_sx_port *mlxsw_sx_port = netdev_priv(dev);
	struct mlxsw_sx *mlxsw_sx = mlxsw_sx_port->mlxsw_sx;
	char ppcnt_pl[MLXSW_REG_PPCNT_LEN];
	int i;
	int err;

	mlxsw_reg_ppcnt_pack(ppcnt_pl, mlxsw_sx_port->local_port,
			     MLXSW_REG_PPCNT_IEEE_8023_CNT, 0);
	err = mlxsw_reg_query(mlxsw_sx->core, MLXSW_REG(ppcnt), ppcnt_pl);
	for (i = 0; i < MLXSW_SX_PORT_HW_STATS_LEN; i++)
		data[i] = !err ? mlxsw_sx_port_hw_stats[i].getter(ppcnt_pl) : 0;
}