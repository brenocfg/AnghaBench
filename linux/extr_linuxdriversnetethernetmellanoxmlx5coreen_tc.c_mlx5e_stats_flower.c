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
typedef  int /*<<< orphan*/  u64 ;
struct tc_cls_flower_offload {int /*<<< orphan*/  exts; int /*<<< orphan*/  cookie; } ;
struct rhashtable {int dummy; } ;
struct mlx5e_tc_flow {int flags; int /*<<< orphan*/ * rule; } ;
struct mlx5e_priv {int dummy; } ;
struct mlx5_fc {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int MLX5E_TC_FLOW_OFFLOADED ; 
 struct rhashtable* get_tc_ht (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5_fc_query_cached (struct mlx5_fc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct mlx5_fc* mlx5_flow_rule_counter (int /*<<< orphan*/ ) ; 
 struct mlx5e_tc_flow* rhashtable_lookup_fast (struct rhashtable*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  same_flow_direction (struct mlx5e_tc_flow*,int) ; 
 int /*<<< orphan*/  tc_ht_params ; 
 int /*<<< orphan*/  tcf_exts_stats_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mlx5e_stats_flower(struct mlx5e_priv *priv,
		       struct tc_cls_flower_offload *f, int flags)
{
	struct rhashtable *tc_ht = get_tc_ht(priv);
	struct mlx5e_tc_flow *flow;
	struct mlx5_fc *counter;
	u64 bytes;
	u64 packets;
	u64 lastuse;

	flow = rhashtable_lookup_fast(tc_ht, &f->cookie, tc_ht_params);
	if (!flow || !same_flow_direction(flow, flags))
		return -EINVAL;

	if (!(flow->flags & MLX5E_TC_FLOW_OFFLOADED))
		return 0;

	counter = mlx5_flow_rule_counter(flow->rule[0]);
	if (!counter)
		return 0;

	mlx5_fc_query_cached(counter, &bytes, &packets, &lastuse);

	tcf_exts_stats_update(f->exts, bytes, packets, lastuse);

	return 0;
}