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
struct TYPE_5__ {int /*<<< orphan*/ * drop_rule; int /*<<< orphan*/  acl; int /*<<< orphan*/ * allowed_vlan; struct mlx5_fc* drop_counter; } ;
struct TYPE_4__ {int /*<<< orphan*/  vlan; int /*<<< orphan*/  qos; } ;
struct mlx5_vport {TYPE_2__ egress; int /*<<< orphan*/  vport; TYPE_1__ info; } ;
struct mlx5_flow_spec {int /*<<< orphan*/  match_criteria_enable; int /*<<< orphan*/  match_value; int /*<<< orphan*/  match_criteria; } ;
struct mlx5_flow_destination {int /*<<< orphan*/  counter_id; int /*<<< orphan*/  type; int /*<<< orphan*/  member_0; } ;
struct mlx5_flow_act {int /*<<< orphan*/  action; int /*<<< orphan*/  member_0; } ;
struct mlx5_fc {int dummy; } ;
struct mlx5_eswitch {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  first_vid; int /*<<< orphan*/  cvlan_tag; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MLX5_FLOW_CONTEXT_ACTION_ALLOW ; 
 int /*<<< orphan*/  MLX5_FLOW_CONTEXT_ACTION_COUNT ; 
 int /*<<< orphan*/  MLX5_FLOW_CONTEXT_ACTION_DROP ; 
 int /*<<< orphan*/  MLX5_FLOW_DESTINATION_TYPE_COUNTER ; 
 int /*<<< orphan*/  MLX5_MATCH_OUTER_HEADERS ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_SET_TO_ONES (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esw_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esw_vport_cleanup_egress_rules (struct mlx5_eswitch*,struct mlx5_vport*) ; 
 int /*<<< orphan*/  esw_vport_disable_egress_acl (struct mlx5_eswitch*,struct mlx5_vport*) ; 
 int esw_vport_enable_egress_acl (struct mlx5_eswitch*,struct mlx5_vport*) ; 
 int /*<<< orphan*/  esw_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fte_match_param ; 
 int /*<<< orphan*/  kvfree (struct mlx5_flow_spec*) ; 
 struct mlx5_flow_spec* kvzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct mlx5_flow_spec*,int /*<<< orphan*/ ,int) ; 
 void* mlx5_add_flow_rules (int /*<<< orphan*/ ,struct mlx5_flow_spec*,struct mlx5_flow_act*,struct mlx5_flow_destination*,int) ; 
 int /*<<< orphan*/  mlx5_core_warn (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_fc_id (struct mlx5_fc*) ; 
 TYPE_3__ outer_headers ; 

__attribute__((used)) static int esw_vport_egress_config(struct mlx5_eswitch *esw,
				   struct mlx5_vport *vport)
{
	struct mlx5_fc *counter = vport->egress.drop_counter;
	struct mlx5_flow_destination drop_ctr_dst = {0};
	struct mlx5_flow_destination *dst = NULL;
	struct mlx5_flow_act flow_act = {0};
	struct mlx5_flow_spec *spec;
	int dest_num = 0;
	int err = 0;

	esw_vport_cleanup_egress_rules(esw, vport);

	if (!vport->info.vlan && !vport->info.qos) {
		esw_vport_disable_egress_acl(esw, vport);
		return 0;
	}

	err = esw_vport_enable_egress_acl(esw, vport);
	if (err) {
		mlx5_core_warn(esw->dev,
			       "failed to enable egress acl (%d) on vport[%d]\n",
			       err, vport->vport);
		return err;
	}

	esw_debug(esw->dev,
		  "vport[%d] configure egress rules, vlan(%d) qos(%d)\n",
		  vport->vport, vport->info.vlan, vport->info.qos);

	spec = kvzalloc(sizeof(*spec), GFP_KERNEL);
	if (!spec) {
		err = -ENOMEM;
		goto out;
	}

	/* Allowed vlan rule */
	MLX5_SET_TO_ONES(fte_match_param, spec->match_criteria, outer_headers.cvlan_tag);
	MLX5_SET_TO_ONES(fte_match_param, spec->match_value, outer_headers.cvlan_tag);
	MLX5_SET_TO_ONES(fte_match_param, spec->match_criteria, outer_headers.first_vid);
	MLX5_SET(fte_match_param, spec->match_value, outer_headers.first_vid, vport->info.vlan);

	spec->match_criteria_enable = MLX5_MATCH_OUTER_HEADERS;
	flow_act.action = MLX5_FLOW_CONTEXT_ACTION_ALLOW;
	vport->egress.allowed_vlan =
		mlx5_add_flow_rules(vport->egress.acl, spec,
				    &flow_act, NULL, 0);
	if (IS_ERR(vport->egress.allowed_vlan)) {
		err = PTR_ERR(vport->egress.allowed_vlan);
		esw_warn(esw->dev,
			 "vport[%d] configure egress allowed vlan rule failed, err(%d)\n",
			 vport->vport, err);
		vport->egress.allowed_vlan = NULL;
		goto out;
	}

	/* Drop others rule (star rule) */
	memset(spec, 0, sizeof(*spec));
	flow_act.action = MLX5_FLOW_CONTEXT_ACTION_DROP;

	/* Attach egress drop flow counter */
	if (counter) {
		flow_act.action |= MLX5_FLOW_CONTEXT_ACTION_COUNT;
		drop_ctr_dst.type = MLX5_FLOW_DESTINATION_TYPE_COUNTER;
		drop_ctr_dst.counter_id = mlx5_fc_id(counter);
		dst = &drop_ctr_dst;
		dest_num++;
	}
	vport->egress.drop_rule =
		mlx5_add_flow_rules(vport->egress.acl, spec,
				    &flow_act, dst, dest_num);
	if (IS_ERR(vport->egress.drop_rule)) {
		err = PTR_ERR(vport->egress.drop_rule);
		esw_warn(esw->dev,
			 "vport[%d] configure egress drop rule failed, err(%d)\n",
			 vport->vport, err);
		vport->egress.drop_rule = NULL;
	}
out:
	kvfree(spec);
	return err;
}