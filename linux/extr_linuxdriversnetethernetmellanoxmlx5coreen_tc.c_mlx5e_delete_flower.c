#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tc_cls_flower_offload {int /*<<< orphan*/  cookie; } ;
struct rhashtable {int dummy; } ;
struct mlx5e_tc_flow {int /*<<< orphan*/  node; } ;
struct mlx5e_priv {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct rhashtable* get_tc_ht (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  kfree (struct mlx5e_tc_flow*) ; 
 int /*<<< orphan*/  mlx5e_tc_del_flow (struct mlx5e_priv*,struct mlx5e_tc_flow*) ; 
 struct mlx5e_tc_flow* rhashtable_lookup_fast (struct rhashtable*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rhashtable_remove_fast (struct rhashtable*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  same_flow_direction (struct mlx5e_tc_flow*,int) ; 
 int /*<<< orphan*/  tc_ht_params ; 

int mlx5e_delete_flower(struct mlx5e_priv *priv,
			struct tc_cls_flower_offload *f, int flags)
{
	struct rhashtable *tc_ht = get_tc_ht(priv);
	struct mlx5e_tc_flow *flow;

	flow = rhashtable_lookup_fast(tc_ht, &f->cookie, tc_ht_params);
	if (!flow || !same_flow_direction(flow, flags))
		return -EINVAL;

	rhashtable_remove_fast(tc_ht, &flow->node, tc_ht_params);

	mlx5e_tc_del_flow(priv, flow);

	kfree(flow);

	return 0;
}