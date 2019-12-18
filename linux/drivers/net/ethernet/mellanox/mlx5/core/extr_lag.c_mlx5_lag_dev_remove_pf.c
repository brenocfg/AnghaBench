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
struct mlx5_lag {TYPE_2__* pf; } ;
struct TYPE_3__ {int /*<<< orphan*/ * lag; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;
struct TYPE_4__ {struct mlx5_core_dev* dev; } ;

/* Variables and functions */
 int MLX5_MAX_PORTS ; 
 int /*<<< orphan*/  lag_mutex ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlx5_lag_dev_remove_pf(struct mlx5_lag *ldev,
				   struct mlx5_core_dev *dev)
{
	int i;

	for (i = 0; i < MLX5_MAX_PORTS; i++)
		if (ldev->pf[i].dev == dev)
			break;

	if (i == MLX5_MAX_PORTS)
		return;

	mutex_lock(&lag_mutex);
	memset(&ldev->pf[i], 0, sizeof(*ldev->pf));

	dev->priv.lag = NULL;
	mutex_unlock(&lag_mutex);
}