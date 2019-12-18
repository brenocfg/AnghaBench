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
struct mlxsw_sp_bridge_vlan {int /*<<< orphan*/  list; int /*<<< orphan*/  vid; int /*<<< orphan*/  port_vlan_list; } ;
struct mlxsw_sp_bridge_port {int /*<<< orphan*/  vlans_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct mlxsw_sp_bridge_vlan* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mlxsw_sp_bridge_vlan *
mlxsw_sp_bridge_vlan_create(struct mlxsw_sp_bridge_port *bridge_port, u16 vid)
{
	struct mlxsw_sp_bridge_vlan *bridge_vlan;

	bridge_vlan = kzalloc(sizeof(*bridge_vlan), GFP_KERNEL);
	if (!bridge_vlan)
		return NULL;

	INIT_LIST_HEAD(&bridge_vlan->port_vlan_list);
	bridge_vlan->vid = vid;
	list_add(&bridge_vlan->list, &bridge_port->vlans_list);

	return bridge_vlan;
}