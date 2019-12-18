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
struct mlxsw_sp_port_vlan {scalar_t__ fid; scalar_t__ bridge_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp_port_vlan_bridge_leave (struct mlxsw_sp_port_vlan*) ; 
 int /*<<< orphan*/  mlxsw_sp_port_vlan_router_leave (struct mlxsw_sp_port_vlan*) ; 

__attribute__((used)) static void
mlxsw_sp_port_vlan_cleanup(struct mlxsw_sp_port_vlan *mlxsw_sp_port_vlan)
{
	if (mlxsw_sp_port_vlan->bridge_port)
		mlxsw_sp_port_vlan_bridge_leave(mlxsw_sp_port_vlan);
	else if (mlxsw_sp_port_vlan->fid)
		mlxsw_sp_port_vlan_router_leave(mlxsw_sp_port_vlan);
}