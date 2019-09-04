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
struct TYPE_3__ {int id_len; int /*<<< orphan*/  id; } ;
struct TYPE_4__ {int brport_flags_support; int /*<<< orphan*/  brport_flags; TYPE_1__ ppid; } ;
struct switchdev_attr {int id; TYPE_2__ u; int /*<<< orphan*/  orig_dev; } ;
struct net_device {int dummy; } ;
struct mlxsw_sp_port {struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp {int /*<<< orphan*/  bridge; int /*<<< orphan*/  base_mac; } ;

/* Variables and functions */
 int BR_FLOOD ; 
 int BR_LEARNING ; 
 int BR_MCAST_FLOOD ; 
 int EOPNOTSUPP ; 
#define  SWITCHDEV_ATTR_ID_PORT_BRIDGE_FLAGS 130 
#define  SWITCHDEV_ATTR_ID_PORT_BRIDGE_FLAGS_SUPPORT 129 
#define  SWITCHDEV_ATTR_ID_PORT_PARENT_ID 128 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mlxsw_sp_port_bridge_flags_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mlxsw_sp_port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlxsw_sp_port_attr_get(struct net_device *dev,
				  struct switchdev_attr *attr)
{
	struct mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);
	struct mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;

	switch (attr->id) {
	case SWITCHDEV_ATTR_ID_PORT_PARENT_ID:
		attr->u.ppid.id_len = sizeof(mlxsw_sp->base_mac);
		memcpy(&attr->u.ppid.id, &mlxsw_sp->base_mac,
		       attr->u.ppid.id_len);
		break;
	case SWITCHDEV_ATTR_ID_PORT_BRIDGE_FLAGS:
		mlxsw_sp_port_bridge_flags_get(mlxsw_sp->bridge, attr->orig_dev,
					       &attr->u.brport_flags);
		break;
	case SWITCHDEV_ATTR_ID_PORT_BRIDGE_FLAGS_SUPPORT:
		attr->u.brport_flags_support = BR_LEARNING | BR_FLOOD |
					       BR_MCAST_FLOOD;
		break;
	default:
		return -EOPNOTSUPP;
	}

	return 0;
}