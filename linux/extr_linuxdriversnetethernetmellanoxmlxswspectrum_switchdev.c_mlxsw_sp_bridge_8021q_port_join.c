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
struct netlink_ext_ack {int dummy; } ;
struct mlxsw_sp_port_vlan {int dummy; } ;
struct mlxsw_sp_port {int dummy; } ;
struct mlxsw_sp_bridge_port {int /*<<< orphan*/  dev; } ;
struct mlxsw_sp_bridge_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ is_vlan_dev (int /*<<< orphan*/ ) ; 
 struct mlxsw_sp_port_vlan* mlxsw_sp_port_vlan_find_by_vid (struct mlxsw_sp_port*,int) ; 
 int /*<<< orphan*/  mlxsw_sp_port_vlan_put (struct mlxsw_sp_port_vlan*) ; 

__attribute__((used)) static int
mlxsw_sp_bridge_8021q_port_join(struct mlxsw_sp_bridge_device *bridge_device,
				struct mlxsw_sp_bridge_port *bridge_port,
				struct mlxsw_sp_port *mlxsw_sp_port,
				struct netlink_ext_ack *extack)
{
	struct mlxsw_sp_port_vlan *mlxsw_sp_port_vlan;

	if (is_vlan_dev(bridge_port->dev)) {
		NL_SET_ERR_MSG_MOD(extack, "Can not enslave a VLAN device to a VLAN-aware bridge");
		return -EINVAL;
	}

	mlxsw_sp_port_vlan = mlxsw_sp_port_vlan_find_by_vid(mlxsw_sp_port, 1);
	if (WARN_ON(!mlxsw_sp_port_vlan))
		return -EINVAL;

	/* Let VLAN-aware bridge take care of its own VLANs */
	mlxsw_sp_port_vlan_put(mlxsw_sp_port_vlan);

	return 0;
}