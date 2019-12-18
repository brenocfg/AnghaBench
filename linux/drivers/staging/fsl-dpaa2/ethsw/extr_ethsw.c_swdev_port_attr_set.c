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
struct TYPE_2__ {int /*<<< orphan*/  brport_flags; int /*<<< orphan*/  stp_state; } ;
struct switchdev_attr {int id; TYPE_1__ u; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  SWITCHDEV_ATTR_ID_BRIDGE_VLAN_FILTERING 131 
#define  SWITCHDEV_ATTR_ID_PORT_BRIDGE_FLAGS 130 
#define  SWITCHDEV_ATTR_ID_PORT_PRE_BRIDGE_FLAGS 129 
#define  SWITCHDEV_ATTR_ID_PORT_STP_STATE 128 
 int port_attr_br_flags_pre_set (struct net_device*,struct switchdev_trans*,int /*<<< orphan*/ ) ; 
 int port_attr_br_flags_set (struct net_device*,struct switchdev_trans*,int /*<<< orphan*/ ) ; 
 int port_attr_stp_state_set (struct net_device*,struct switchdev_trans*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int swdev_port_attr_set(struct net_device *netdev,
			       const struct switchdev_attr *attr,
			       struct switchdev_trans *trans)
{
	int err = 0;

	switch (attr->id) {
	case SWITCHDEV_ATTR_ID_PORT_STP_STATE:
		err = port_attr_stp_state_set(netdev, trans,
					      attr->u.stp_state);
		break;
	case SWITCHDEV_ATTR_ID_PORT_PRE_BRIDGE_FLAGS:
		err = port_attr_br_flags_pre_set(netdev, trans,
						 attr->u.brport_flags);
		break;
	case SWITCHDEV_ATTR_ID_PORT_BRIDGE_FLAGS:
		err = port_attr_br_flags_set(netdev, trans,
					     attr->u.brport_flags);
		break;
	case SWITCHDEV_ATTR_ID_BRIDGE_VLAN_FILTERING:
		/* VLANs are supported by default  */
		break;
	default:
		err = -EOPNOTSUPP;
		break;
	}

	return err;
}