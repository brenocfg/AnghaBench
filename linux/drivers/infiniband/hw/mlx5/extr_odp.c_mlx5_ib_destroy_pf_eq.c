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
struct mlx5_ib_pf_eq {int /*<<< orphan*/  pool; int /*<<< orphan*/  wq; int /*<<< orphan*/  work; int /*<<< orphan*/  core; int /*<<< orphan*/  irq_nb; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_destroy (int /*<<< orphan*/ ) ; 
 int mlx5_eq_destroy_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_eq_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mlx5_ib_destroy_pf_eq(struct mlx5_ib_dev *dev, struct mlx5_ib_pf_eq *eq)
{
	int err;

	mlx5_eq_disable(dev->mdev, eq->core, &eq->irq_nb);
	err = mlx5_eq_destroy_generic(dev->mdev, eq->core);
	cancel_work_sync(&eq->work);
	destroy_workqueue(eq->wq);
	mempool_destroy(eq->pool);

	return err;
}