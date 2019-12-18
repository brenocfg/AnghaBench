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
typedef  scalar_t__ u16 ;
struct switchdev_obj_port_vlan {scalar_t__ vid_begin; scalar_t__ vid_end; } ;
struct switchdev_notifier_port_obj_info {int handled; int /*<<< orphan*/  obj; } ;
struct net_device {int dummy; } ;
struct mlxsw_sp_bridge_device {int /*<<< orphan*/  vlan_enabled; } ;
struct mlxsw_sp {int /*<<< orphan*/  bridge; } ;

/* Variables and functions */
 struct switchdev_obj_port_vlan* SWITCHDEV_OBJ_PORT_VLAN (int /*<<< orphan*/ ) ; 
 struct mlxsw_sp_bridge_device* mlxsw_sp_bridge_device_find (int /*<<< orphan*/ ,struct net_device*) ; 
 struct mlxsw_sp* mlxsw_sp_lower_get (struct net_device*) ; 
 int /*<<< orphan*/  mlxsw_sp_switchdev_vxlan_vlan_del (struct mlxsw_sp*,struct mlxsw_sp_bridge_device*,struct net_device*,scalar_t__) ; 
 struct net_device* netdev_master_upper_dev_get (struct net_device*) ; 

__attribute__((used)) static void
mlxsw_sp_switchdev_vxlan_vlans_del(struct net_device *vxlan_dev,
				   struct switchdev_notifier_port_obj_info *
				   port_obj_info)
{
	struct switchdev_obj_port_vlan *vlan =
		SWITCHDEV_OBJ_PORT_VLAN(port_obj_info->obj);
	struct mlxsw_sp_bridge_device *bridge_device;
	struct mlxsw_sp *mlxsw_sp;
	struct net_device *br_dev;
	u16 vid;

	br_dev = netdev_master_upper_dev_get(vxlan_dev);
	if (!br_dev)
		return;

	mlxsw_sp = mlxsw_sp_lower_get(br_dev);
	if (!mlxsw_sp)
		return;

	port_obj_info->handled = true;

	bridge_device = mlxsw_sp_bridge_device_find(mlxsw_sp->bridge, br_dev);
	if (!bridge_device)
		return;

	if (!bridge_device->vlan_enabled)
		return;

	for (vid = vlan->vid_begin; vid <= vlan->vid_end; vid++)
		mlxsw_sp_switchdev_vxlan_vlan_del(mlxsw_sp, bridge_device,
						  vxlan_dev, vid);
}