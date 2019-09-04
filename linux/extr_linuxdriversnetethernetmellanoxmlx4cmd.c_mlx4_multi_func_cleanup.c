#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_3__* vf_oper; TYPE_3__* vf_admin; TYPE_3__* slave_state; int /*<<< orphan*/  comm_wq; } ;
struct TYPE_5__ {int /*<<< orphan*/ * comm; TYPE_1__ master; } ;
struct mlx4_priv {TYPE_2__ mfunc; } ;
struct mlx4_dev {int num_slaves; } ;
struct TYPE_6__ {struct TYPE_6__** vlan_filter; } ;

/* Variables and functions */
 int MLX4_MAX_PORTS ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (TYPE_3__*) ; 
 scalar_t__ mlx4_is_master (struct mlx4_dev*) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 

void mlx4_multi_func_cleanup(struct mlx4_dev *dev)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	int i, port;

	if (mlx4_is_master(dev)) {
		flush_workqueue(priv->mfunc.master.comm_wq);
		destroy_workqueue(priv->mfunc.master.comm_wq);
		for (i = 0; i < dev->num_slaves; i++) {
			for (port = 1; port <= MLX4_MAX_PORTS; port++)
				kfree(priv->mfunc.master.slave_state[i].vlan_filter[port]);
		}
		kfree(priv->mfunc.master.slave_state);
		kfree(priv->mfunc.master.vf_admin);
		kfree(priv->mfunc.master.vf_oper);
		dev->num_slaves = 0;
	}

	iounmap(priv->mfunc.comm);
	priv->mfunc.comm = NULL;
}