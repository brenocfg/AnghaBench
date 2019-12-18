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
struct mlx4_vport_state {scalar_t__ default_vlan; int /*<<< orphan*/  default_qos; int /*<<< orphan*/  vlan_proto; } ;
struct TYPE_10__ {scalar_t__ default_vlan; int /*<<< orphan*/  default_qos; int /*<<< orphan*/  vlan_proto; } ;
struct mlx4_vport_oper_state {TYPE_5__ state; int /*<<< orphan*/  vlan_idx; } ;
struct TYPE_8__ {TYPE_2__* vf_admin; TYPE_1__* vf_oper; } ;
struct TYPE_9__ {TYPE_3__ master; } ;
struct mlx4_priv {int /*<<< orphan*/  dev; TYPE_4__ mfunc; } ;
struct TYPE_7__ {struct mlx4_vport_state* vport; } ;
struct TYPE_6__ {struct mlx4_vport_oper_state* vport; } ;

/* Variables and functions */
 int /*<<< orphan*/  NO_INDX ; 
 int __mlx4_register_vlan (int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_dbg (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mlx4_warn (int /*<<< orphan*/ *,char*,int,int) ; 

__attribute__((used)) static int mlx4_activate_vst_qinq(struct mlx4_priv *priv, int slave, int port)
{
	struct mlx4_vport_oper_state *vp_oper;
	struct mlx4_vport_state *vp_admin;
	int err;

	vp_oper = &priv->mfunc.master.vf_oper[slave].vport[port];
	vp_admin = &priv->mfunc.master.vf_admin[slave].vport[port];

	if (vp_admin->default_vlan != vp_oper->state.default_vlan) {
		err = __mlx4_register_vlan(&priv->dev, port,
					   vp_admin->default_vlan,
					   &vp_oper->vlan_idx);
		if (err) {
			vp_oper->vlan_idx = NO_INDX;
			mlx4_warn(&priv->dev,
				  "No vlan resources slave %d, port %d\n",
				  slave, port);
			return err;
		}
		mlx4_dbg(&priv->dev, "alloc vlan %d idx  %d slave %d port %d\n",
			 (int)(vp_oper->state.default_vlan),
			 vp_oper->vlan_idx, slave, port);
	}
	vp_oper->state.vlan_proto   = vp_admin->vlan_proto;
	vp_oper->state.default_vlan = vp_admin->default_vlan;
	vp_oper->state.default_qos  = vp_admin->default_qos;

	return 0;
}