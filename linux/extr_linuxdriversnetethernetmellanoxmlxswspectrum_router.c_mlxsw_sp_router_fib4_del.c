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
struct TYPE_4__ {struct mlxsw_sp_fib_node* fib_node; } ;
struct mlxsw_sp_fib4_entry {TYPE_2__ common; } ;
struct mlxsw_sp {TYPE_1__* router; } ;
struct fib_entry_notifier_info {int dummy; } ;
struct TYPE_3__ {scalar_t__ aborted; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  mlxsw_sp_fib4_entry_destroy (struct mlxsw_sp*,struct mlxsw_sp_fib4_entry*) ; 
 struct mlxsw_sp_fib4_entry* mlxsw_sp_fib4_entry_lookup (struct mlxsw_sp*,struct fib_entry_notifier_info*) ; 
 int /*<<< orphan*/  mlxsw_sp_fib4_node_entry_unlink (struct mlxsw_sp*,struct mlxsw_sp_fib4_entry*) ; 
 int /*<<< orphan*/  mlxsw_sp_fib_node_put (struct mlxsw_sp*,struct mlxsw_sp_fib_node*) ; 

__attribute__((used)) static void mlxsw_sp_router_fib4_del(struct mlxsw_sp *mlxsw_sp,
				     struct fib_entry_notifier_info *fen_info)
{
	struct mlxsw_sp_fib4_entry *fib4_entry;
	struct mlxsw_sp_fib_node *fib_node;

	if (mlxsw_sp->router->aborted)
		return;

	fib4_entry = mlxsw_sp_fib4_entry_lookup(mlxsw_sp, fen_info);
	if (WARN_ON(!fib4_entry))
		return;
	fib_node = fib4_entry->common.fib_node;

	mlxsw_sp_fib4_node_entry_unlink(mlxsw_sp, fib4_entry);
	mlxsw_sp_fib4_entry_destroy(mlxsw_sp, fib4_entry);
	mlxsw_sp_fib_node_put(mlxsw_sp, fib_node);
}