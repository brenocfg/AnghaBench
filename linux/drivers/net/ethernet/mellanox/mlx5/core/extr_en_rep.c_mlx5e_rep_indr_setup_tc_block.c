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
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tc_indr_block_priv_list; } ;
struct mlx5e_rep_priv {TYPE_1__ uplink_priv; } ;
struct mlx5e_rep_indr_block_priv {int /*<<< orphan*/  list; struct mlx5e_rep_priv* rpriv; struct net_device* netdev; } ;
struct flow_block_offload {scalar_t__ binder_type; int unlocked_driver_cb; int command; int /*<<< orphan*/  block; int /*<<< orphan*/ * driver_block_list; } ;
struct flow_block_cb {int /*<<< orphan*/  driver_list; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENOENT ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
#define  FLOW_BLOCK_BIND 129 
 scalar_t__ FLOW_BLOCK_BINDER_TYPE_CLSACT_INGRESS ; 
#define  FLOW_BLOCK_UNBIND 128 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR (struct flow_block_cb*) ; 
 int PTR_ERR (struct flow_block_cb*) ; 
 int /*<<< orphan*/  flow_block_cb_add (struct flow_block_cb*,struct flow_block_offload*) ; 
 struct flow_block_cb* flow_block_cb_alloc (int /*<<< orphan*/ ,struct mlx5e_rep_indr_block_priv*,struct mlx5e_rep_indr_block_priv*,int /*<<< orphan*/ ) ; 
 struct flow_block_cb* flow_block_cb_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mlx5e_rep_indr_block_priv*) ; 
 int /*<<< orphan*/  flow_block_cb_remove (struct flow_block_cb*,struct flow_block_offload*) ; 
 int /*<<< orphan*/  kfree (struct mlx5e_rep_indr_block_priv*) ; 
 struct mlx5e_rep_indr_block_priv* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_block_cb_list ; 
 struct mlx5e_rep_indr_block_priv* mlx5e_rep_indr_block_priv_lookup (struct mlx5e_rep_priv*,struct net_device*) ; 
 int /*<<< orphan*/  mlx5e_rep_indr_setup_block_cb ; 
 int /*<<< orphan*/  mlx5e_rep_indr_tc_block_unbind ; 

__attribute__((used)) static int
mlx5e_rep_indr_setup_tc_block(struct net_device *netdev,
			      struct mlx5e_rep_priv *rpriv,
			      struct flow_block_offload *f)
{
	struct mlx5e_rep_indr_block_priv *indr_priv;
	struct flow_block_cb *block_cb;

	if (f->binder_type != FLOW_BLOCK_BINDER_TYPE_CLSACT_INGRESS)
		return -EOPNOTSUPP;

	f->unlocked_driver_cb = true;
	f->driver_block_list = &mlx5e_block_cb_list;

	switch (f->command) {
	case FLOW_BLOCK_BIND:
		indr_priv = mlx5e_rep_indr_block_priv_lookup(rpriv, netdev);
		if (indr_priv)
			return -EEXIST;

		indr_priv = kmalloc(sizeof(*indr_priv), GFP_KERNEL);
		if (!indr_priv)
			return -ENOMEM;

		indr_priv->netdev = netdev;
		indr_priv->rpriv = rpriv;
		list_add(&indr_priv->list,
			 &rpriv->uplink_priv.tc_indr_block_priv_list);

		block_cb = flow_block_cb_alloc(mlx5e_rep_indr_setup_block_cb,
					       indr_priv, indr_priv,
					       mlx5e_rep_indr_tc_block_unbind);
		if (IS_ERR(block_cb)) {
			list_del(&indr_priv->list);
			kfree(indr_priv);
			return PTR_ERR(block_cb);
		}
		flow_block_cb_add(block_cb, f);
		list_add_tail(&block_cb->driver_list, &mlx5e_block_cb_list);

		return 0;
	case FLOW_BLOCK_UNBIND:
		indr_priv = mlx5e_rep_indr_block_priv_lookup(rpriv, netdev);
		if (!indr_priv)
			return -ENOENT;

		block_cb = flow_block_cb_lookup(f->block,
						mlx5e_rep_indr_setup_block_cb,
						indr_priv);
		if (!block_cb)
			return -ENOENT;

		flow_block_cb_remove(block_cb, f);
		list_del(&block_cb->driver_list);
		return 0;
	default:
		return -EOPNOTSUPP;
	}
	return 0;
}