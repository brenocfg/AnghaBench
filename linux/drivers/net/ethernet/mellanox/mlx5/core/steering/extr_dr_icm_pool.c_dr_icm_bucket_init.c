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
struct mlx5dr_icm_pool {scalar_t__ icm_type; } ;
struct mlx5dr_icm_bucket {int /*<<< orphan*/  sync_list; int /*<<< orphan*/  hot_list; int /*<<< orphan*/  used_list; int /*<<< orphan*/  free_list; int /*<<< orphan*/  mutex; struct mlx5dr_icm_pool* pool; int /*<<< orphan*/  num_of_entries; int /*<<< orphan*/  entry_size; } ;
typedef  enum mlx5dr_icm_chunk_size { ____Placeholder_mlx5dr_icm_chunk_size } mlx5dr_icm_chunk_size ;

/* Variables and functions */
 scalar_t__ DR_ICM_TYPE_STE ; 
 int /*<<< orphan*/  DR_MODIFY_ACTION_SIZE ; 
 int /*<<< orphan*/  DR_STE_SIZE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5dr_icm_pool_chunk_size_to_entries (int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dr_icm_bucket_init(struct mlx5dr_icm_pool *pool,
			       struct mlx5dr_icm_bucket *bucket,
			       enum mlx5dr_icm_chunk_size chunk_size)
{
	if (pool->icm_type == DR_ICM_TYPE_STE)
		bucket->entry_size = DR_STE_SIZE;
	else
		bucket->entry_size = DR_MODIFY_ACTION_SIZE;

	bucket->num_of_entries = mlx5dr_icm_pool_chunk_size_to_entries(chunk_size);
	bucket->pool = pool;
	mutex_init(&bucket->mutex);
	INIT_LIST_HEAD(&bucket->free_list);
	INIT_LIST_HEAD(&bucket->used_list);
	INIT_LIST_HEAD(&bucket->hot_list);
	INIT_LIST_HEAD(&bucket->sync_list);
}