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
struct mlx5e_tc_flow {int flags; int /*<<< orphan*/ * rule; struct mlx5_nic_flow_attr* nic_attr; } ;
struct TYPE_3__ {int /*<<< orphan*/ * t; } ;
struct TYPE_4__ {TYPE_1__ tc; } ;
struct mlx5e_priv {TYPE_2__ fs; int /*<<< orphan*/  mdev; } ;
struct mlx5_nic_flow_attr {int action; } ;
struct mlx5_fc {int dummy; } ;

/* Variables and functions */
 int MLX5E_TC_FLOW_HAIRPIN ; 
 int MLX5_FLOW_CONTEXT_ACTION_MOD_HDR ; 
 int /*<<< orphan*/  mlx5_del_flow_rules (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_destroy_flow_table (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_fc_destroy (int /*<<< orphan*/ ,struct mlx5_fc*) ; 
 struct mlx5_fc* mlx5_flow_rule_counter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_detach_mod_hdr (struct mlx5e_priv*,struct mlx5e_tc_flow*) ; 
 int /*<<< orphan*/  mlx5e_hairpin_flow_del (struct mlx5e_priv*,struct mlx5e_tc_flow*) ; 
 int /*<<< orphan*/  mlx5e_tc_num_filters (struct mlx5e_priv*) ; 

__attribute__((used)) static void mlx5e_tc_del_nic_flow(struct mlx5e_priv *priv,
				  struct mlx5e_tc_flow *flow)
{
	struct mlx5_nic_flow_attr *attr = flow->nic_attr;
	struct mlx5_fc *counter = NULL;

	counter = mlx5_flow_rule_counter(flow->rule[0]);
	mlx5_del_flow_rules(flow->rule[0]);
	mlx5_fc_destroy(priv->mdev, counter);

	if (!mlx5e_tc_num_filters(priv) && priv->fs.tc.t) {
		mlx5_destroy_flow_table(priv->fs.tc.t);
		priv->fs.tc.t = NULL;
	}

	if (attr->action & MLX5_FLOW_CONTEXT_ACTION_MOD_HDR)
		mlx5e_detach_mod_hdr(priv, flow);

	if (flow->flags & MLX5E_TC_FLOW_HAIRPIN)
		mlx5e_hairpin_flow_del(priv, flow);
}