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
struct TYPE_5__ {int /*<<< orphan*/ * allow_rule; int /*<<< orphan*/  acl; int /*<<< orphan*/  modify_metadata; scalar_t__ modify_metadata_rule; } ;
struct mlx5_vport {TYPE_2__ ingress; int /*<<< orphan*/  vport; } ;
struct mlx5_flow_spec {int /*<<< orphan*/  match_criteria_enable; int /*<<< orphan*/  match_value; int /*<<< orphan*/  match_criteria; } ;
struct mlx5_flow_act {int action; int /*<<< orphan*/  modify_hdr; TYPE_1__* vlan; int /*<<< orphan*/  member_0; } ;
struct mlx5_eswitch {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  cvlan_tag; } ;
struct TYPE_4__ {scalar_t__ prio; scalar_t__ vid; int /*<<< orphan*/  ethtype; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int MLX5_FLOW_CONTEXT_ACTION_ALLOW ; 
 int MLX5_FLOW_CONTEXT_ACTION_MOD_HDR ; 
 int MLX5_FLOW_CONTEXT_ACTION_VLAN_PUSH ; 
 int /*<<< orphan*/  MLX5_MATCH_OUTER_HEADERS ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_SET_TO_ONES (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esw_vport_cleanup_ingress_rules (struct mlx5_eswitch*,struct mlx5_vport*) ; 
 int /*<<< orphan*/  esw_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fte_match_param ; 
 int /*<<< orphan*/  kvfree (struct mlx5_flow_spec*) ; 
 struct mlx5_flow_spec* kvzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mlx5_add_flow_rules (int /*<<< orphan*/ ,struct mlx5_flow_spec*,struct mlx5_flow_act*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__ outer_headers ; 

__attribute__((used)) static int esw_vport_ingress_prio_tag_config(struct mlx5_eswitch *esw,
					     struct mlx5_vport *vport)
{
	struct mlx5_flow_act flow_act = {0};
	struct mlx5_flow_spec *spec;
	int err = 0;

	/* For prio tag mode, there is only 1 FTEs:
	 * 1) Untagged packets - push prio tag VLAN and modify metadata if
	 * required, allow
	 * Unmatched traffic is allowed by default
	 */

	spec = kvzalloc(sizeof(*spec), GFP_KERNEL);
	if (!spec) {
		err = -ENOMEM;
		goto out_no_mem;
	}

	/* Untagged packets - push prio tag VLAN, allow */
	MLX5_SET_TO_ONES(fte_match_param, spec->match_criteria, outer_headers.cvlan_tag);
	MLX5_SET(fte_match_param, spec->match_value, outer_headers.cvlan_tag, 0);
	spec->match_criteria_enable = MLX5_MATCH_OUTER_HEADERS;
	flow_act.action = MLX5_FLOW_CONTEXT_ACTION_VLAN_PUSH |
			  MLX5_FLOW_CONTEXT_ACTION_ALLOW;
	flow_act.vlan[0].ethtype = ETH_P_8021Q;
	flow_act.vlan[0].vid = 0;
	flow_act.vlan[0].prio = 0;

	if (vport->ingress.modify_metadata_rule) {
		flow_act.action |= MLX5_FLOW_CONTEXT_ACTION_MOD_HDR;
		flow_act.modify_hdr = vport->ingress.modify_metadata;
	}

	vport->ingress.allow_rule =
		mlx5_add_flow_rules(vport->ingress.acl, spec,
				    &flow_act, NULL, 0);
	if (IS_ERR(vport->ingress.allow_rule)) {
		err = PTR_ERR(vport->ingress.allow_rule);
		esw_warn(esw->dev,
			 "vport[%d] configure ingress untagged allow rule, err(%d)\n",
			 vport->vport, err);
		vport->ingress.allow_rule = NULL;
		goto out;
	}

out:
	kvfree(spec);
out_no_mem:
	if (err)
		esw_vport_cleanup_ingress_rules(esw, vport);
	return err;
}