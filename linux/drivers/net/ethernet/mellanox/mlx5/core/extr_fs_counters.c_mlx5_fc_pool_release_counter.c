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
struct mlx5_fc_pool {scalar_t__ available_fcs; scalar_t__ threshold; int /*<<< orphan*/  pool_lock; int /*<<< orphan*/  unused; int /*<<< orphan*/  partially_used; int /*<<< orphan*/  used_fcs; struct mlx5_core_dev* dev; } ;
struct mlx5_fc_bulk {int bulk_len; int /*<<< orphan*/  pool_list; } ;
struct mlx5_fc {struct mlx5_fc_bulk* bulk; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*) ; 
 int mlx5_fc_bulk_get_free_fcs_amount (struct mlx5_fc_bulk*) ; 
 scalar_t__ mlx5_fc_bulk_release_fc (struct mlx5_fc_bulk*,struct mlx5_fc*) ; 
 int /*<<< orphan*/  mlx5_fc_pool_free_bulk (struct mlx5_fc_pool*,struct mlx5_fc_bulk*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mlx5_fc_pool_release_counter(struct mlx5_fc_pool *fc_pool, struct mlx5_fc *fc)
{
	struct mlx5_core_dev *dev = fc_pool->dev;
	struct mlx5_fc_bulk *bulk = fc->bulk;
	int bulk_free_fcs_amount;

	mutex_lock(&fc_pool->pool_lock);

	if (mlx5_fc_bulk_release_fc(bulk, fc)) {
		mlx5_core_warn(dev, "Attempted to release a counter which is not acquired\n");
		goto unlock;
	}

	fc_pool->available_fcs++;
	fc_pool->used_fcs--;

	bulk_free_fcs_amount = mlx5_fc_bulk_get_free_fcs_amount(bulk);
	if (bulk_free_fcs_amount == 1)
		list_move_tail(&bulk->pool_list, &fc_pool->partially_used);
	if (bulk_free_fcs_amount == bulk->bulk_len) {
		list_del(&bulk->pool_list);
		if (fc_pool->available_fcs > fc_pool->threshold)
			mlx5_fc_pool_free_bulk(fc_pool, bulk);
		else
			list_add(&bulk->pool_list, &fc_pool->unused);
	}

unlock:
	mutex_unlock(&fc_pool->pool_lock);
}