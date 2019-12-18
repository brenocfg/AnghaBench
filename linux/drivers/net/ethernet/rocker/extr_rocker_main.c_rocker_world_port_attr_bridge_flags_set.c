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
struct switchdev_trans {int dummy; } ;
struct rocker_world_ops {int (* port_attr_bridge_flags_set ) (struct rocker_port*,unsigned long,struct switchdev_trans*) ;} ;
struct rocker_port {TYPE_1__* rocker; } ;
struct TYPE_2__ {struct rocker_world_ops* wops; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int stub1 (struct rocker_port*,unsigned long,struct switchdev_trans*) ; 
 scalar_t__ switchdev_trans_ph_prepare (struct switchdev_trans*) ; 

__attribute__((used)) static int
rocker_world_port_attr_bridge_flags_set(struct rocker_port *rocker_port,
					unsigned long brport_flags,
					struct switchdev_trans *trans)
{
	struct rocker_world_ops *wops = rocker_port->rocker->wops;

	if (!wops->port_attr_bridge_flags_set)
		return -EOPNOTSUPP;

	if (switchdev_trans_ph_prepare(trans))
		return 0;

	return wops->port_attr_bridge_flags_set(rocker_port, brport_flags,
						trans);
}