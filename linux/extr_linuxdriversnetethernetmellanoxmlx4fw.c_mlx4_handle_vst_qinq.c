#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct mlx4_vport_state {scalar_t__ vlan_proto; scalar_t__ default_vlan; scalar_t__ default_qos; } ;
struct TYPE_10__ {scalar_t__ vlan_proto; scalar_t__ default_vlan; scalar_t__ default_qos; } ;
struct mlx4_vport_oper_state {TYPE_5__ state; } ;
struct mlx4_slave_state {int /*<<< orphan*/  vst_qinq_supported; int /*<<< orphan*/  active; } ;
struct TYPE_8__ {struct mlx4_slave_state* slave_state; TYPE_2__* vf_admin; TYPE_1__* vf_oper; } ;
struct TYPE_9__ {TYPE_3__ master; } ;
struct mlx4_priv {int /*<<< orphan*/  dev; TYPE_4__ mfunc; } ;
struct TYPE_7__ {struct mlx4_vport_state* vport; } ;
struct TYPE_6__ {struct mlx4_vport_oper_state* vport; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_8021AD ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int mlx4_activate_vst_qinq (struct mlx4_priv*,int,int) ; 
 int /*<<< orphan*/  mlx4_warn (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int mlx4_handle_vst_qinq(struct mlx4_priv *priv, int slave, int port)
{
	struct mlx4_vport_oper_state *vp_oper;
	struct mlx4_slave_state *slave_state;
	struct mlx4_vport_state *vp_admin;
	int err;

	vp_oper = &priv->mfunc.master.vf_oper[slave].vport[port];
	vp_admin = &priv->mfunc.master.vf_admin[slave].vport[port];
	slave_state = &priv->mfunc.master.slave_state[slave];

	if ((vp_admin->vlan_proto != htons(ETH_P_8021AD)) ||
	    (!slave_state->active))
		return 0;

	if (vp_oper->state.vlan_proto == vp_admin->vlan_proto &&
	    vp_oper->state.default_vlan == vp_admin->default_vlan &&
	    vp_oper->state.default_qos == vp_admin->default_qos)
		return 0;

	if (!slave_state->vst_qinq_supported) {
		/* Warn and revert the request to set vst QinQ mode */
		vp_admin->vlan_proto   = vp_oper->state.vlan_proto;
		vp_admin->default_vlan = vp_oper->state.default_vlan;
		vp_admin->default_qos  = vp_oper->state.default_qos;

		mlx4_warn(&priv->dev,
			  "Slave %d does not support VST QinQ mode\n", slave);
		return 0;
	}

	err = mlx4_activate_vst_qinq(priv, slave, port);
	return err;
}