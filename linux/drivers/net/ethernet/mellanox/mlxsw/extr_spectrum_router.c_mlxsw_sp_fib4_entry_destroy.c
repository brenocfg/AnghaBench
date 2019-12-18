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
struct mlxsw_sp_fib4_entry {int /*<<< orphan*/  common; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mlxsw_sp_fib4_entry*) ; 
 int /*<<< orphan*/  mlxsw_sp_nexthop4_group_put (struct mlxsw_sp*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlxsw_sp_fib4_entry_destroy(struct mlxsw_sp *mlxsw_sp,
					struct mlxsw_sp_fib4_entry *fib4_entry)
{
	mlxsw_sp_nexthop4_group_put(mlxsw_sp, &fib4_entry->common);
	kfree(fib4_entry);
}