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
struct switchdev_trans {int dummy; } ;
struct switchdev_obj_port_vlan {int flags; scalar_t__ vid_begin; scalar_t__ vid_end; } ;
struct switchdev_notifier_port_obj_info {int handled; int /*<<< orphan*/  info; struct switchdev_trans* trans; int /*<<< orphan*/  obj; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct mlxsw_sp_bridge_device {int /*<<< orphan*/  vlan_enabled; } ;
struct mlxsw_sp {int /*<<< orphan*/  bridge; } ;

/* Variables and functions */
 int BRIDGE_VLAN_INFO_PVID ; 
 int BRIDGE_VLAN_INFO_UNTAGGED ; 
 int EINVAL ; 
 struct switchdev_obj_port_vlan* SWITCHDEV_OBJ_PORT_VLAN (int /*<<< orphan*/ ) ; 
 struct mlxsw_sp_bridge_device* mlxsw_sp_bridge_device_find (int /*<<< orphan*/ ,struct net_device*) ; 
 struct mlxsw_sp* mlxsw_sp_lower_get (struct net_device*) ; 
 int mlxsw_sp_switchdev_vxlan_vlan_add (struct mlxsw_sp*,struct mlxsw_sp_bridge_device*,struct net_device*,scalar_t__,int,int,struct netlink_ext_ack*) ; 
 struct net_device* netdev_master_upper_dev_get (struct net_device*) ; 
 struct netlink_ext_ack* switchdev_notifier_info_to_extack (int /*<<< orphan*/ *) ; 
 scalar_t__ switchdev_trans_ph_commit (struct switchdev_trans*) ; 

__attribute__((used)) static int
mlxsw_sp_switchdev_vxlan_vlans_add(struct net_device *vxlan_dev,
				   struct switchdev_notifier_port_obj_info *
				   port_obj_info)
{
	struct switchdev_obj_port_vlan *vlan =
		SWITCHDEV_OBJ_PORT_VLAN(port_obj_info->obj);
	bool flag_untagged = vlan->flags & BRIDGE_VLAN_INFO_UNTAGGED;
	bool flag_pvid = vlan->flags & BRIDGE_VLAN_INFO_PVID;
	struct switchdev_trans *trans = port_obj_info->trans;
	struct mlxsw_sp_bridge_device *bridge_device;
	struct netlink_ext_ack *extack;
	struct mlxsw_sp *mlxsw_sp;
	struct net_device *br_dev;
	u16 vid;

	extack = switchdev_notifier_info_to_extack(&port_obj_info->info);
	br_dev = netdev_master_upper_dev_get(vxlan_dev);
	if (!br_dev)
		return 0;

	mlxsw_sp = mlxsw_sp_lower_get(br_dev);
	if (!mlxsw_sp)
		return 0;

	port_obj_info->handled = true;

	if (switchdev_trans_ph_commit(trans))
		return 0;

	bridge_device = mlxsw_sp_bridge_device_find(mlxsw_sp->bridge, br_dev);
	if (!bridge_device)
		return -EINVAL;

	if (!bridge_device->vlan_enabled)
		return 0;

	for (vid = vlan->vid_begin; vid <= vlan->vid_end; vid++) {
		int err;

		err = mlxsw_sp_switchdev_vxlan_vlan_add(mlxsw_sp, bridge_device,
							vxlan_dev, vid,
							flag_untagged,
							flag_pvid, extack);
		if (err)
			return err;
	}

	return 0;
}