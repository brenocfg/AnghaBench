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
struct TYPE_3__ {int /*<<< orphan*/ * allowed_vlan; int /*<<< orphan*/  acl; } ;
struct mlx5_vport {TYPE_1__ egress; int /*<<< orphan*/  vport; } ;
struct mlx5_flow_spec {int /*<<< orphan*/  match_criteria_enable; int /*<<< orphan*/  match_value; int /*<<< orphan*/  match_criteria; } ;
struct mlx5_flow_act {int action; int /*<<< orphan*/  member_0; } ;
struct mlx5_eswitch {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  first_vid; int /*<<< orphan*/  cvlan_tag; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MLX5_CAP_GEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_FLOW_CONTEXT_ACTION_ALLOW ; 
 int MLX5_FLOW_CONTEXT_ACTION_VLAN_POP ; 
 int /*<<< orphan*/  MLX5_MATCH_OUTER_HEADERS ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_SET_TO_ONES (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esw_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esw_vport_cleanup_egress_rules (struct mlx5_eswitch*,struct mlx5_vport*) ; 
 int esw_vport_enable_egress_acl (struct mlx5_eswitch*,struct mlx5_vport*) ; 
 int /*<<< orphan*/  esw_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fte_match_param ; 
 int /*<<< orphan*/  kvfree (struct mlx5_flow_spec*) ; 
 struct mlx5_flow_spec* kvzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mlx5_add_flow_rules (int /*<<< orphan*/ ,struct mlx5_flow_spec*,struct mlx5_flow_act*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_warn (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 TYPE_2__ outer_headers ; 
 int /*<<< orphan*/  prio_tag_required ; 

__attribute__((used)) static int esw_vport_egress_prio_tag_config(struct mlx5_eswitch *esw,
					    struct mlx5_vport *vport)
{
	struct mlx5_flow_act flow_act = {0};
	struct mlx5_flow_spec *spec;
	int err = 0;

	if (!MLX5_CAP_GEN(esw->dev, prio_tag_required))
		return 0;

	/* For prio tag mode, there is only 1 FTEs:
	 * 1) prio tag packets - pop the prio tag VLAN, allow
	 * Unmatched traffic is allowed by default
	 */

	esw_vport_cleanup_egress_rules(esw, vport);

	err = esw_vport_enable_egress_acl(esw, vport);
	if (err) {
		mlx5_core_warn(esw->dev,
			       "failed to enable egress acl (%d) on vport[%d]\n",
			       err, vport->vport);
		return err;
	}

	esw_debug(esw->dev,
		  "vport[%d] configure prio tag egress rules\n", vport->vport);

	spec = kvzalloc(sizeof(*spec), GFP_KERNEL);
	if (!spec) {
		err = -ENOMEM;
		goto out_no_mem;
	}

	/* prio tag vlan rule - pop it so VF receives untagged packets */
	MLX5_SET_TO_ONES(fte_match_param, spec->match_criteria, outer_headers.cvlan_tag);
	MLX5_SET_TO_ONES(fte_match_param, spec->match_value, outer_headers.cvlan_tag);
	MLX5_SET_TO_ONES(fte_match_param, spec->match_criteria, outer_headers.first_vid);
	MLX5_SET(fte_match_param, spec->match_value, outer_headers.first_vid, 0);

	spec->match_criteria_enable = MLX5_MATCH_OUTER_HEADERS;
	flow_act.action = MLX5_FLOW_CONTEXT_ACTION_VLAN_POP |
			  MLX5_FLOW_CONTEXT_ACTION_ALLOW;
	vport->egress.allowed_vlan =
		mlx5_add_flow_rules(vport->egress.acl, spec,
				    &flow_act, NULL, 0);
	if (IS_ERR(vport->egress.allowed_vlan)) {
		err = PTR_ERR(vport->egress.allowed_vlan);
		esw_warn(esw->dev,
			 "vport[%d] configure egress pop prio tag vlan rule failed, err(%d)\n",
			 vport->vport, err);
		vport->egress.allowed_vlan = NULL;
		goto out;
	}

out:
	kvfree(spec);
out_no_mem:
	if (err)
		esw_vport_cleanup_egress_rules(esw, vport);
	return err;
}