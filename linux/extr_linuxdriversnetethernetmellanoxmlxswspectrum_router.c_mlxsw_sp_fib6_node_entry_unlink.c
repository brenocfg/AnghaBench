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
struct mlxsw_sp_fib6_entry {int /*<<< orphan*/  common; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp_fib6_node_list_remove (struct mlxsw_sp_fib6_entry*) ; 
 int /*<<< orphan*/  mlxsw_sp_fib_node_entry_del (struct mlxsw_sp*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mlxsw_sp_fib6_node_entry_unlink(struct mlxsw_sp *mlxsw_sp,
				struct mlxsw_sp_fib6_entry *fib6_entry)
{
	mlxsw_sp_fib_node_entry_del(mlxsw_sp, &fib6_entry->common);
	mlxsw_sp_fib6_node_list_remove(fib6_entry);
}