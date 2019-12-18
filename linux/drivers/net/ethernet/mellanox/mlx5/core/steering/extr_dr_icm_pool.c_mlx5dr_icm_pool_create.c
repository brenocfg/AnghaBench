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
struct mlx5dr_icm_pool {int icm_type; int max_log_chunk_sz; int num_of_buckets; int /*<<< orphan*/  mr_mutex; int /*<<< orphan*/ * buckets; int /*<<< orphan*/  icm_mr_list; struct mlx5dr_domain* dmn; } ;
struct TYPE_2__ {int max_log_sw_icm_sz; int max_log_action_icm_sz; } ;
struct mlx5dr_domain {TYPE_1__ info; } ;
typedef  enum mlx5dr_icm_type { ____Placeholder_mlx5dr_icm_type } mlx5dr_icm_type ;
typedef  enum mlx5dr_icm_chunk_size { ____Placeholder_mlx5dr_icm_chunk_size } mlx5dr_icm_chunk_size ;

/* Variables and functions */
 int DR_ICM_TYPE_STE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dr_icm_bucket_init (struct mlx5dr_icm_pool*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvfree (struct mlx5dr_icm_pool*) ; 
 struct mlx5dr_icm_pool* kvzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

struct mlx5dr_icm_pool *mlx5dr_icm_pool_create(struct mlx5dr_domain *dmn,
					       enum mlx5dr_icm_type icm_type)
{
	enum mlx5dr_icm_chunk_size max_log_chunk_sz;
	struct mlx5dr_icm_pool *pool;
	int i;

	if (icm_type == DR_ICM_TYPE_STE)
		max_log_chunk_sz = dmn->info.max_log_sw_icm_sz;
	else
		max_log_chunk_sz = dmn->info.max_log_action_icm_sz;

	pool = kvzalloc(sizeof(*pool), GFP_KERNEL);
	if (!pool)
		return NULL;

	pool->buckets = kcalloc(max_log_chunk_sz + 1,
				sizeof(pool->buckets[0]),
				GFP_KERNEL);
	if (!pool->buckets)
		goto free_pool;

	pool->dmn = dmn;
	pool->icm_type = icm_type;
	pool->max_log_chunk_sz = max_log_chunk_sz;
	pool->num_of_buckets = max_log_chunk_sz + 1;
	INIT_LIST_HEAD(&pool->icm_mr_list);

	for (i = 0; i < pool->num_of_buckets; i++)
		dr_icm_bucket_init(pool, &pool->buckets[i], i);

	mutex_init(&pool->mr_mutex);

	return pool;

free_pool:
	kvfree(pool);
	return NULL;
}