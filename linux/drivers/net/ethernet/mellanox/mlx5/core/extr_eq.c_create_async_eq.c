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
struct mlx5_eq_table {int /*<<< orphan*/  lock; } ;
struct mlx5_eq_param {scalar_t__ irq_index; } ;
struct mlx5_eq {int dummy; } ;
struct TYPE_2__ {struct mlx5_eq_table* eq_table; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int create_map_eq (struct mlx5_core_dev*,struct mlx5_eq*,struct mlx5_eq_param*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int create_async_eq(struct mlx5_core_dev *dev,
			   struct mlx5_eq *eq, struct mlx5_eq_param *param)
{
	struct mlx5_eq_table *eq_table = dev->priv.eq_table;
	int err;

	mutex_lock(&eq_table->lock);
	/* Async EQs must share irq index 0 */
	if (param->irq_index != 0) {
		err = -EINVAL;
		goto unlock;
	}

	err = create_map_eq(dev, eq, param);
unlock:
	mutex_unlock(&eq_table->lock);
	return err;
}