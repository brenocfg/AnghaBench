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
struct net_device {int dummy; } ;
struct mlxsw_sp_port_vlan {int /*<<< orphan*/  bridge_port; } ;
struct mlxsw_sp_port {int dummy; } ;
struct mlxsw_sp_bridge_port {struct net_device* dev; } ;
struct mlxsw_sp_bridge_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_SP_DEFAULT_VID ; 
 scalar_t__ is_vlan_dev (struct net_device*) ; 
 int /*<<< orphan*/  mlxsw_sp_port_vlan_bridge_leave (struct mlxsw_sp_port_vlan*) ; 
 struct mlxsw_sp_port_vlan* mlxsw_sp_port_vlan_find_by_vid (struct mlxsw_sp_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlan_dev_vlan_id (struct net_device*) ; 

__attribute__((used)) static void
mlxsw_sp_bridge_8021d_port_leave(struct mlxsw_sp_bridge_device *bridge_device,
				 struct mlxsw_sp_bridge_port *bridge_port,
				 struct mlxsw_sp_port *mlxsw_sp_port)
{
	struct mlxsw_sp_port_vlan *mlxsw_sp_port_vlan;
	struct net_device *dev = bridge_port->dev;
	u16 vid;

	vid = is_vlan_dev(dev) ? vlan_dev_vlan_id(dev) : MLXSW_SP_DEFAULT_VID;
	mlxsw_sp_port_vlan = mlxsw_sp_port_vlan_find_by_vid(mlxsw_sp_port, vid);
	if (!mlxsw_sp_port_vlan || !mlxsw_sp_port_vlan->bridge_port)
		return;

	mlxsw_sp_port_vlan_bridge_leave(mlxsw_sp_port_vlan);
}