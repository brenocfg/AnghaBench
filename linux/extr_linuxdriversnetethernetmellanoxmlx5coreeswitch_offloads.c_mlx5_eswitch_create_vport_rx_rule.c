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
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_flow_spec {int /*<<< orphan*/  match_criteria_enable; int /*<<< orphan*/  match_criteria; int /*<<< orphan*/  match_value; } ;
struct mlx5_flow_handle {int dummy; } ;
struct mlx5_flow_destination {int /*<<< orphan*/  tir_num; int /*<<< orphan*/  type; } ;
struct mlx5_flow_act {int /*<<< orphan*/  action; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {int /*<<< orphan*/  ft_offloads; } ;
struct mlx5_eswitch {int /*<<< orphan*/  dev; TYPE_1__ offloads; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct mlx5_flow_handle* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct mlx5_flow_handle*) ; 
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_FLOW_CONTEXT_ACTION_FWD_DEST ; 
 int /*<<< orphan*/  MLX5_FLOW_DESTINATION_TYPE_TIR ; 
 int /*<<< orphan*/  MLX5_MATCH_MISC_PARAMETERS ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MLX5_SET_TO_ONES (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTR_ERR (struct mlx5_flow_handle*) ; 
 int /*<<< orphan*/  esw_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fte_match_param ; 
 int /*<<< orphan*/  fte_match_set_misc ; 
 int /*<<< orphan*/  kvfree (struct mlx5_flow_spec*) ; 
 struct mlx5_flow_spec* kvzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  misc_parameters ; 
 struct mlx5_flow_handle* mlx5_add_flow_rules (int /*<<< orphan*/ ,struct mlx5_flow_spec*,struct mlx5_flow_act*,struct mlx5_flow_destination*,int) ; 
 int /*<<< orphan*/  source_port ; 

struct mlx5_flow_handle *
mlx5_eswitch_create_vport_rx_rule(struct mlx5_eswitch *esw, int vport, u32 tirn)
{
	struct mlx5_flow_act flow_act = {0};
	struct mlx5_flow_destination dest = {};
	struct mlx5_flow_handle *flow_rule;
	struct mlx5_flow_spec *spec;
	void *misc;

	spec = kvzalloc(sizeof(*spec), GFP_KERNEL);
	if (!spec) {
		flow_rule = ERR_PTR(-ENOMEM);
		goto out;
	}

	misc = MLX5_ADDR_OF(fte_match_param, spec->match_value, misc_parameters);
	MLX5_SET(fte_match_set_misc, misc, source_port, vport);

	misc = MLX5_ADDR_OF(fte_match_param, spec->match_criteria, misc_parameters);
	MLX5_SET_TO_ONES(fte_match_set_misc, misc, source_port);

	spec->match_criteria_enable = MLX5_MATCH_MISC_PARAMETERS;
	dest.type = MLX5_FLOW_DESTINATION_TYPE_TIR;
	dest.tir_num = tirn;

	flow_act.action = MLX5_FLOW_CONTEXT_ACTION_FWD_DEST;
	flow_rule = mlx5_add_flow_rules(esw->offloads.ft_offloads, spec,
					&flow_act, &dest, 1);
	if (IS_ERR(flow_rule)) {
		esw_warn(esw->dev, "fs offloads: Failed to add vport rx rule err %ld\n", PTR_ERR(flow_rule));
		goto out;
	}

out:
	kvfree(spec);
	return flow_rule;
}