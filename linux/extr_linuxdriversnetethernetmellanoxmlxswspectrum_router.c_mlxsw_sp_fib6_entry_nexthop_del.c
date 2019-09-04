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
struct mlxsw_sp_rt6 {int /*<<< orphan*/  list; } ;
struct mlxsw_sp_fib6_entry {int /*<<< orphan*/  nrt6; } ;
struct mlxsw_sp {int dummy; } ;
struct fib6_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct mlxsw_sp_rt6* mlxsw_sp_fib6_entry_rt_find (struct mlxsw_sp_fib6_entry*,struct fib6_info*) ; 
 int /*<<< orphan*/  mlxsw_sp_nexthop6_group_update (struct mlxsw_sp*,struct mlxsw_sp_fib6_entry*) ; 
 int /*<<< orphan*/  mlxsw_sp_rt6_destroy (struct mlxsw_sp_rt6*) ; 

__attribute__((used)) static void
mlxsw_sp_fib6_entry_nexthop_del(struct mlxsw_sp *mlxsw_sp,
				struct mlxsw_sp_fib6_entry *fib6_entry,
				struct fib6_info *rt)
{
	struct mlxsw_sp_rt6 *mlxsw_sp_rt6;

	mlxsw_sp_rt6 = mlxsw_sp_fib6_entry_rt_find(fib6_entry, rt);
	if (WARN_ON(!mlxsw_sp_rt6))
		return;

	fib6_entry->nrt6--;
	list_del(&mlxsw_sp_rt6->list);
	mlxsw_sp_nexthop6_group_update(mlxsw_sp, fib6_entry);
	mlxsw_sp_rt6_destroy(mlxsw_sp_rt6);
}