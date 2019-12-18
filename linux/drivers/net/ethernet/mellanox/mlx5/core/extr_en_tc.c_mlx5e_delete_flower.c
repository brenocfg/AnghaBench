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
struct rhashtable {int dummy; } ;
struct net_device {int dummy; } ;
struct mlx5e_tc_flow {int /*<<< orphan*/  node; } ;
struct mlx5e_priv {int dummy; } ;
struct flow_cls_offload {int /*<<< orphan*/  cookie; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELETED ; 
 int EINVAL ; 
 scalar_t__ flow_flag_test_and_set (struct mlx5e_tc_flow*,int /*<<< orphan*/ ) ; 
 struct rhashtable* get_tc_ht (struct mlx5e_priv*,unsigned long) ; 
 int /*<<< orphan*/  mlx5e_flow_put (struct mlx5e_priv*,struct mlx5e_tc_flow*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct mlx5e_tc_flow* rhashtable_lookup_fast (struct rhashtable*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rhashtable_remove_fast (struct rhashtable*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  same_flow_direction (struct mlx5e_tc_flow*,unsigned long) ; 
 int /*<<< orphan*/  tc_ht_params ; 
 int /*<<< orphan*/  trace_mlx5e_delete_flower (struct flow_cls_offload*) ; 

int mlx5e_delete_flower(struct net_device *dev, struct mlx5e_priv *priv,
			struct flow_cls_offload *f, unsigned long flags)
{
	struct rhashtable *tc_ht = get_tc_ht(priv, flags);
	struct mlx5e_tc_flow *flow;
	int err;

	rcu_read_lock();
	flow = rhashtable_lookup_fast(tc_ht, &f->cookie, tc_ht_params);
	if (!flow || !same_flow_direction(flow, flags)) {
		err = -EINVAL;
		goto errout;
	}

	/* Only delete the flow if it doesn't have MLX5E_TC_FLOW_DELETED flag
	 * set.
	 */
	if (flow_flag_test_and_set(flow, DELETED)) {
		err = -EINVAL;
		goto errout;
	}
	rhashtable_remove_fast(tc_ht, &flow->node, tc_ht_params);
	rcu_read_unlock();

	trace_mlx5e_delete_flower(f);
	mlx5e_flow_put(priv, flow);

	return 0;

errout:
	rcu_read_unlock();
	return err;
}