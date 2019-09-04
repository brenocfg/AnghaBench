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
struct mlxsw_sp_counter_pool {scalar_t__ pool_size; struct mlxsw_sp_counter_pool* usage; } ;
struct mlxsw_sp {struct mlxsw_sp_counter_pool* counter_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ find_first_bit (struct mlxsw_sp_counter_pool*,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_counter_pool*) ; 

void mlxsw_sp_counter_pool_fini(struct mlxsw_sp *mlxsw_sp)
{
	struct mlxsw_sp_counter_pool *pool = mlxsw_sp->counter_pool;

	WARN_ON(find_first_bit(pool->usage, pool->pool_size) !=
			       pool->pool_size);
	kfree(pool->usage);
	kfree(pool);
}