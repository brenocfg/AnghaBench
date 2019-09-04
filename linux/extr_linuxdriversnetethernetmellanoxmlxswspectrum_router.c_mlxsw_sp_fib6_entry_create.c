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
struct mlxsw_sp_rt6 {int /*<<< orphan*/  list; int /*<<< orphan*/  rt; } ;
struct mlxsw_sp_fib_node {int dummy; } ;
struct mlxsw_sp_fib_entry {struct mlxsw_sp_fib_node* fib_node; } ;
struct mlxsw_sp_fib6_entry {int nrt6; int /*<<< orphan*/  rt6_list; struct mlxsw_sp_fib_entry common; } ;
struct mlxsw_sp {int dummy; } ;
struct fib6_info {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct mlxsw_sp_fib6_entry* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct mlxsw_sp_rt6*) ; 
 int PTR_ERR (struct mlxsw_sp_rt6*) ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_fib6_entry*) ; 
 struct mlxsw_sp_fib6_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_fib6_entry_type_set (struct mlxsw_sp*,struct mlxsw_sp_fib_entry*,int /*<<< orphan*/ ) ; 
 int mlxsw_sp_nexthop6_group_get (struct mlxsw_sp*,struct mlxsw_sp_fib6_entry*) ; 
 struct mlxsw_sp_rt6* mlxsw_sp_rt6_create (struct fib6_info*) ; 
 int /*<<< orphan*/  mlxsw_sp_rt6_destroy (struct mlxsw_sp_rt6*) ; 

__attribute__((used)) static struct mlxsw_sp_fib6_entry *
mlxsw_sp_fib6_entry_create(struct mlxsw_sp *mlxsw_sp,
			   struct mlxsw_sp_fib_node *fib_node,
			   struct fib6_info *rt)
{
	struct mlxsw_sp_fib6_entry *fib6_entry;
	struct mlxsw_sp_fib_entry *fib_entry;
	struct mlxsw_sp_rt6 *mlxsw_sp_rt6;
	int err;

	fib6_entry = kzalloc(sizeof(*fib6_entry), GFP_KERNEL);
	if (!fib6_entry)
		return ERR_PTR(-ENOMEM);
	fib_entry = &fib6_entry->common;

	mlxsw_sp_rt6 = mlxsw_sp_rt6_create(rt);
	if (IS_ERR(mlxsw_sp_rt6)) {
		err = PTR_ERR(mlxsw_sp_rt6);
		goto err_rt6_create;
	}

	mlxsw_sp_fib6_entry_type_set(mlxsw_sp, fib_entry, mlxsw_sp_rt6->rt);

	INIT_LIST_HEAD(&fib6_entry->rt6_list);
	list_add_tail(&mlxsw_sp_rt6->list, &fib6_entry->rt6_list);
	fib6_entry->nrt6 = 1;
	err = mlxsw_sp_nexthop6_group_get(mlxsw_sp, fib6_entry);
	if (err)
		goto err_nexthop6_group_get;

	fib_entry->fib_node = fib_node;

	return fib6_entry;

err_nexthop6_group_get:
	list_del(&mlxsw_sp_rt6->list);
	mlxsw_sp_rt6_destroy(mlxsw_sp_rt6);
err_rt6_create:
	kfree(fib6_entry);
	return ERR_PTR(err);
}