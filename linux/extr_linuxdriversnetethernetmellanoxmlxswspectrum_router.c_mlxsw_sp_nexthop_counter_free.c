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
struct mlxsw_sp_nexthop {int counter_valid; int /*<<< orphan*/  counter_index; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp_flow_counter_free (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 

void mlxsw_sp_nexthop_counter_free(struct mlxsw_sp *mlxsw_sp,
				   struct mlxsw_sp_nexthop *nh)
{
	if (!nh->counter_valid)
		return;
	mlxsw_sp_flow_counter_free(mlxsw_sp, nh->counter_index);
	nh->counter_valid = false;
}