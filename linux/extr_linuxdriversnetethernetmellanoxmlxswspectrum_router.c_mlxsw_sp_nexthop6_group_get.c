#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mlxsw_sp_nexthop_group {int /*<<< orphan*/  fib_list; } ;
struct TYPE_2__ {struct mlxsw_sp_nexthop_group* nh_group; int /*<<< orphan*/  nexthop_group_node; } ;
struct mlxsw_sp_fib6_entry {TYPE_1__ common; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mlxsw_sp_nexthop_group*) ; 
 int PTR_ERR (struct mlxsw_sp_nexthop_group*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct mlxsw_sp_nexthop_group* mlxsw_sp_nexthop6_group_create (struct mlxsw_sp*,struct mlxsw_sp_fib6_entry*) ; 
 struct mlxsw_sp_nexthop_group* mlxsw_sp_nexthop6_group_lookup (struct mlxsw_sp*,struct mlxsw_sp_fib6_entry*) ; 

__attribute__((used)) static int mlxsw_sp_nexthop6_group_get(struct mlxsw_sp *mlxsw_sp,
				       struct mlxsw_sp_fib6_entry *fib6_entry)
{
	struct mlxsw_sp_nexthop_group *nh_grp;

	nh_grp = mlxsw_sp_nexthop6_group_lookup(mlxsw_sp, fib6_entry);
	if (!nh_grp) {
		nh_grp = mlxsw_sp_nexthop6_group_create(mlxsw_sp, fib6_entry);
		if (IS_ERR(nh_grp))
			return PTR_ERR(nh_grp);
	}

	list_add_tail(&fib6_entry->common.nexthop_group_node,
		      &nh_grp->fib_list);
	fib6_entry->common.nh_group = nh_grp;

	return 0;
}