#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mlxsw_sp_nexthop_group {int /*<<< orphan*/  fib_list; } ;
struct TYPE_3__ {struct mlxsw_sp_nexthop_group* nh_group; int /*<<< orphan*/  nexthop_group_node; } ;
struct mlxsw_sp_fib6_entry {TYPE_1__ common; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int mlxsw_sp_fib_node_entry_add (struct mlxsw_sp*,TYPE_1__*) ; 
 int /*<<< orphan*/  mlxsw_sp_nexthop6_group_destroy (struct mlxsw_sp*,struct mlxsw_sp_nexthop_group*) ; 
 int mlxsw_sp_nexthop6_group_get (struct mlxsw_sp*,struct mlxsw_sp_fib6_entry*) ; 
 int /*<<< orphan*/  mlxsw_sp_nexthop6_group_put (struct mlxsw_sp*,TYPE_1__*) ; 

__attribute__((used)) static int
mlxsw_sp_nexthop6_group_update(struct mlxsw_sp *mlxsw_sp,
			       struct mlxsw_sp_fib6_entry *fib6_entry)
{
	struct mlxsw_sp_nexthop_group *old_nh_grp = fib6_entry->common.nh_group;
	int err;

	fib6_entry->common.nh_group = NULL;
	list_del(&fib6_entry->common.nexthop_group_node);

	err = mlxsw_sp_nexthop6_group_get(mlxsw_sp, fib6_entry);
	if (err)
		goto err_nexthop6_group_get;

	/* In case this entry is offloaded, then the adjacency index
	 * currently associated with it in the device's table is that
	 * of the old group. Start using the new one instead.
	 */
	err = mlxsw_sp_fib_node_entry_add(mlxsw_sp, &fib6_entry->common);
	if (err)
		goto err_fib_node_entry_add;

	if (list_empty(&old_nh_grp->fib_list))
		mlxsw_sp_nexthop6_group_destroy(mlxsw_sp, old_nh_grp);

	return 0;

err_fib_node_entry_add:
	mlxsw_sp_nexthop6_group_put(mlxsw_sp, &fib6_entry->common);
err_nexthop6_group_get:
	list_add_tail(&fib6_entry->common.nexthop_group_node,
		      &old_nh_grp->fib_list);
	fib6_entry->common.nh_group = old_nh_grp;
	return err;
}