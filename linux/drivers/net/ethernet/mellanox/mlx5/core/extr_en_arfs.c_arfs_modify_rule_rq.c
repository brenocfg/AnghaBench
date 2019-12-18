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
typedef  size_t u16 ;
struct mlx5e_priv {int /*<<< orphan*/  netdev; TYPE_1__* direct_tir; } ;
struct mlx5_flow_handle {int dummy; } ;
struct mlx5_flow_destination {int /*<<< orphan*/  tir_num; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int /*<<< orphan*/  tirn; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_FLOW_DESTINATION_TYPE_TIR ; 
 int mlx5_modify_rule_destination (struct mlx5_flow_handle*,struct mlx5_flow_destination*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,size_t) ; 

__attribute__((used)) static void arfs_modify_rule_rq(struct mlx5e_priv *priv,
				struct mlx5_flow_handle *rule, u16 rxq)
{
	struct mlx5_flow_destination dst = {};
	int err = 0;

	dst.type = MLX5_FLOW_DESTINATION_TYPE_TIR;
	dst.tir_num = priv->direct_tir[rxq].tirn;
	err =  mlx5_modify_rule_destination(rule, &dst, NULL);
	if (err)
		netdev_warn(priv->netdev,
			    "Failed to modify aRFS rule destination to rq=%d\n", rxq);
}