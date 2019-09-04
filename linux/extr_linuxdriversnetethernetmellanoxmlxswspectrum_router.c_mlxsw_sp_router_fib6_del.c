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
struct mlxsw_sp_fib6_entry {TYPE_2__ common; int /*<<< orphan*/  rt6_list; } ;
struct mlxsw_sp {TYPE_1__* router; } ;
struct fib6_info {int dummy; } ;
struct TYPE_3__ {scalar_t__ aborted; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  list_is_singular (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_fib6_entry_destroy (struct mlxsw_sp*,struct mlxsw_sp_fib6_entry*) ; 
 struct mlxsw_sp_fib6_entry* mlxsw_sp_fib6_entry_lookup (struct mlxsw_sp*,struct fib6_info*) ; 
 int /*<<< orphan*/  mlxsw_sp_fib6_entry_nexthop_del (struct mlxsw_sp*,struct mlxsw_sp_fib6_entry*,struct fib6_info*) ; 
 int /*<<< orphan*/  mlxsw_sp_fib6_node_entry_unlink (struct mlxsw_sp*,struct mlxsw_sp_fib6_entry*) ; 
 scalar_t__ mlxsw_sp_fib6_rt_should_ignore (struct fib6_info*) ; 
 int /*<<< orphan*/  mlxsw_sp_fib_node_put (struct mlxsw_sp*,struct mlxsw_sp_fib_node*) ; 

__attribute__((used)) static void mlxsw_sp_router_fib6_del(struct mlxsw_sp *mlxsw_sp,
				     struct fib6_info *rt)
{
	struct mlxsw_sp_fib6_entry *fib6_entry;
	struct mlxsw_sp_fib_node *fib_node;

	if (mlxsw_sp->router->aborted)
		return;

	if (mlxsw_sp_fib6_rt_should_ignore(rt))
		return;

	fib6_entry = mlxsw_sp_fib6_entry_lookup(mlxsw_sp, rt);
	if (WARN_ON(!fib6_entry))
		return;

	/* If route is part of a multipath entry, but not the last one
	 * removed, then only reduce its nexthop group.
	 */
	if (!list_is_singular(&fib6_entry->rt6_list)) {
		mlxsw_sp_fib6_entry_nexthop_del(mlxsw_sp, fib6_entry, rt);
		return;
	}

	fib_node = fib6_entry->common.fib_node;

	mlxsw_sp_fib6_node_entry_unlink(mlxsw_sp, fib6_entry);
	mlxsw_sp_fib6_entry_destroy(mlxsw_sp, fib6_entry);
	mlxsw_sp_fib_node_put(mlxsw_sp, fib_node);
}