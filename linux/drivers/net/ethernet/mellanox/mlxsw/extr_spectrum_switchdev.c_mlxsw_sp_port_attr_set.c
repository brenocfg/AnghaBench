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
struct TYPE_2__ {int /*<<< orphan*/  mrouter; int /*<<< orphan*/  mc_disabled; int /*<<< orphan*/  vlan_filtering; int /*<<< orphan*/  ageing_time; int /*<<< orphan*/  brport_flags; int /*<<< orphan*/  stp_state; } ;
struct switchdev_attr {int id; TYPE_1__ u; int /*<<< orphan*/  orig_dev; } ;
struct net_device {int dummy; } ;
struct mlxsw_sp_port {int /*<<< orphan*/  mlxsw_sp; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  SWITCHDEV_ATTR_ID_BRIDGE_AGEING_TIME 135 
#define  SWITCHDEV_ATTR_ID_BRIDGE_MC_DISABLED 134 
#define  SWITCHDEV_ATTR_ID_BRIDGE_MROUTER 133 
#define  SWITCHDEV_ATTR_ID_BRIDGE_VLAN_FILTERING 132 
#define  SWITCHDEV_ATTR_ID_PORT_BRIDGE_FLAGS 131 
#define  SWITCHDEV_ATTR_ID_PORT_MROUTER 130 
#define  SWITCHDEV_ATTR_ID_PORT_PRE_BRIDGE_FLAGS 129 
#define  SWITCHDEV_ATTR_ID_PORT_STP_STATE 128 
 int mlxsw_sp_port_attr_br_ageing_set (struct mlxsw_sp_port*,struct switchdev_trans*,int /*<<< orphan*/ ) ; 
 int mlxsw_sp_port_attr_br_flags_set (struct mlxsw_sp_port*,struct switchdev_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlxsw_sp_port_attr_br_mrouter_set (struct mlxsw_sp_port*,struct switchdev_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlxsw_sp_port_attr_br_pre_flags_set (struct mlxsw_sp_port*,struct switchdev_trans*,int /*<<< orphan*/ ) ; 
 int mlxsw_sp_port_attr_br_vlan_set (struct mlxsw_sp_port*,struct switchdev_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlxsw_sp_port_attr_mrouter_set (struct mlxsw_sp_port*,struct switchdev_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlxsw_sp_port_attr_stp_state_set (struct mlxsw_sp_port*,struct switchdev_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlxsw_sp_port_mc_disabled_set (struct mlxsw_sp_port*,struct switchdev_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_span_respin (int /*<<< orphan*/ ) ; 
 struct mlxsw_sp_port* netdev_priv (struct net_device*) ; 
 scalar_t__ switchdev_trans_ph_commit (struct switchdev_trans*) ; 

__attribute__((used)) static int mlxsw_sp_port_attr_set(struct net_device *dev,
				  const struct switchdev_attr *attr,
				  struct switchdev_trans *trans)
{
	struct mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);
	int err;

	switch (attr->id) {
	case SWITCHDEV_ATTR_ID_PORT_STP_STATE:
		err = mlxsw_sp_port_attr_stp_state_set(mlxsw_sp_port, trans,
						       attr->orig_dev,
						       attr->u.stp_state);
		break;
	case SWITCHDEV_ATTR_ID_PORT_PRE_BRIDGE_FLAGS:
		err = mlxsw_sp_port_attr_br_pre_flags_set(mlxsw_sp_port,
							  trans,
							  attr->u.brport_flags);
		break;
	case SWITCHDEV_ATTR_ID_PORT_BRIDGE_FLAGS:
		err = mlxsw_sp_port_attr_br_flags_set(mlxsw_sp_port, trans,
						      attr->orig_dev,
						      attr->u.brport_flags);
		break;
	case SWITCHDEV_ATTR_ID_BRIDGE_AGEING_TIME:
		err = mlxsw_sp_port_attr_br_ageing_set(mlxsw_sp_port, trans,
						       attr->u.ageing_time);
		break;
	case SWITCHDEV_ATTR_ID_BRIDGE_VLAN_FILTERING:
		err = mlxsw_sp_port_attr_br_vlan_set(mlxsw_sp_port, trans,
						     attr->orig_dev,
						     attr->u.vlan_filtering);
		break;
	case SWITCHDEV_ATTR_ID_PORT_MROUTER:
		err = mlxsw_sp_port_attr_mrouter_set(mlxsw_sp_port, trans,
						     attr->orig_dev,
						     attr->u.mrouter);
		break;
	case SWITCHDEV_ATTR_ID_BRIDGE_MC_DISABLED:
		err = mlxsw_sp_port_mc_disabled_set(mlxsw_sp_port, trans,
						    attr->orig_dev,
						    attr->u.mc_disabled);
		break;
	case SWITCHDEV_ATTR_ID_BRIDGE_MROUTER:
		err = mlxsw_sp_port_attr_br_mrouter_set(mlxsw_sp_port, trans,
							attr->orig_dev,
							attr->u.mrouter);
		break;
	default:
		err = -EOPNOTSUPP;
		break;
	}

	if (switchdev_trans_ph_commit(trans))
		mlxsw_sp_span_respin(mlxsw_sp_port->mlxsw_sp);

	return err;
}