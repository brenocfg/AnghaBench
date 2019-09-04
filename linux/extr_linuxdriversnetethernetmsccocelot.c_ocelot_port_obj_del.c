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
struct switchdev_obj {int id; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  SWITCHDEV_OBJ_ID_PORT_MDB 129 
#define  SWITCHDEV_OBJ_ID_PORT_VLAN 128 
 int /*<<< orphan*/  SWITCHDEV_OBJ_PORT_MDB (struct switchdev_obj const*) ; 
 int /*<<< orphan*/  SWITCHDEV_OBJ_PORT_VLAN (struct switchdev_obj const*) ; 
 int ocelot_port_obj_del_mdb (struct net_device*,int /*<<< orphan*/ ) ; 
 int ocelot_port_vlan_del_vlan (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocelot_port_obj_del(struct net_device *dev,
			       const struct switchdev_obj *obj)
{
	int ret = 0;

	switch (obj->id) {
	case SWITCHDEV_OBJ_ID_PORT_VLAN:
		ret = ocelot_port_vlan_del_vlan(dev,
						SWITCHDEV_OBJ_PORT_VLAN(obj));
		break;
	case SWITCHDEV_OBJ_ID_PORT_MDB:
		ret = ocelot_port_obj_del_mdb(dev, SWITCHDEV_OBJ_PORT_MDB(obj));
		break;
	default:
		return -EOPNOTSUPP;
	}

	return ret;
}