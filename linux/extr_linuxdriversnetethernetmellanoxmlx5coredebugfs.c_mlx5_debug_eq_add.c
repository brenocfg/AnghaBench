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
struct mlx5_eq {int /*<<< orphan*/ * dbg; int /*<<< orphan*/  eqn; } ;
struct TYPE_2__ {int /*<<< orphan*/  eq_debugfs; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_DBG_RSC_EQ ; 
 int add_res_tree (struct mlx5_core_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mlx5_eq*) ; 
 int /*<<< orphan*/  eq_fields ; 
 int /*<<< orphan*/  mlx5_debugfs_root ; 

int mlx5_debug_eq_add(struct mlx5_core_dev *dev, struct mlx5_eq *eq)
{
	int err;

	if (!mlx5_debugfs_root)
		return 0;

	err = add_res_tree(dev, MLX5_DBG_RSC_EQ, dev->priv.eq_debugfs,
			   &eq->dbg, eq->eqn, eq_fields,
			   ARRAY_SIZE(eq_fields), eq);
	if (err)
		eq->dbg = NULL;

	return err;
}