#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct offloads_fdb {int /*<<< orphan*/  vlan_push_pop_refcount; } ;
struct mlx5_eswitch_rep {scalar_t__ vlan_refcount; int /*<<< orphan*/  vlan; int /*<<< orphan*/  vport; } ;
struct TYPE_4__ {struct offloads_fdb offloads; } ;
struct mlx5_eswitch {int /*<<< orphan*/  state_lock; int /*<<< orphan*/  dev; TYPE_1__ fdb_table; } ;
struct mlx5_esw_flow_attr {int action; int vlan_handled; int /*<<< orphan*/ * vlan_vid; TYPE_3__* dests; int /*<<< orphan*/  dest_chain; } ;
struct TYPE_6__ {TYPE_2__* rep; } ;
struct TYPE_5__ {scalar_t__ vport; } ;

/* Variables and functions */
 int MLX5_FLOW_CONTEXT_ACTION_FWD_DEST ; 
 int MLX5_FLOW_CONTEXT_ACTION_VLAN_POP ; 
 int MLX5_FLOW_CONTEXT_ACTION_VLAN_PUSH ; 
 scalar_t__ MLX5_VPORT_UPLINK ; 
 int SET_VLAN_INSERT ; 
 int SET_VLAN_STRIP ; 
 int __mlx5_eswitch_set_vport_vlan (struct mlx5_eswitch*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int esw_add_vlan_action_check (struct mlx5_esw_flow_attr*,int,int,int) ; 
 int esw_set_global_vlan_pop (struct mlx5_eswitch*,int) ; 
 struct mlx5_eswitch_rep* esw_vlan_action_get_vport (struct mlx5_esw_flow_attr*,int,int) ; 
 scalar_t__ mlx5_eswitch_vlan_actions_supported (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int mlx5_eswitch_add_vlan_action(struct mlx5_eswitch *esw,
				 struct mlx5_esw_flow_attr *attr)
{
	struct offloads_fdb *offloads = &esw->fdb_table.offloads;
	struct mlx5_eswitch_rep *vport = NULL;
	bool push, pop, fwd;
	int err = 0;

	/* nop if we're on the vlan push/pop non emulation mode */
	if (mlx5_eswitch_vlan_actions_supported(esw->dev, 1))
		return 0;

	push = !!(attr->action & MLX5_FLOW_CONTEXT_ACTION_VLAN_PUSH);
	pop  = !!(attr->action & MLX5_FLOW_CONTEXT_ACTION_VLAN_POP);
	fwd  = !!((attr->action & MLX5_FLOW_CONTEXT_ACTION_FWD_DEST) &&
		   !attr->dest_chain);

	mutex_lock(&esw->state_lock);

	err = esw_add_vlan_action_check(attr, push, pop, fwd);
	if (err)
		goto unlock;

	attr->vlan_handled = false;

	vport = esw_vlan_action_get_vport(attr, push, pop);

	if (!push && !pop && fwd) {
		/* tracks VF --> wire rules without vlan push action */
		if (attr->dests[0].rep->vport == MLX5_VPORT_UPLINK) {
			vport->vlan_refcount++;
			attr->vlan_handled = true;
		}

		goto unlock;
	}

	if (!push && !pop)
		goto unlock;

	if (!(offloads->vlan_push_pop_refcount)) {
		/* it's the 1st vlan rule, apply global vlan pop policy */
		err = esw_set_global_vlan_pop(esw, SET_VLAN_STRIP);
		if (err)
			goto out;
	}
	offloads->vlan_push_pop_refcount++;

	if (push) {
		if (vport->vlan_refcount)
			goto skip_set_push;

		err = __mlx5_eswitch_set_vport_vlan(esw, vport->vport, attr->vlan_vid[0], 0,
						    SET_VLAN_INSERT | SET_VLAN_STRIP);
		if (err)
			goto out;
		vport->vlan = attr->vlan_vid[0];
skip_set_push:
		vport->vlan_refcount++;
	}
out:
	if (!err)
		attr->vlan_handled = true;
unlock:
	mutex_unlock(&esw->state_lock);
	return err;
}