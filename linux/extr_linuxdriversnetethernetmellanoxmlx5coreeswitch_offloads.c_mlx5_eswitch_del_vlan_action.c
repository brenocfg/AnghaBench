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
struct offloads_fdb {scalar_t__ vlan_push_pop_refcount; } ;
struct mlx5_eswitch_rep {int /*<<< orphan*/  vport; scalar_t__ vlan; scalar_t__ vlan_refcount; } ;
struct TYPE_3__ {struct offloads_fdb offloads; } ;
struct mlx5_eswitch {int /*<<< orphan*/  dev; TYPE_1__ fdb_table; } ;
struct mlx5_esw_flow_attr {int action; TYPE_2__** out_rep; int /*<<< orphan*/  vlan_handled; } ;
struct TYPE_4__ {scalar_t__ vport; } ;

/* Variables and functions */
 scalar_t__ FDB_UPLINK_VPORT ; 
 int MLX5_FLOW_CONTEXT_ACTION_FWD_DEST ; 
 int MLX5_FLOW_CONTEXT_ACTION_VLAN_POP ; 
 int MLX5_FLOW_CONTEXT_ACTION_VLAN_PUSH ; 
 int /*<<< orphan*/  SET_VLAN_STRIP ; 
 int __mlx5_eswitch_set_vport_vlan (struct mlx5_eswitch*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int esw_set_global_vlan_pop (struct mlx5_eswitch*,int /*<<< orphan*/ ) ; 
 struct mlx5_eswitch_rep* esw_vlan_action_get_vport (struct mlx5_esw_flow_attr*,int,int) ; 
 scalar_t__ mlx5_eswitch_vlan_actions_supported (int /*<<< orphan*/ ,int) ; 

int mlx5_eswitch_del_vlan_action(struct mlx5_eswitch *esw,
				 struct mlx5_esw_flow_attr *attr)
{
	struct offloads_fdb *offloads = &esw->fdb_table.offloads;
	struct mlx5_eswitch_rep *vport = NULL;
	bool push, pop, fwd;
	int err = 0;

	/* nop if we're on the vlan push/pop non emulation mode */
	if (mlx5_eswitch_vlan_actions_supported(esw->dev, 1))
		return 0;

	if (!attr->vlan_handled)
		return 0;

	push = !!(attr->action & MLX5_FLOW_CONTEXT_ACTION_VLAN_PUSH);
	pop  = !!(attr->action & MLX5_FLOW_CONTEXT_ACTION_VLAN_POP);
	fwd  = !!(attr->action & MLX5_FLOW_CONTEXT_ACTION_FWD_DEST);

	vport = esw_vlan_action_get_vport(attr, push, pop);

	if (!push && !pop && fwd) {
		/* tracks VF --> wire rules without vlan push action */
		if (attr->out_rep[0]->vport == FDB_UPLINK_VPORT)
			vport->vlan_refcount--;

		return 0;
	}

	if (push) {
		vport->vlan_refcount--;
		if (vport->vlan_refcount)
			goto skip_unset_push;

		vport->vlan = 0;
		err = __mlx5_eswitch_set_vport_vlan(esw, vport->vport,
						    0, 0, SET_VLAN_STRIP);
		if (err)
			goto out;
	}

skip_unset_push:
	offloads->vlan_push_pop_refcount--;
	if (offloads->vlan_push_pop_refcount)
		return 0;

	/* no more vlan rules, stop global vlan pop policy */
	err = esw_set_global_vlan_pop(esw, 0);

out:
	return err;
}