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
struct TYPE_7__ {int /*<<< orphan*/  vhca_id; int /*<<< orphan*/  num; } ;
struct TYPE_8__ {TYPE_3__ vport; } ;
struct mlx5_termtbl_handle {scalar_t__ termtbl; TYPE_4__ dest; } ;
struct mlx5_flow_table {int dummy; } ;
struct mlx5_flow_spec {int dummy; } ;
struct mlx5_flow_handle {scalar_t__ termtbl; TYPE_4__ dest; } ;
struct TYPE_6__ {int /*<<< orphan*/  vhca_id; int /*<<< orphan*/  num; } ;
struct mlx5_flow_destination {scalar_t__ type; scalar_t__ ft; TYPE_2__ vport; } ;
struct mlx5_flow_act {int /*<<< orphan*/  action; } ;
struct mlx5_eswitch {int /*<<< orphan*/  dev; } ;
struct mlx5_esw_flow_attr {TYPE_1__* dests; } ;
typedef  int /*<<< orphan*/  dest ;
struct TYPE_5__ {struct mlx5_termtbl_handle* termtbl; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mlx5_termtbl_handle*) ; 
 int /*<<< orphan*/  MLX5_FLOW_CONTEXT_ACTION_FWD_DEST ; 
 scalar_t__ MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE ; 
 scalar_t__ MLX5_FLOW_DESTINATION_TYPE_VPORT ; 
 int /*<<< orphan*/  esw_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (struct mlx5_flow_destination*,int /*<<< orphan*/ ,int) ; 
 struct mlx5_termtbl_handle* mlx5_add_flow_rules (struct mlx5_flow_table*,struct mlx5_flow_spec*,struct mlx5_flow_act*,struct mlx5_flow_destination*,int) ; 
 int /*<<< orphan*/  mlx5_eswitch_termtbl_actions_move (struct mlx5_flow_act*,struct mlx5_flow_act*) ; 
 struct mlx5_termtbl_handle* mlx5_eswitch_termtbl_get_create (struct mlx5_eswitch*,struct mlx5_flow_act*,struct mlx5_flow_destination*) ; 
 int /*<<< orphan*/  mlx5_eswitch_termtbl_put (struct mlx5_eswitch*,struct mlx5_termtbl_handle*) ; 

struct mlx5_flow_handle *
mlx5_eswitch_add_termtbl_rule(struct mlx5_eswitch *esw,
			      struct mlx5_flow_table *fdb,
			      struct mlx5_flow_spec *spec,
			      struct mlx5_esw_flow_attr *attr,
			      struct mlx5_flow_act *flow_act,
			      struct mlx5_flow_destination *dest,
			      int num_dest)
{
	struct mlx5_flow_act term_tbl_act = {};
	struct mlx5_flow_handle *rule = NULL;
	bool term_table_created = false;
	int num_vport_dests = 0;
	int i, curr_dest;

	mlx5_eswitch_termtbl_actions_move(flow_act, &term_tbl_act);
	term_tbl_act.action |= MLX5_FLOW_CONTEXT_ACTION_FWD_DEST;

	for (i = 0; i < num_dest; i++) {
		struct mlx5_termtbl_handle *tt;

		/* only vport destinations can be terminated */
		if (dest[i].type != MLX5_FLOW_DESTINATION_TYPE_VPORT)
			continue;

		/* get the terminating table for the action list */
		tt = mlx5_eswitch_termtbl_get_create(esw, &term_tbl_act,
						     &dest[i]);
		if (IS_ERR(tt)) {
			esw_warn(esw->dev, "Failed to create termination table\n");
			goto revert_changes;
		}
		attr->dests[num_vport_dests].termtbl = tt;
		num_vport_dests++;

		/* link the destination with the termination table */
		dest[i].type = MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE;
		dest[i].ft = tt->termtbl;
		term_table_created = true;
	}

	/* at least one destination should reference a termination table */
	if (!term_table_created)
		goto revert_changes;

	/* create the FTE */
	rule = mlx5_add_flow_rules(fdb, spec, flow_act, dest, num_dest);
	if (IS_ERR(rule))
		goto revert_changes;

	goto out;

revert_changes:
	/* revert the changes that were made to the original flow_act
	 * and fall-back to the original rule actions
	 */
	mlx5_eswitch_termtbl_actions_move(&term_tbl_act, flow_act);

	for (curr_dest = 0; curr_dest < num_vport_dests; curr_dest++) {
		struct mlx5_termtbl_handle *tt = attr->dests[curr_dest].termtbl;

		/* search for the destination associated with the
		 * current term table
		 */
		for (i = 0; i < num_dest; i++) {
			if (dest[i].ft != tt->termtbl)
				continue;

			memset(&dest[i], 0, sizeof(dest[i]));
			dest[i].type = MLX5_FLOW_DESTINATION_TYPE_VPORT;
			dest[i].vport.num = tt->dest.vport.num;
			dest[i].vport.vhca_id = tt->dest.vport.vhca_id;
			mlx5_eswitch_termtbl_put(esw, tt);
			break;
		}
	}
	rule = mlx5_add_flow_rules(fdb, spec, flow_act, dest, num_dest);
out:
	return rule;
}