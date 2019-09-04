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
struct mlxsw_sp_port_vlan {scalar_t__ ref_count; scalar_t__ bridge_port; struct mlxsw_sp_fid* fid; } ;
struct mlxsw_sp_fid {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp_port_vlan_bridge_leave (struct mlxsw_sp_port_vlan*) ; 
 int /*<<< orphan*/  mlxsw_sp_port_vlan_destroy (struct mlxsw_sp_port_vlan*) ; 
 int /*<<< orphan*/  mlxsw_sp_port_vlan_router_leave (struct mlxsw_sp_port_vlan*) ; 

void mlxsw_sp_port_vlan_put(struct mlxsw_sp_port_vlan *mlxsw_sp_port_vlan)
{
	struct mlxsw_sp_fid *fid = mlxsw_sp_port_vlan->fid;

	if (--mlxsw_sp_port_vlan->ref_count != 0)
		return;

	if (mlxsw_sp_port_vlan->bridge_port)
		mlxsw_sp_port_vlan_bridge_leave(mlxsw_sp_port_vlan);
	else if (fid)
		mlxsw_sp_port_vlan_router_leave(mlxsw_sp_port_vlan);

	mlxsw_sp_port_vlan_destroy(mlxsw_sp_port_vlan);
}