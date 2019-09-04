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
struct mlxsw_sp_counter_sub_pool {int entry_size; } ;
struct mlxsw_sp_counter_pool {unsigned int pool_size; int /*<<< orphan*/  usage; } ;
struct mlxsw_sp {struct mlxsw_sp_counter_pool* counter_pool; } ;
typedef  enum mlxsw_sp_counter_sub_pool_id { ____Placeholder_mlxsw_sp_counter_sub_pool_id } mlxsw_sp_counter_sub_pool_id ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  __clear_bit (unsigned int,int /*<<< orphan*/ ) ; 
 struct mlxsw_sp_counter_sub_pool* mlxsw_sp_counter_sub_pools ; 

void mlxsw_sp_counter_free(struct mlxsw_sp *mlxsw_sp,
			   enum mlxsw_sp_counter_sub_pool_id sub_pool_id,
			   unsigned int counter_index)
{
	struct mlxsw_sp_counter_pool *pool = mlxsw_sp->counter_pool;
	struct mlxsw_sp_counter_sub_pool *sub_pool;
	int i;

	if (WARN_ON(counter_index >= pool->pool_size))
		return;
	sub_pool = &mlxsw_sp_counter_sub_pools[sub_pool_id];
	for (i = 0; i < sub_pool->entry_size; i++)
		__clear_bit(counter_index + i, pool->usage);
}