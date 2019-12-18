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
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_SP_COUNTER_SUB_POOL_FLOW ; 
 int mlxsw_sp_counter_alloc (struct mlxsw_sp*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  mlxsw_sp_counter_free (struct mlxsw_sp*,int /*<<< orphan*/ ,unsigned int) ; 
 int mlxsw_sp_flow_counter_clear (struct mlxsw_sp*,unsigned int) ; 

int mlxsw_sp_flow_counter_alloc(struct mlxsw_sp *mlxsw_sp,
				unsigned int *p_counter_index)
{
	int err;

	err = mlxsw_sp_counter_alloc(mlxsw_sp, MLXSW_SP_COUNTER_SUB_POOL_FLOW,
				     p_counter_index);
	if (err)
		return err;
	err = mlxsw_sp_flow_counter_clear(mlxsw_sp, *p_counter_index);
	if (err)
		goto err_counter_clear;
	return 0;

err_counter_clear:
	mlxsw_sp_counter_free(mlxsw_sp, MLXSW_SP_COUNTER_SUB_POOL_FLOW,
			      *p_counter_index);
	return err;
}