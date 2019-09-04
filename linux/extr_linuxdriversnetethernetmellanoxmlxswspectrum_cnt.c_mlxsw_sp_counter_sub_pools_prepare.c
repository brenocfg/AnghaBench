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
struct mlxsw_sp_counter_sub_pool {void* entry_size; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  COUNTER_SIZE_PACKETS_BYTES ; 
 int /*<<< orphan*/  COUNTER_SIZE_ROUTER_BASIC ; 
 int EIO ; 
 void* MLXSW_CORE_RES_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLXSW_CORE_RES_VALID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t MLXSW_SP_COUNTER_SUB_POOL_FLOW ; 
 size_t MLXSW_SP_COUNTER_SUB_POOL_RIF ; 
 struct mlxsw_sp_counter_sub_pool* mlxsw_sp_counter_sub_pools ; 

__attribute__((used)) static int mlxsw_sp_counter_sub_pools_prepare(struct mlxsw_sp *mlxsw_sp)
{
	struct mlxsw_sp_counter_sub_pool *sub_pool;

	/* Prepare generic flow pool*/
	sub_pool = &mlxsw_sp_counter_sub_pools[MLXSW_SP_COUNTER_SUB_POOL_FLOW];
	if (!MLXSW_CORE_RES_VALID(mlxsw_sp->core, COUNTER_SIZE_PACKETS_BYTES))
		return -EIO;
	sub_pool->entry_size = MLXSW_CORE_RES_GET(mlxsw_sp->core,
						  COUNTER_SIZE_PACKETS_BYTES);
	/* Prepare erif pool*/
	sub_pool = &mlxsw_sp_counter_sub_pools[MLXSW_SP_COUNTER_SUB_POOL_RIF];
	if (!MLXSW_CORE_RES_VALID(mlxsw_sp->core, COUNTER_SIZE_ROUTER_BASIC))
		return -EIO;
	sub_pool->entry_size = MLXSW_CORE_RES_GET(mlxsw_sp->core,
						  COUNTER_SIZE_ROUTER_BASIC);
	return 0;
}