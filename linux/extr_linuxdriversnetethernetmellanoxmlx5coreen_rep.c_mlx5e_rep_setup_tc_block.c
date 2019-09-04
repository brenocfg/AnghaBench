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
struct tc_block_offload {scalar_t__ binder_type; int command; int /*<<< orphan*/  block; int /*<<< orphan*/  extack; } ;
struct net_device {int dummy; } ;
struct mlx5e_priv {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ TCF_BLOCK_BINDER_TYPE_CLSACT_INGRESS ; 
#define  TC_BLOCK_BIND 129 
#define  TC_BLOCK_UNBIND 128 
 int /*<<< orphan*/  mlx5e_rep_setup_tc_cb ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 
 int tcf_block_cb_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mlx5e_priv*,struct mlx5e_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_block_cb_unregister (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mlx5e_priv*) ; 

__attribute__((used)) static int mlx5e_rep_setup_tc_block(struct net_device *dev,
				    struct tc_block_offload *f)
{
	struct mlx5e_priv *priv = netdev_priv(dev);

	if (f->binder_type != TCF_BLOCK_BINDER_TYPE_CLSACT_INGRESS)
		return -EOPNOTSUPP;

	switch (f->command) {
	case TC_BLOCK_BIND:
		return tcf_block_cb_register(f->block, mlx5e_rep_setup_tc_cb,
					     priv, priv, f->extack);
	case TC_BLOCK_UNBIND:
		tcf_block_cb_unregister(f->block, mlx5e_rep_setup_tc_cb, priv);
		return 0;
	default:
		return -EOPNOTSUPP;
	}
}