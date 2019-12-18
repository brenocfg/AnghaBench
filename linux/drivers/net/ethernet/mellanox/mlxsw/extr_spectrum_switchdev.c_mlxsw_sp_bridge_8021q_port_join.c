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
struct netlink_ext_ack {int dummy; } ;
struct mlxsw_sp_port {TYPE_1__* default_vlan; } ;
struct mlxsw_sp_bridge_port {int /*<<< orphan*/  dev; } ;
struct mlxsw_sp_bridge_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ fid; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 scalar_t__ is_vlan_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_port_vlan_router_leave (TYPE_1__*) ; 

__attribute__((used)) static int
mlxsw_sp_bridge_8021q_port_join(struct mlxsw_sp_bridge_device *bridge_device,
				struct mlxsw_sp_bridge_port *bridge_port,
				struct mlxsw_sp_port *mlxsw_sp_port,
				struct netlink_ext_ack *extack)
{
	if (is_vlan_dev(bridge_port->dev)) {
		NL_SET_ERR_MSG_MOD(extack, "Can not enslave a VLAN device to a VLAN-aware bridge");
		return -EINVAL;
	}

	/* Port is no longer usable as a router interface */
	if (mlxsw_sp_port->default_vlan->fid)
		mlxsw_sp_port_vlan_router_leave(mlxsw_sp_port->default_vlan);

	return 0;
}