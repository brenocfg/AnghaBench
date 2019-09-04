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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {struct net_device* dev; } ;
struct switchdev_notifier_fdb_info {int /*<<< orphan*/  addr; int /*<<< orphan*/  vid; TYPE_1__ info; } ;
struct net_device {int dummy; } ;
struct mlxsw_sp_port_vlan {int /*<<< orphan*/  vid; int /*<<< orphan*/  fid; } ;
struct mlxsw_sp_port {struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp_bridge_port {int /*<<< orphan*/  lag_id; int /*<<< orphan*/  system_port; int /*<<< orphan*/  lagged; struct mlxsw_sp_bridge_device* bridge_device; } ;
struct mlxsw_sp_bridge_device {int dummy; } ;
struct mlxsw_sp {int /*<<< orphan*/  bridge; } ;

/* Variables and functions */
 int EINVAL ; 
 struct mlxsw_sp_bridge_port* mlxsw_sp_bridge_port_find (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  mlxsw_sp_fid_index (int /*<<< orphan*/ ) ; 
 int mlxsw_sp_port_fdb_uc_lag_op (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int mlxsw_sp_port_fdb_uc_op (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct mlxsw_sp_port_vlan* mlxsw_sp_port_vlan_find_by_bridge (struct mlxsw_sp_port*,struct mlxsw_sp_bridge_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mlxsw_sp_port_fdb_set(struct mlxsw_sp_port *mlxsw_sp_port,
		      struct switchdev_notifier_fdb_info *fdb_info, bool adding)
{
	struct mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	struct net_device *orig_dev = fdb_info->info.dev;
	struct mlxsw_sp_port_vlan *mlxsw_sp_port_vlan;
	struct mlxsw_sp_bridge_device *bridge_device;
	struct mlxsw_sp_bridge_port *bridge_port;
	u16 fid_index, vid;

	bridge_port = mlxsw_sp_bridge_port_find(mlxsw_sp->bridge, orig_dev);
	if (!bridge_port)
		return -EINVAL;

	bridge_device = bridge_port->bridge_device;
	mlxsw_sp_port_vlan = mlxsw_sp_port_vlan_find_by_bridge(mlxsw_sp_port,
							       bridge_device,
							       fdb_info->vid);
	if (!mlxsw_sp_port_vlan)
		return 0;

	fid_index = mlxsw_sp_fid_index(mlxsw_sp_port_vlan->fid);
	vid = mlxsw_sp_port_vlan->vid;

	if (!bridge_port->lagged)
		return mlxsw_sp_port_fdb_uc_op(mlxsw_sp,
					       bridge_port->system_port,
					       fdb_info->addr, fid_index,
					       adding, false);
	else
		return mlxsw_sp_port_fdb_uc_lag_op(mlxsw_sp,
						   bridge_port->lag_id,
						   fdb_info->addr, fid_index,
						   vid, adding, false);
}