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
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_ft_underlay_qp {int /*<<< orphan*/  list; int /*<<< orphan*/  qpn; } ;
struct mlx5_flow_root_namespace {int /*<<< orphan*/  chain_lock; int /*<<< orphan*/  underlay_qpns; int /*<<< orphan*/  root_ft; TYPE_3__* cmds; } ;
struct TYPE_5__ {TYPE_1__* steering; } ;
struct mlx5_core_dev {TYPE_2__ priv; } ;
struct TYPE_6__ {int (* update_root_ft ) (struct mlx5_flow_root_namespace*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_4__ {struct mlx5_flow_root_namespace* root_ns; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct mlx5_ft_underlay_qp*) ; 
 struct mlx5_ft_underlay_qp* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct mlx5_flow_root_namespace*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int mlx5_fs_add_rx_underlay_qpn(struct mlx5_core_dev *dev, u32 underlay_qpn)
{
	struct mlx5_flow_root_namespace *root = dev->priv.steering->root_ns;
	struct mlx5_ft_underlay_qp *new_uqp;
	int err = 0;

	new_uqp = kzalloc(sizeof(*new_uqp), GFP_KERNEL);
	if (!new_uqp)
		return -ENOMEM;

	mutex_lock(&root->chain_lock);

	if (!root->root_ft) {
		err = -EINVAL;
		goto update_ft_fail;
	}

	err = root->cmds->update_root_ft(root, root->root_ft, underlay_qpn,
					 false);
	if (err) {
		mlx5_core_warn(dev, "Failed adding underlay QPN (%u) to root FT err(%d)\n",
			       underlay_qpn, err);
		goto update_ft_fail;
	}

	new_uqp->qpn = underlay_qpn;
	list_add_tail(&new_uqp->list, &root->underlay_qpns);

	mutex_unlock(&root->chain_lock);

	return 0;

update_ft_fail:
	mutex_unlock(&root->chain_lock);
	kfree(new_uqp);
	return err;
}