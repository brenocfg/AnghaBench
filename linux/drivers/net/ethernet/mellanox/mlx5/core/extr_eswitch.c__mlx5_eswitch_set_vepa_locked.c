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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int /*<<< orphan*/  num; } ;
struct mlx5_flow_spec {TYPE_1__ vport; int /*<<< orphan*/  type; int /*<<< orphan*/  ft; int /*<<< orphan*/  match_criteria_enable; int /*<<< orphan*/  match_criteria; int /*<<< orphan*/  match_value; } ;
struct mlx5_flow_handle {int dummy; } ;
struct mlx5_flow_destination {TYPE_1__ vport; int /*<<< orphan*/  type; int /*<<< orphan*/  ft; int /*<<< orphan*/  match_criteria_enable; int /*<<< orphan*/  match_criteria; int /*<<< orphan*/  match_value; } ;
struct mlx5_flow_act {void* action; } ;
struct TYPE_5__ {struct mlx5_flow_handle* vepa_star_rule; int /*<<< orphan*/  vepa_fdb; struct mlx5_flow_handle* vepa_uplink_rule; int /*<<< orphan*/  fdb; } ;
struct TYPE_6__ {TYPE_2__ legacy; } ;
struct mlx5_eswitch {TYPE_3__ fdb_table; } ;
typedef  int /*<<< orphan*/  dest ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct mlx5_flow_handle*) ; 
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* MLX5_FLOW_CONTEXT_ACTION_FWD_DEST ; 
 int /*<<< orphan*/  MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE ; 
 int /*<<< orphan*/  MLX5_FLOW_DESTINATION_TYPE_VPORT ; 
 int /*<<< orphan*/  MLX5_MATCH_MISC_PARAMETERS ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_SET_TO_ONES (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_VPORT_UPLINK ; 
 int PTR_ERR (struct mlx5_flow_handle*) ; 
 int /*<<< orphan*/  esw_cleanup_vepa_rules (struct mlx5_eswitch*) ; 
 int /*<<< orphan*/  fte_match_param ; 
 int /*<<< orphan*/  fte_match_set_misc ; 
 int /*<<< orphan*/  kvfree (struct mlx5_flow_spec*) ; 
 struct mlx5_flow_spec* kvzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct mlx5_flow_spec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  misc_parameters ; 
 struct mlx5_flow_handle* mlx5_add_flow_rules (int /*<<< orphan*/ ,struct mlx5_flow_spec*,struct mlx5_flow_act*,struct mlx5_flow_spec*,int) ; 
 int /*<<< orphan*/  source_port ; 

__attribute__((used)) static int _mlx5_eswitch_set_vepa_locked(struct mlx5_eswitch *esw,
					 u8 setting)
{
	struct mlx5_flow_destination dest = {};
	struct mlx5_flow_act flow_act = {};
	struct mlx5_flow_handle *flow_rule;
	struct mlx5_flow_spec *spec;
	int err = 0;
	void *misc;

	if (!setting) {
		esw_cleanup_vepa_rules(esw);
		return 0;
	}

	if (esw->fdb_table.legacy.vepa_uplink_rule)
		return 0;

	spec = kvzalloc(sizeof(*spec), GFP_KERNEL);
	if (!spec)
		return -ENOMEM;

	/* Uplink rule forward uplink traffic to FDB */
	misc = MLX5_ADDR_OF(fte_match_param, spec->match_value, misc_parameters);
	MLX5_SET(fte_match_set_misc, misc, source_port, MLX5_VPORT_UPLINK);

	misc = MLX5_ADDR_OF(fte_match_param, spec->match_criteria, misc_parameters);
	MLX5_SET_TO_ONES(fte_match_set_misc, misc, source_port);

	spec->match_criteria_enable = MLX5_MATCH_MISC_PARAMETERS;
	dest.type = MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE;
	dest.ft = esw->fdb_table.legacy.fdb;
	flow_act.action = MLX5_FLOW_CONTEXT_ACTION_FWD_DEST;
	flow_rule = mlx5_add_flow_rules(esw->fdb_table.legacy.vepa_fdb, spec,
					&flow_act, &dest, 1);
	if (IS_ERR(flow_rule)) {
		err = PTR_ERR(flow_rule);
		goto out;
	} else {
		esw->fdb_table.legacy.vepa_uplink_rule = flow_rule;
	}

	/* Star rule to forward all traffic to uplink vport */
	memset(spec, 0, sizeof(*spec));
	memset(&dest, 0, sizeof(dest));
	dest.type = MLX5_FLOW_DESTINATION_TYPE_VPORT;
	dest.vport.num = MLX5_VPORT_UPLINK;
	flow_act.action = MLX5_FLOW_CONTEXT_ACTION_FWD_DEST;
	flow_rule = mlx5_add_flow_rules(esw->fdb_table.legacy.vepa_fdb, spec,
					&flow_act, &dest, 1);
	if (IS_ERR(flow_rule)) {
		err = PTR_ERR(flow_rule);
		goto out;
	} else {
		esw->fdb_table.legacy.vepa_star_rule = flow_rule;
	}

out:
	kvfree(spec);
	if (err)
		esw_cleanup_vepa_rules(esw);
	return err;
}