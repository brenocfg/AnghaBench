#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct switchdev_trans {int dummy; } ;
struct TYPE_3__ {struct net_device* orig_dev; } ;
struct switchdev_obj_port_vlan {int flags; scalar_t__ vid_begin; scalar_t__ vid_end; TYPE_1__ obj; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct mlxsw_sp_port {struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp_bridge_port {TYPE_2__* bridge_device; } ;
struct mlxsw_sp {int /*<<< orphan*/  bridge; } ;
struct TYPE_4__ {int /*<<< orphan*/  vlan_enabled; } ;

/* Variables and functions */
 int BRIDGE_VLAN_INFO_BRENTRY ; 
 int BRIDGE_VLAN_INFO_PVID ; 
 int BRIDGE_VLAN_INFO_UNTAGGED ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ br_vlan_enabled (struct net_device*) ; 
 int mlxsw_sp_br_ban_rif_pvid_change (struct mlxsw_sp*,struct net_device*,struct switchdev_obj_port_vlan const*) ; 
 struct mlxsw_sp_bridge_port* mlxsw_sp_bridge_port_find (int /*<<< orphan*/ ,struct net_device*) ; 
 int mlxsw_sp_bridge_port_vlan_add (struct mlxsw_sp_port*,struct mlxsw_sp_bridge_port*,scalar_t__,int,int,struct netlink_ext_ack*) ; 
 scalar_t__ netif_is_bridge_master (struct net_device*) ; 
 scalar_t__ switchdev_trans_ph_commit (struct switchdev_trans*) ; 
 scalar_t__ switchdev_trans_ph_prepare (struct switchdev_trans*) ; 

__attribute__((used)) static int mlxsw_sp_port_vlans_add(struct mlxsw_sp_port *mlxsw_sp_port,
				   const struct switchdev_obj_port_vlan *vlan,
				   struct switchdev_trans *trans,
				   struct netlink_ext_ack *extack)
{
	bool flag_untagged = vlan->flags & BRIDGE_VLAN_INFO_UNTAGGED;
	bool flag_pvid = vlan->flags & BRIDGE_VLAN_INFO_PVID;
	struct mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	struct net_device *orig_dev = vlan->obj.orig_dev;
	struct mlxsw_sp_bridge_port *bridge_port;
	u16 vid;

	if (netif_is_bridge_master(orig_dev)) {
		int err = 0;

		if ((vlan->flags & BRIDGE_VLAN_INFO_BRENTRY) &&
		    br_vlan_enabled(orig_dev) &&
		    switchdev_trans_ph_prepare(trans))
			err = mlxsw_sp_br_ban_rif_pvid_change(mlxsw_sp,
							      orig_dev, vlan);
		if (!err)
			err = -EOPNOTSUPP;
		return err;
	}

	if (switchdev_trans_ph_commit(trans))
		return 0;

	bridge_port = mlxsw_sp_bridge_port_find(mlxsw_sp->bridge, orig_dev);
	if (WARN_ON(!bridge_port))
		return -EINVAL;

	if (!bridge_port->bridge_device->vlan_enabled)
		return 0;

	for (vid = vlan->vid_begin; vid <= vlan->vid_end; vid++) {
		int err;

		err = mlxsw_sp_bridge_port_vlan_add(mlxsw_sp_port, bridge_port,
						    vid, flag_untagged,
						    flag_pvid, extack);
		if (err)
			return err;
	}

	return 0;
}