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
struct switchdev_notifier_port_obj_info {int handled; int /*<<< orphan*/  obj; int /*<<< orphan*/  trans; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  SWITCHDEV_PORT_OBJ_ADD 129 
#define  SWITCHDEV_PORT_OBJ_DEL 128 
 int notifier_from_errno (int) ; 
 int swdev_port_obj_add (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int swdev_port_obj_del (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ethsw_switchdev_port_obj_event(unsigned long event, struct net_device *netdev,
			struct switchdev_notifier_port_obj_info *port_obj_info)
{
	int err = -EOPNOTSUPP;

	switch (event) {
	case SWITCHDEV_PORT_OBJ_ADD:
		err = swdev_port_obj_add(netdev, port_obj_info->obj,
					 port_obj_info->trans);
		break;
	case SWITCHDEV_PORT_OBJ_DEL:
		err = swdev_port_obj_del(netdev, port_obj_info->obj);
		break;
	}

	port_obj_info->handled = true;
	return notifier_from_errno(err);
}