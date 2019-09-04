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
struct mlxsw_sp_port_vlan {struct mlxsw_sp_bridge_port* bridge_port; int /*<<< orphan*/  bridge_vlan_node; int /*<<< orphan*/  vid; struct mlxsw_sp_fid* fid; struct mlxsw_sp_port* mlxsw_sp_port; } ;
struct mlxsw_sp_port {TYPE_1__* mlxsw_sp; } ;
struct mlxsw_sp_fid {int dummy; } ;
struct mlxsw_sp_bridge_vlan {int /*<<< orphan*/  port_vlan_list; } ;
struct mlxsw_sp_bridge_port {int /*<<< orphan*/  vlans_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  bridge; } ;

/* Variables and functions */
 int /*<<< orphan*/  BR_STATE_DISABLED ; 
 scalar_t__ MLXSW_SP_FID_TYPE_8021D ; 
 scalar_t__ MLXSW_SP_FID_TYPE_8021Q ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int list_is_singular (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_bridge_port_fdb_flush (TYPE_1__*,struct mlxsw_sp_bridge_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_bridge_port_mdb_flush (struct mlxsw_sp_port*,struct mlxsw_sp_bridge_port*) ; 
 int /*<<< orphan*/  mlxsw_sp_bridge_port_put (int /*<<< orphan*/ ,struct mlxsw_sp_bridge_port*) ; 
 struct mlxsw_sp_bridge_vlan* mlxsw_sp_bridge_vlan_find (struct mlxsw_sp_bridge_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_bridge_vlan_put (struct mlxsw_sp_bridge_vlan*) ; 
 int /*<<< orphan*/  mlxsw_sp_fid_index (struct mlxsw_sp_fid*) ; 
 scalar_t__ mlxsw_sp_fid_type (struct mlxsw_sp_fid*) ; 
 int /*<<< orphan*/  mlxsw_sp_port_vid_learning_set (struct mlxsw_sp_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlxsw_sp_port_vid_stp_set (struct mlxsw_sp_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_port_vlan_fid_leave (struct mlxsw_sp_port_vlan*) ; 

void
mlxsw_sp_port_vlan_bridge_leave(struct mlxsw_sp_port_vlan *mlxsw_sp_port_vlan)
{
	struct mlxsw_sp_port *mlxsw_sp_port = mlxsw_sp_port_vlan->mlxsw_sp_port;
	struct mlxsw_sp_fid *fid = mlxsw_sp_port_vlan->fid;
	struct mlxsw_sp_bridge_vlan *bridge_vlan;
	struct mlxsw_sp_bridge_port *bridge_port;
	u16 vid = mlxsw_sp_port_vlan->vid;
	bool last_port, last_vlan;

	if (WARN_ON(mlxsw_sp_fid_type(fid) != MLXSW_SP_FID_TYPE_8021Q &&
		    mlxsw_sp_fid_type(fid) != MLXSW_SP_FID_TYPE_8021D))
		return;

	bridge_port = mlxsw_sp_port_vlan->bridge_port;
	last_vlan = list_is_singular(&bridge_port->vlans_list);
	bridge_vlan = mlxsw_sp_bridge_vlan_find(bridge_port, vid);
	last_port = list_is_singular(&bridge_vlan->port_vlan_list);

	list_del(&mlxsw_sp_port_vlan->bridge_vlan_node);
	mlxsw_sp_bridge_vlan_put(bridge_vlan);
	mlxsw_sp_port_vid_stp_set(mlxsw_sp_port, vid, BR_STATE_DISABLED);
	mlxsw_sp_port_vid_learning_set(mlxsw_sp_port, vid, false);
	if (last_port)
		mlxsw_sp_bridge_port_fdb_flush(mlxsw_sp_port->mlxsw_sp,
					       bridge_port,
					       mlxsw_sp_fid_index(fid));
	if (last_vlan)
		mlxsw_sp_bridge_port_mdb_flush(mlxsw_sp_port, bridge_port);

	mlxsw_sp_port_vlan_fid_leave(mlxsw_sp_port_vlan);

	mlxsw_sp_bridge_port_put(mlxsw_sp_port->mlxsw_sp->bridge, bridge_port);
	mlxsw_sp_port_vlan->bridge_port = NULL;
}