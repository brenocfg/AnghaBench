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
struct mlx5_core_qp {int /*<<< orphan*/ * dbg; int /*<<< orphan*/  qpn; } ;
struct TYPE_2__ {int /*<<< orphan*/  qp_debugfs; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_DBG_RSC_QP ; 
 int add_res_tree (struct mlx5_core_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mlx5_core_qp*) ; 
 int /*<<< orphan*/  mlx5_debugfs_root ; 
 int /*<<< orphan*/  qp_fields ; 

int mlx5_debug_qp_add(struct mlx5_core_dev *dev, struct mlx5_core_qp *qp)
{
	int err;

	if (!mlx5_debugfs_root)
		return 0;

	err = add_res_tree(dev, MLX5_DBG_RSC_QP, dev->priv.qp_debugfs,
			   &qp->dbg, qp->qpn, qp_fields,
			   ARRAY_SIZE(qp_fields), qp);
	if (err)
		qp->dbg = NULL;

	return err;
}