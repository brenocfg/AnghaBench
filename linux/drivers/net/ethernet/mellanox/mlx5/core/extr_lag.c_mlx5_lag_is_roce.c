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
struct mlx5_lag {int dummy; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ __mlx5_lag_is_roce (struct mlx5_lag*) ; 
 int /*<<< orphan*/  lag_mutex ; 
 struct mlx5_lag* mlx5_lag_dev_get (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

bool mlx5_lag_is_roce(struct mlx5_core_dev *dev)
{
	struct mlx5_lag *ldev;
	bool res;

	mutex_lock(&lag_mutex);
	ldev = mlx5_lag_dev_get(dev);
	res  = ldev && __mlx5_lag_is_roce(ldev);
	mutex_unlock(&lag_mutex);

	return res;
}