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
 int mlxsw_sp_fib4_node_list_insert (struct mlxsw_sp_fib4_entry*,int,int) ; 
 int /*<<< orphan*/  mlxsw_sp_fib4_node_list_remove (struct mlxsw_sp_fib4_entry*) ; 
 int mlxsw_sp_fib_node_entry_add (struct mlxsw_sp*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlxsw_sp_fib4_node_entry_link(struct mlxsw_sp *mlxsw_sp,
					 struct mlxsw_sp_fib4_entry *fib4_entry,
					 bool replace, bool append)
{
	int err;

	err = mlxsw_sp_fib4_node_list_insert(fib4_entry, replace, append);
	if (err)
		return err;

	err = mlxsw_sp_fib_node_entry_add(mlxsw_sp, &fib4_entry->common);
	if (err)
		goto err_fib_node_entry_add;

	return 0;

err_fib_node_entry_add:
	mlxsw_sp_fib4_node_list_remove(fib4_entry);
	return err;
}