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
struct mlx5_fc_pool {int /*<<< orphan*/  pool_lock; int /*<<< orphan*/  used_fcs; int /*<<< orphan*/  available_fcs; int /*<<< orphan*/  partially_used; int /*<<< orphan*/  unused; int /*<<< orphan*/  fully_used; } ;
struct mlx5_fc_bulk {int /*<<< orphan*/  pool_list; } ;
struct mlx5_fc {int /*<<< orphan*/  pool_list; } ;

/* Variables and functions */
 struct mlx5_fc_bulk* ERR_CAST (struct mlx5_fc_bulk*) ; 
 scalar_t__ IS_ERR (struct mlx5_fc_bulk*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct mlx5_fc_bulk* mlx5_fc_bulk_acquire_fc (struct mlx5_fc_bulk*) ; 
 struct mlx5_fc_bulk* mlx5_fc_pool_acquire_from_list (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct mlx5_fc_bulk* mlx5_fc_pool_alloc_new_bulk (struct mlx5_fc_pool*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mlx5_fc *
mlx5_fc_pool_acquire_counter(struct mlx5_fc_pool *fc_pool)
{
	struct mlx5_fc_bulk *new_bulk;
	struct mlx5_fc *fc;

	mutex_lock(&fc_pool->pool_lock);

	fc = mlx5_fc_pool_acquire_from_list(&fc_pool->partially_used,
					    &fc_pool->fully_used, false);
	if (IS_ERR(fc))
		fc = mlx5_fc_pool_acquire_from_list(&fc_pool->unused,
						    &fc_pool->partially_used,
						    true);
	if (IS_ERR(fc)) {
		new_bulk = mlx5_fc_pool_alloc_new_bulk(fc_pool);
		if (IS_ERR(new_bulk)) {
			fc = ERR_CAST(new_bulk);
			goto out;
		}
		fc = mlx5_fc_bulk_acquire_fc(new_bulk);
		list_add(&new_bulk->pool_list, &fc_pool->partially_used);
	}
	fc_pool->available_fcs--;
	fc_pool->used_fcs++;

out:
	mutex_unlock(&fc_pool->pool_lock);
	return fc;
}