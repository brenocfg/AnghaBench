#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct mlx4_vport_state {int link_state; } ;
struct TYPE_7__ {TYPE_2__* vf_admin; } ;
struct TYPE_8__ {TYPE_3__ master; } ;
struct TYPE_5__ {int /*<<< orphan*/ * do_sense_port; } ;
struct mlx4_priv {TYPE_4__ mfunc; TYPE_1__ sense; } ;
struct mlx4_dev {int dummy; } ;
struct TYPE_6__ {struct mlx4_vport_state* vport; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IFLA_VF_LINK_STATE_AUTO 130 
#define  IFLA_VF_LINK_STATE_DISABLE 129 
#define  IFLA_VF_LINK_STATE_ENABLE 128 
 int /*<<< orphan*/  MLX4_PORT_CHANGE_SUBTYPE_ACTIVE ; 
 int /*<<< orphan*/  MLX4_PORT_CHANGE_SUBTYPE_DOWN ; 
 int /*<<< orphan*/  mlx4_dbg (struct mlx4_dev*,char*,int,int) ; 
 int /*<<< orphan*/  mlx4_gen_port_state_change_eqe (struct mlx4_dev*,int,int,int /*<<< orphan*/ ) ; 
 int mlx4_get_slave_indx (struct mlx4_dev*,int) ; 
 scalar_t__ mlx4_master_immediate_activate_vlan_qos (struct mlx4_priv*,int,int) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 int mlx4_slaves_closest_port (struct mlx4_dev*,int,int) ; 
 int /*<<< orphan*/  mlx4_warn (struct mlx4_dev*,char*,int,int,int) ; 

int mlx4_set_vf_link_state(struct mlx4_dev *dev, int port, int vf, int link_state)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	struct mlx4_vport_state *s_info;
	int slave;
	u8 link_stat_event;

	slave = mlx4_get_slave_indx(dev, vf);
	if (slave < 0)
		return -EINVAL;

	port = mlx4_slaves_closest_port(dev, slave, port);
	switch (link_state) {
	case IFLA_VF_LINK_STATE_AUTO:
		/* get current link state */
		if (!priv->sense.do_sense_port[port])
			link_stat_event = MLX4_PORT_CHANGE_SUBTYPE_ACTIVE;
		else
			link_stat_event = MLX4_PORT_CHANGE_SUBTYPE_DOWN;
	    break;

	case IFLA_VF_LINK_STATE_ENABLE:
		link_stat_event = MLX4_PORT_CHANGE_SUBTYPE_ACTIVE;
	    break;

	case IFLA_VF_LINK_STATE_DISABLE:
		link_stat_event = MLX4_PORT_CHANGE_SUBTYPE_DOWN;
	    break;

	default:
		mlx4_warn(dev, "unknown value for link_state %02x on slave %d port %d\n",
			  link_state, slave, port);
		return -EINVAL;
	}
	s_info = &priv->mfunc.master.vf_admin[slave].vport[port];
	s_info->link_state = link_state;

	/* send event */
	mlx4_gen_port_state_change_eqe(dev, slave, port, link_stat_event);

	if (mlx4_master_immediate_activate_vlan_qos(priv, slave, port))
		mlx4_dbg(dev,
			 "updating vf %d port %d no link state HW enforcement\n",
			 vf, port);
	return 0;
}