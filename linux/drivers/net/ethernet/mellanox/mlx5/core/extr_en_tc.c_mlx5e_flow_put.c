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
struct mlx5e_tc_flow {int /*<<< orphan*/  refcnt; } ;
struct mlx5e_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree_rcu (struct mlx5e_tc_flow*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_tc_del_flow (struct mlx5e_priv*,struct mlx5e_tc_flow*) ; 
 int /*<<< orphan*/  rcu_head ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlx5e_flow_put(struct mlx5e_priv *priv,
			   struct mlx5e_tc_flow *flow)
{
	if (refcount_dec_and_test(&flow->refcnt)) {
		mlx5e_tc_del_flow(priv, flow);
		kfree_rcu(flow, rcu_head);
	}
}