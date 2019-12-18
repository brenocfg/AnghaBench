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
struct TYPE_2__ {int /*<<< orphan*/  pg_wq; int /*<<< orphan*/  pg_nb; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_eq_notifier_unregister (struct mlx5_core_dev*,int /*<<< orphan*/ *) ; 

void mlx5_pagealloc_stop(struct mlx5_core_dev *dev)
{
	mlx5_eq_notifier_unregister(dev, &dev->priv.pg_nb);
	flush_workqueue(dev->priv.pg_wq);
}