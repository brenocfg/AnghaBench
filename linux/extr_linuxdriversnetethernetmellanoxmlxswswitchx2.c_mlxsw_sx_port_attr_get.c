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
struct TYPE_4__ {TYPE_1__ ppid; } ;
struct switchdev_attr {int id; TYPE_2__ u; } ;
struct net_device {int dummy; } ;
struct mlxsw_sx_port {struct mlxsw_sx* mlxsw_sx; } ;
struct mlxsw_sx {int /*<<< orphan*/  hw_id; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  SWITCHDEV_ATTR_ID_PORT_PARENT_ID 128 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct mlxsw_sx_port* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlxsw_sx_port_attr_get(struct net_device *dev,
				  struct switchdev_attr *attr)
{
	struct mlxsw_sx_port *mlxsw_sx_port = netdev_priv(dev);
	struct mlxsw_sx *mlxsw_sx = mlxsw_sx_port->mlxsw_sx;

	switch (attr->id) {
	case SWITCHDEV_ATTR_ID_PORT_PARENT_ID:
		attr->u.ppid.id_len = sizeof(mlxsw_sx->hw_id);
		memcpy(&attr->u.ppid.id, &mlxsw_sx->hw_id, attr->u.ppid.id_len);
		break;
	default:
		return -EOPNOTSUPP;
	}

	return 0;
}