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
struct mlx5_ib_rwq_ind_table {int /*<<< orphan*/  uid; int /*<<< orphan*/  rqtn; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;
struct ib_rwq_ind_table {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mlx5_ib_rwq_ind_table*) ; 
 int /*<<< orphan*/  mlx5_cmd_destroy_rqt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlx5_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 
 struct mlx5_ib_rwq_ind_table* to_mrwq_ind_table (struct ib_rwq_ind_table*) ; 

int mlx5_ib_destroy_rwq_ind_table(struct ib_rwq_ind_table *ib_rwq_ind_tbl)
{
	struct mlx5_ib_rwq_ind_table *rwq_ind_tbl = to_mrwq_ind_table(ib_rwq_ind_tbl);
	struct mlx5_ib_dev *dev = to_mdev(ib_rwq_ind_tbl->device);

	mlx5_cmd_destroy_rqt(dev->mdev, rwq_ind_tbl->rqtn, rwq_ind_tbl->uid);

	kfree(rwq_ind_tbl);
	return 0;
}