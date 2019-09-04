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
struct mlxsw_sp_fib6_entry {int /*<<< orphan*/  nrt6; int /*<<< orphan*/  rt6_list; } ;
struct mlxsw_sp {int dummy; } ;
struct fib6_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mlxsw_sp_rt6*) ; 
 int PTR_ERR (struct mlxsw_sp_rt6*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int mlxsw_sp_nexthop6_group_update (struct mlxsw_sp*,struct mlxsw_sp_fib6_entry*) ; 
 struct mlxsw_sp_rt6* mlxsw_sp_rt6_create (struct fib6_info*) ; 
 int /*<<< orphan*/  mlxsw_sp_rt6_destroy (struct mlxsw_sp_rt6*) ; 

__attribute__((used)) static int
mlxsw_sp_fib6_entry_nexthop_add(struct mlxsw_sp *mlxsw_sp,
				struct mlxsw_sp_fib6_entry *fib6_entry,
				struct fib6_info *rt)
{
	struct mlxsw_sp_rt6 *mlxsw_sp_rt6;
	int err;

	mlxsw_sp_rt6 = mlxsw_sp_rt6_create(rt);
	if (IS_ERR(mlxsw_sp_rt6))
		return PTR_ERR(mlxsw_sp_rt6);

	list_add_tail(&mlxsw_sp_rt6->list, &fib6_entry->rt6_list);
	fib6_entry->nrt6++;

	err = mlxsw_sp_nexthop6_group_update(mlxsw_sp, fib6_entry);
	if (err)
		goto err_nexthop6_group_update;

	return 0;

err_nexthop6_group_update:
	fib6_entry->nrt6--;
	list_del(&mlxsw_sp_rt6->list);
	mlxsw_sp_rt6_destroy(mlxsw_sp_rt6);
	return err;
}