#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mlxsw_sp {int /*<<< orphan*/  core; } ;
struct TYPE_3__ {scalar_t__ bank_count; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  COUNTER_POOL_SIZE ; 
 int EINVAL ; 
 unsigned int MLXSW_CORE_RES_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int MLXSW_SP_COUNTER_POOL_BANK_SIZE ; 
 TYPE_1__* mlxsw_sp_counter_sub_pools ; 

__attribute__((used)) static int mlxsw_sp_counter_pool_validate(struct mlxsw_sp *mlxsw_sp)
{
	unsigned int total_bank_config = 0;
	unsigned int pool_size;
	int i;

	pool_size = MLXSW_CORE_RES_GET(mlxsw_sp->core, COUNTER_POOL_SIZE);
	/* Check config is valid, no bank over subscription */
	for (i = 0; i < ARRAY_SIZE(mlxsw_sp_counter_sub_pools); i++)
		total_bank_config += mlxsw_sp_counter_sub_pools[i].bank_count;
	if (total_bank_config > pool_size / MLXSW_SP_COUNTER_POOL_BANK_SIZE + 1)
		return -EINVAL;
	return 0;
}