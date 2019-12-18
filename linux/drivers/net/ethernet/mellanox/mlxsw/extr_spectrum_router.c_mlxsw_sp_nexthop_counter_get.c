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
typedef  int /*<<< orphan*/  u64 ;
struct mlxsw_sp_nexthop {int /*<<< orphan*/  counter_index; int /*<<< orphan*/  counter_valid; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int mlxsw_sp_flow_counter_get (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int mlxsw_sp_nexthop_counter_get(struct mlxsw_sp *mlxsw_sp,
				 struct mlxsw_sp_nexthop *nh, u64 *p_counter)
{
	if (!nh->counter_valid)
		return -EINVAL;

	return mlxsw_sp_flow_counter_get(mlxsw_sp, nh->counter_index,
					 p_counter, NULL);
}