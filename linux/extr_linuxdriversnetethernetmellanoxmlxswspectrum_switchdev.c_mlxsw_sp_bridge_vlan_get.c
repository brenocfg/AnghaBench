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
struct mlxsw_sp_bridge_vlan {int dummy; } ;
struct mlxsw_sp_bridge_port {int dummy; } ;

/* Variables and functions */
 struct mlxsw_sp_bridge_vlan* mlxsw_sp_bridge_vlan_create (struct mlxsw_sp_bridge_port*,int /*<<< orphan*/ ) ; 
 struct mlxsw_sp_bridge_vlan* mlxsw_sp_bridge_vlan_find (struct mlxsw_sp_bridge_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mlxsw_sp_bridge_vlan *
mlxsw_sp_bridge_vlan_get(struct mlxsw_sp_bridge_port *bridge_port, u16 vid)
{
	struct mlxsw_sp_bridge_vlan *bridge_vlan;

	bridge_vlan = mlxsw_sp_bridge_vlan_find(bridge_port, vid);
	if (bridge_vlan)
		return bridge_vlan;

	return mlxsw_sp_bridge_vlan_create(bridge_port, vid);
}