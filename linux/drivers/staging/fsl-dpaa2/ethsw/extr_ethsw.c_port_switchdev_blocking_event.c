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
struct notifier_block {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int NOTIFY_DONE ; 
#define  SWITCHDEV_PORT_ATTR_SET 130 
#define  SWITCHDEV_PORT_OBJ_ADD 129 
#define  SWITCHDEV_PORT_OBJ_DEL 128 
 int /*<<< orphan*/  ethsw_port_dev_check (struct net_device*) ; 
 int ethsw_switchdev_port_attr_set_event (struct net_device*,void*) ; 
 int ethsw_switchdev_port_obj_event (unsigned long,struct net_device*,void*) ; 
 struct net_device* switchdev_notifier_info_to_dev (void*) ; 

__attribute__((used)) static int port_switchdev_blocking_event(struct notifier_block *unused,
					 unsigned long event, void *ptr)
{
	struct net_device *dev = switchdev_notifier_info_to_dev(ptr);

	if (!ethsw_port_dev_check(dev))
		return NOTIFY_DONE;

	switch (event) {
	case SWITCHDEV_PORT_OBJ_ADD: /* fall through */
	case SWITCHDEV_PORT_OBJ_DEL:
		return ethsw_switchdev_port_obj_event(event, dev, ptr);
	case SWITCHDEV_PORT_ATTR_SET:
		return ethsw_switchdev_port_attr_set_event(dev, ptr);
	}

	return NOTIFY_DONE;
}