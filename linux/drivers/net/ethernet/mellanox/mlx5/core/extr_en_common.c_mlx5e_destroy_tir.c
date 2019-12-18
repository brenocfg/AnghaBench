#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mlx5e_tir {int /*<<< orphan*/  list; int /*<<< orphan*/  tirn; } ;
struct TYPE_3__ {int /*<<< orphan*/  list_lock; } ;
struct TYPE_4__ {TYPE_1__ td; } ;
struct mlx5_core_dev {TYPE_2__ mlx5e_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_core_destroy_tir (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void mlx5e_destroy_tir(struct mlx5_core_dev *mdev,
		       struct mlx5e_tir *tir)
{
	mutex_lock(&mdev->mlx5e_res.td.list_lock);
	mlx5_core_destroy_tir(mdev, tir->tirn);
	list_del(&tir->list);
	mutex_unlock(&mdev->mlx5e_res.td.list_lock);
}