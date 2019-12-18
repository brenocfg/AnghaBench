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
struct rhashtable {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {int dummy; } ;
struct mlx5e_tc_flow {int /*<<< orphan*/  node; } ;
struct mlx5e_priv {int /*<<< orphan*/  netdev; } ;
struct TYPE_2__ {struct netlink_ext_ack* extack; } ;
struct flow_cls_offload {int /*<<< orphan*/  cookie; TYPE_1__ common; } ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 struct rhashtable* get_tc_ht (struct mlx5e_priv*,unsigned long) ; 
 int /*<<< orphan*/  mlx5e_flow_put (struct mlx5e_priv*,struct mlx5e_tc_flow*) ; 
 int mlx5e_tc_add_flow (struct mlx5e_priv*,struct flow_cls_offload*,unsigned long,struct net_device*,struct mlx5e_tc_flow**) ; 
 int /*<<< orphan*/  netdev_warn_once (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct mlx5e_tc_flow* rhashtable_lookup (struct rhashtable*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int rhashtable_lookup_insert_fast (struct rhashtable*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tc_ht_params ; 
 int /*<<< orphan*/  trace_mlx5e_configure_flower (struct flow_cls_offload*) ; 

int mlx5e_configure_flower(struct net_device *dev, struct mlx5e_priv *priv,
			   struct flow_cls_offload *f, unsigned long flags)
{
	struct netlink_ext_ack *extack = f->common.extack;
	struct rhashtable *tc_ht = get_tc_ht(priv, flags);
	struct mlx5e_tc_flow *flow;
	int err = 0;

	rcu_read_lock();
	flow = rhashtable_lookup(tc_ht, &f->cookie, tc_ht_params);
	rcu_read_unlock();
	if (flow) {
		NL_SET_ERR_MSG_MOD(extack,
				   "flow cookie already exists, ignoring");
		netdev_warn_once(priv->netdev,
				 "flow cookie %lx already exists, ignoring\n",
				 f->cookie);
		err = -EEXIST;
		goto out;
	}

	trace_mlx5e_configure_flower(f);
	err = mlx5e_tc_add_flow(priv, f, flags, dev, &flow);
	if (err)
		goto out;

	err = rhashtable_lookup_insert_fast(tc_ht, &flow->node, tc_ht_params);
	if (err)
		goto err_free;

	return 0;

err_free:
	mlx5e_flow_put(priv, flow);
out:
	return err;
}