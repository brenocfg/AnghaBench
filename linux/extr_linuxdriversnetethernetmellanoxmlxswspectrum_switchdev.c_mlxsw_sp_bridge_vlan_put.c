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
struct mlxsw_sp_bridge_vlan {int /*<<< orphan*/  port_vlan_list; } ;

/* Variables and functions */
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_bridge_vlan_destroy (struct mlxsw_sp_bridge_vlan*) ; 

__attribute__((used)) static void mlxsw_sp_bridge_vlan_put(struct mlxsw_sp_bridge_vlan *bridge_vlan)
{
	if (list_empty(&bridge_vlan->port_vlan_list))
		mlxsw_sp_bridge_vlan_destroy(bridge_vlan);
}