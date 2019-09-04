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
typedef  int /*<<< orphan*/  u64 ;
struct net_device {int dummy; } ;
struct mlxsw_sp_port_hw_stats {int /*<<< orphan*/  cells_bytes; int /*<<< orphan*/  (* getter ) (char*) ;} ;
struct mlxsw_sp_port {struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp {int dummy; } ;
typedef  enum mlxsw_reg_ppcnt_grp { ____Placeholder_mlxsw_reg_ppcnt_grp } mlxsw_reg_ppcnt_grp ;

/* Variables and functions */
 int MLXSW_REG_PPCNT_LEN ; 
 int /*<<< orphan*/  mlxsw_sp_cells_bytes (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 
 int mlxsw_sp_get_hw_stats_by_group (struct mlxsw_sp_port_hw_stats**,int*,int) ; 
 int /*<<< orphan*/  mlxsw_sp_port_get_stats_raw (struct net_device*,int,int,char*) ; 
 struct mlxsw_sp_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (char*) ; 

__attribute__((used)) static void __mlxsw_sp_port_get_stats(struct net_device *dev,
				      enum mlxsw_reg_ppcnt_grp grp, int prio,
				      u64 *data, int data_index)
{
	struct mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);
	struct mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	struct mlxsw_sp_port_hw_stats *hw_stats;
	char ppcnt_pl[MLXSW_REG_PPCNT_LEN];
	int i, len;
	int err;

	err = mlxsw_sp_get_hw_stats_by_group(&hw_stats, &len, grp);
	if (err)
		return;
	mlxsw_sp_port_get_stats_raw(dev, grp, prio, ppcnt_pl);
	for (i = 0; i < len; i++) {
		data[data_index + i] = hw_stats[i].getter(ppcnt_pl);
		if (!hw_stats[i].cells_bytes)
			continue;
		data[data_index + i] = mlxsw_sp_cells_bytes(mlxsw_sp,
							    data[data_index + i]);
	}
}