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
typedef  int u64 ;
struct mlx5dr_icm_pool {int num_of_buckets; int /*<<< orphan*/  icm_type; TYPE_1__* buckets; } ;
struct TYPE_2__ {int hot_list_count; } ;

/* Variables and functions */
 int mlx5dr_icm_pool_chunk_size_to_byte (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 dr_icm_hot_mem_size(struct mlx5dr_icm_pool *pool)
{
	u64 hot_size = 0;
	int chunk_order;

	for (chunk_order = 0; chunk_order < pool->num_of_buckets; chunk_order++)
		hot_size += pool->buckets[chunk_order].hot_list_count *
			    mlx5dr_icm_pool_chunk_size_to_byte(chunk_order, pool->icm_type);

	return hot_size;
}