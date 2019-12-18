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
struct switchdev_notifier_port_obj_info {TYPE_1__* obj; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int id; } ;

/* Variables and functions */
#define  SWITCHDEV_OBJ_ID_PORT_VLAN 128 
 int /*<<< orphan*/  mlxsw_sp_switchdev_vxlan_vlans_del (struct net_device*,struct switchdev_notifier_port_obj_info*) ; 

__attribute__((used)) static void
mlxsw_sp_switchdev_handle_vxlan_obj_del(struct net_device *vxlan_dev,
					struct switchdev_notifier_port_obj_info *
					port_obj_info)
{
	switch (port_obj_info->obj->id) {
	case SWITCHDEV_OBJ_ID_PORT_VLAN:
		mlxsw_sp_switchdev_vxlan_vlans_del(vxlan_dev, port_obj_info);
		break;
	default:
		break;
	}
}