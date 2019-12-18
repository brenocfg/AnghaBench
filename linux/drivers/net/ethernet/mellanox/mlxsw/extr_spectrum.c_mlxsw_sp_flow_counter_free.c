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
 int /*<<< orphan*/  mlxsw_sp_counter_free (struct mlxsw_sp*,int /*<<< orphan*/ ,unsigned int) ; 

void mlxsw_sp_flow_counter_free(struct mlxsw_sp *mlxsw_sp,
				unsigned int counter_index)
{
	 mlxsw_sp_counter_free(mlxsw_sp, MLXSW_SP_COUNTER_SUB_POOL_FLOW,
			       counter_index);
}