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
struct mlx5e_tc_flow {int /*<<< orphan*/ * rule; struct mlx5_nic_flow_attr* nic_attr; } ;
struct TYPE_3__ {int /*<<< orphan*/  t_lock; int /*<<< orphan*/ * t; } ;
struct TYPE_4__ {TYPE_1__ tc; } ;
struct mlx5e_priv {TYPE_2__ fs; int /*<<< orphan*/  mdev; } ;
struct mlx5_nic_flow_attr {int action; struct mlx5_fc* counter; } ;
struct mlx5_fc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HAIRPIN ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int MLX5_FLOW_CONTEXT_ACTION_MOD_HDR ; 
 int /*<<< orphan*/  MLX5_TC_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NIC_OFFLOAD ; 
 scalar_t__ flow_flag_test (struct mlx5e_tc_flow*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_del_flow_rules (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_destroy_flow_table (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_fc_destroy (int /*<<< orphan*/ ,struct mlx5_fc*) ; 
 int /*<<< orphan*/  mlx5e_detach_mod_hdr (struct mlx5e_priv*,struct mlx5e_tc_flow*) ; 
 int /*<<< orphan*/  mlx5e_hairpin_flow_del (struct mlx5e_priv*,struct mlx5e_tc_flow*) ; 
 int /*<<< orphan*/  mlx5e_tc_num_filters (struct mlx5e_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlx5e_tc_del_nic_flow(struct mlx5e_priv *priv,
				  struct mlx5e_tc_flow *flow)
{
	struct mlx5_nic_flow_attr *attr = flow->nic_attr;
	struct mlx5_fc *counter = NULL;

	counter = attr->counter;
	if (!IS_ERR_OR_NULL(flow->rule[0]))
		mlx5_del_flow_rules(flow->rule[0]);
	mlx5_fc_destroy(priv->mdev, counter);

	mutex_lock(&priv->fs.tc.t_lock);
	if (!mlx5e_tc_num_filters(priv, MLX5_TC_FLAG(NIC_OFFLOAD)) && priv->fs.tc.t) {
		mlx5_destroy_flow_table(priv->fs.tc.t);
		priv->fs.tc.t = NULL;
	}
	mutex_unlock(&priv->fs.tc.t_lock);

	if (attr->action & MLX5_FLOW_CONTEXT_ACTION_MOD_HDR)
		mlx5e_detach_mod_hdr(priv, flow);

	if (flow_flag_test(flow, HAIRPIN))
		mlx5e_hairpin_flow_del(priv, flow);
}