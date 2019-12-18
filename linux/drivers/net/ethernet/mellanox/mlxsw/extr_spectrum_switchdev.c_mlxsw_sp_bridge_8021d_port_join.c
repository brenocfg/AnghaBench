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
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct mlxsw_sp_port_vlan {scalar_t__ fid; } ;
struct mlxsw_sp_port {int dummy; } ;
struct mlxsw_sp_bridge_port {struct net_device* dev; } ;
struct mlxsw_sp_bridge_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MLXSW_SP_DEFAULT_VID ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ is_vlan_dev (struct net_device*) ; 
 scalar_t__ mlxsw_sp_port_is_br_member (struct mlxsw_sp_port*,int /*<<< orphan*/ ) ; 
 int mlxsw_sp_port_vlan_bridge_join (struct mlxsw_sp_port_vlan*,struct mlxsw_sp_bridge_port*,struct netlink_ext_ack*) ; 
 struct mlxsw_sp_port_vlan* mlxsw_sp_port_vlan_find_by_vid (struct mlxsw_sp_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_port_vlan_router_leave (struct mlxsw_sp_port_vlan*) ; 
 int /*<<< orphan*/  vlan_dev_vlan_id (struct net_device*) ; 

__attribute__((used)) static int
mlxsw_sp_bridge_8021d_port_join(struct mlxsw_sp_bridge_device *bridge_device,
				struct mlxsw_sp_bridge_port *bridge_port,
				struct mlxsw_sp_port *mlxsw_sp_port,
				struct netlink_ext_ack *extack)
{
	struct mlxsw_sp_port_vlan *mlxsw_sp_port_vlan;
	struct net_device *dev = bridge_port->dev;
	u16 vid;

	vid = is_vlan_dev(dev) ? vlan_dev_vlan_id(dev) : MLXSW_SP_DEFAULT_VID;
	mlxsw_sp_port_vlan = mlxsw_sp_port_vlan_find_by_vid(mlxsw_sp_port, vid);
	if (WARN_ON(!mlxsw_sp_port_vlan))
		return -EINVAL;

	if (mlxsw_sp_port_is_br_member(mlxsw_sp_port, bridge_device->dev)) {
		NL_SET_ERR_MSG_MOD(extack, "Can not bridge VLAN uppers of the same port");
		return -EINVAL;
	}

	/* Port is no longer usable as a router interface */
	if (mlxsw_sp_port_vlan->fid)
		mlxsw_sp_port_vlan_router_leave(mlxsw_sp_port_vlan);

	return mlxsw_sp_port_vlan_bridge_join(mlxsw_sp_port_vlan, bridge_port,
					      extack);
}