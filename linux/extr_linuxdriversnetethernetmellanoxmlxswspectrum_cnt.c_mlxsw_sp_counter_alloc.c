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
struct mlxsw_sp_counter_sub_pool {unsigned int base_index; unsigned int size; unsigned int entry_size; } ;
struct mlxsw_sp_counter_pool {int /*<<< orphan*/  usage; } ;
struct mlxsw_sp {struct mlxsw_sp_counter_pool* counter_pool; } ;
typedef  enum mlxsw_sp_counter_sub_pool_id { ____Placeholder_mlxsw_sp_counter_sub_pool_id } mlxsw_sp_counter_sub_pool_id ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  __set_bit (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int find_next_zero_bit (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct mlxsw_sp_counter_sub_pool* mlxsw_sp_counter_sub_pools ; 

int mlxsw_sp_counter_alloc(struct mlxsw_sp *mlxsw_sp,
			   enum mlxsw_sp_counter_sub_pool_id sub_pool_id,
			   unsigned int *p_counter_index)
{
	struct mlxsw_sp_counter_pool *pool = mlxsw_sp->counter_pool;
	struct mlxsw_sp_counter_sub_pool *sub_pool;
	unsigned int entry_index;
	unsigned int stop_index;
	int i;

	sub_pool = &mlxsw_sp_counter_sub_pools[sub_pool_id];
	stop_index = sub_pool->base_index + sub_pool->size;
	entry_index = sub_pool->base_index;

	entry_index = find_next_zero_bit(pool->usage, stop_index, entry_index);
	if (entry_index == stop_index)
		return -ENOBUFS;
	/* The sub-pools can contain non-integer number of entries
	 * so we must check for overflow
	 */
	if (entry_index + sub_pool->entry_size > stop_index)
		return -ENOBUFS;
	for (i = 0; i < sub_pool->entry_size; i++)
		__set_bit(entry_index + i, pool->usage);

	*p_counter_index = entry_index;
	return 0;
}