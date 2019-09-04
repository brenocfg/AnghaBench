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
typedef  int /*<<< orphan*/  u16 ;
struct mlxsw_sp_port_vlan {int /*<<< orphan*/  ref_count; } ;
struct mlxsw_sp_port {int dummy; } ;

/* Variables and functions */
 struct mlxsw_sp_port_vlan* mlxsw_sp_port_vlan_create (struct mlxsw_sp_port*,int /*<<< orphan*/ ) ; 
 struct mlxsw_sp_port_vlan* mlxsw_sp_port_vlan_find_by_vid (struct mlxsw_sp_port*,int /*<<< orphan*/ ) ; 

struct mlxsw_sp_port_vlan *
mlxsw_sp_port_vlan_get(struct mlxsw_sp_port *mlxsw_sp_port, u16 vid)
{
	struct mlxsw_sp_port_vlan *mlxsw_sp_port_vlan;

	mlxsw_sp_port_vlan = mlxsw_sp_port_vlan_find_by_vid(mlxsw_sp_port, vid);
	if (mlxsw_sp_port_vlan) {
		mlxsw_sp_port_vlan->ref_count++;
		return mlxsw_sp_port_vlan;
	}

	return mlxsw_sp_port_vlan_create(mlxsw_sp_port, vid);
}