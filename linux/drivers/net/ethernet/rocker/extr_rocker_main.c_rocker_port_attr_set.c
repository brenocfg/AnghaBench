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
struct TYPE_2__ {int /*<<< orphan*/  ageing_time; int /*<<< orphan*/  brport_flags; int /*<<< orphan*/  stp_state; } ;
struct switchdev_attr {int id; TYPE_1__ u; } ;
struct rocker_port {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  SWITCHDEV_ATTR_ID_BRIDGE_AGEING_TIME 131 
#define  SWITCHDEV_ATTR_ID_PORT_BRIDGE_FLAGS 130 
#define  SWITCHDEV_ATTR_ID_PORT_PRE_BRIDGE_FLAGS 129 
#define  SWITCHDEV_ATTR_ID_PORT_STP_STATE 128 
 struct rocker_port* netdev_priv (struct net_device*) ; 
 int rocker_world_port_attr_bridge_ageing_time_set (struct rocker_port*,int /*<<< orphan*/ ,struct switchdev_trans*) ; 
 int rocker_world_port_attr_bridge_flags_set (struct rocker_port*,int /*<<< orphan*/ ,struct switchdev_trans*) ; 
 int rocker_world_port_attr_pre_bridge_flags_set (struct rocker_port*,int /*<<< orphan*/ ,struct switchdev_trans*) ; 
 int rocker_world_port_attr_stp_state_set (struct rocker_port*,int /*<<< orphan*/ ,struct switchdev_trans*) ; 

__attribute__((used)) static int rocker_port_attr_set(struct net_device *dev,
				const struct switchdev_attr *attr,
				struct switchdev_trans *trans)
{
	struct rocker_port *rocker_port = netdev_priv(dev);
	int err = 0;

	switch (attr->id) {
	case SWITCHDEV_ATTR_ID_PORT_STP_STATE:
		err = rocker_world_port_attr_stp_state_set(rocker_port,
							   attr->u.stp_state,
							   trans);
		break;
	case SWITCHDEV_ATTR_ID_PORT_PRE_BRIDGE_FLAGS:
		err = rocker_world_port_attr_pre_bridge_flags_set(rocker_port,
							      attr->u.brport_flags,
							      trans);
		break;
	case SWITCHDEV_ATTR_ID_PORT_BRIDGE_FLAGS:
		err = rocker_world_port_attr_bridge_flags_set(rocker_port,
							      attr->u.brport_flags,
							      trans);
		break;
	case SWITCHDEV_ATTR_ID_BRIDGE_AGEING_TIME:
		err = rocker_world_port_attr_bridge_ageing_time_set(rocker_port,
								    attr->u.ageing_time,
								    trans);
		break;
	default:
		err = -EOPNOTSUPP;
		break;
	}

	return err;
}