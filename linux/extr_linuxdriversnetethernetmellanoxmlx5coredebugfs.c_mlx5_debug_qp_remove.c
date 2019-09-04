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
struct mlx5_core_qp {scalar_t__ dbg; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_debugfs_root ; 
 int /*<<< orphan*/  rem_res_tree (scalar_t__) ; 

void mlx5_debug_qp_remove(struct mlx5_core_dev *dev, struct mlx5_core_qp *qp)
{
	if (!mlx5_debugfs_root)
		return;

	if (qp->dbg)
		rem_res_tree(qp->dbg);
}