#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mlxsw_sp_fib_node {int dummy; } ;
struct TYPE_3__ {struct mlxsw_sp_fib_node* fib_node; } ;
struct mlxsw_sp_fib6_entry {TYPE_1__ common; } ;
struct mlxsw_sp {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 TYPE_2__ common ; 
 struct mlxsw_sp_fib6_entry* list_next_entry (struct mlxsw_sp_fib6_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_fib6_entry_destroy (struct mlxsw_sp*,struct mlxsw_sp_fib6_entry*) ; 
 int /*<<< orphan*/  mlxsw_sp_fib6_node_entry_unlink (struct mlxsw_sp*,struct mlxsw_sp_fib6_entry*) ; 
 int /*<<< orphan*/  mlxsw_sp_fib_node_put (struct mlxsw_sp*,struct mlxsw_sp_fib_node*) ; 

__attribute__((used)) static void mlxsw_sp_fib6_entry_replace(struct mlxsw_sp *mlxsw_sp,
					struct mlxsw_sp_fib6_entry *fib6_entry,
					bool replace)
{
	struct mlxsw_sp_fib_node *fib_node = fib6_entry->common.fib_node;
	struct mlxsw_sp_fib6_entry *replaced;

	if (!replace)
		return;

	replaced = list_next_entry(fib6_entry, common.list);

	mlxsw_sp_fib6_node_entry_unlink(mlxsw_sp, replaced);
	mlxsw_sp_fib6_entry_destroy(mlxsw_sp, replaced);
	mlxsw_sp_fib_node_put(mlxsw_sp, fib_node);
}