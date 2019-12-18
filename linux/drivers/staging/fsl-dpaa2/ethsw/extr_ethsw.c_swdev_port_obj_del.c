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
 int port_mdb_del (struct net_device*,int /*<<< orphan*/ ) ; 
 int port_vlans_del (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int swdev_port_obj_del(struct net_device *netdev,
			      const struct switchdev_obj *obj)
{
	int err;

	switch (obj->id) {
	case SWITCHDEV_OBJ_ID_PORT_VLAN:
		err = port_vlans_del(netdev, SWITCHDEV_OBJ_PORT_VLAN(obj));
		break;
	case SWITCHDEV_OBJ_ID_PORT_MDB:
		err = port_mdb_del(netdev, SWITCHDEV_OBJ_PORT_MDB(obj));
		break;
	default:
		err = -EOPNOTSUPP;
		break;
	}
	return err;
}