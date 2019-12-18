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
struct mlx5_devx_event_table {int /*<<< orphan*/  devx_nb; int /*<<< orphan*/  event_xa_lock; int /*<<< orphan*/  event_xa; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; struct mlx5_devx_event_table devx_event_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_NB_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NOTIFY_ANY ; 
 int /*<<< orphan*/  devx_event_notifier ; 
 int /*<<< orphan*/  mlx5_eq_notifier_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xa_init (int /*<<< orphan*/ *) ; 

void mlx5_ib_devx_init_event_table(struct mlx5_ib_dev *dev)
{
	struct mlx5_devx_event_table *table = &dev->devx_event_table;

	xa_init(&table->event_xa);
	mutex_init(&table->event_xa_lock);
	MLX5_NB_INIT(&table->devx_nb, devx_event_notifier, NOTIFY_ANY);
	mlx5_eq_notifier_register(dev->mdev, &table->devx_nb);
}