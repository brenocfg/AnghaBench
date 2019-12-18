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
struct mlxsw_sp_fib_node {int dummy; } ;
struct mlxsw_sp_fib_entry {struct mlxsw_sp_fib_node* fib_node; } ;
struct mlxsw_sp_fib4_entry {int /*<<< orphan*/  tos; int /*<<< orphan*/  type; int /*<<< orphan*/  tb_id; int /*<<< orphan*/  prio; struct mlxsw_sp_fib_entry common; } ;
struct mlxsw_sp {int dummy; } ;
struct fib_entry_notifier_info {int /*<<< orphan*/  tos; int /*<<< orphan*/  type; int /*<<< orphan*/  tb_id; TYPE_1__* fi; } ;
struct TYPE_2__ {int /*<<< orphan*/  fib_priority; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct mlxsw_sp_fib4_entry* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_fib4_entry*) ; 
 struct mlxsw_sp_fib4_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mlxsw_sp_fib4_entry_type_set (struct mlxsw_sp*,struct fib_entry_notifier_info const*,struct mlxsw_sp_fib_entry*) ; 
 int mlxsw_sp_nexthop4_group_get (struct mlxsw_sp*,struct mlxsw_sp_fib_entry*,TYPE_1__*) ; 

__attribute__((used)) static struct mlxsw_sp_fib4_entry *
mlxsw_sp_fib4_entry_create(struct mlxsw_sp *mlxsw_sp,
			   struct mlxsw_sp_fib_node *fib_node,
			   const struct fib_entry_notifier_info *fen_info)
{
	struct mlxsw_sp_fib4_entry *fib4_entry;
	struct mlxsw_sp_fib_entry *fib_entry;
	int err;

	fib4_entry = kzalloc(sizeof(*fib4_entry), GFP_KERNEL);
	if (!fib4_entry)
		return ERR_PTR(-ENOMEM);
	fib_entry = &fib4_entry->common;

	err = mlxsw_sp_fib4_entry_type_set(mlxsw_sp, fen_info, fib_entry);
	if (err)
		goto err_fib4_entry_type_set;

	err = mlxsw_sp_nexthop4_group_get(mlxsw_sp, fib_entry, fen_info->fi);
	if (err)
		goto err_nexthop4_group_get;

	fib4_entry->prio = fen_info->fi->fib_priority;
	fib4_entry->tb_id = fen_info->tb_id;
	fib4_entry->type = fen_info->type;
	fib4_entry->tos = fen_info->tos;

	fib_entry->fib_node = fib_node;

	return fib4_entry;

err_nexthop4_group_get:
err_fib4_entry_type_set:
	kfree(fib4_entry);
	return ERR_PTR(err);
}