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
struct mlxsw_sp_vr {int dummy; } ;
struct mlxsw_sp_lpm_tree {int /*<<< orphan*/  id; } ;
struct mlxsw_sp_fib {int proto; struct mlxsw_sp_lpm_tree* lpm_tree; struct mlxsw_sp_vr* vr; int /*<<< orphan*/  node_list; int /*<<< orphan*/  ht; } ;
struct mlxsw_sp {TYPE_2__* router; } ;
typedef  enum mlxsw_sp_l3proto { ____Placeholder_mlxsw_sp_l3proto } mlxsw_sp_l3proto ;
struct TYPE_3__ {struct mlxsw_sp_lpm_tree** proto_trees; } ;
struct TYPE_4__ {TYPE_1__ lpm; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct mlxsw_sp_fib* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_fib*) ; 
 struct mlxsw_sp_fib* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_fib_ht_params ; 
 int /*<<< orphan*/  mlxsw_sp_lpm_tree_hold (struct mlxsw_sp_lpm_tree*) ; 
 int /*<<< orphan*/  mlxsw_sp_lpm_tree_put (struct mlxsw_sp*,struct mlxsw_sp_lpm_tree*) ; 
 int mlxsw_sp_vr_lpm_tree_bind (struct mlxsw_sp*,struct mlxsw_sp_fib*,int /*<<< orphan*/ ) ; 
 int rhashtable_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mlxsw_sp_fib *mlxsw_sp_fib_create(struct mlxsw_sp *mlxsw_sp,
						struct mlxsw_sp_vr *vr,
						enum mlxsw_sp_l3proto proto)
{
	struct mlxsw_sp_lpm_tree *lpm_tree;
	struct mlxsw_sp_fib *fib;
	int err;

	lpm_tree = mlxsw_sp->router->lpm.proto_trees[proto];
	fib = kzalloc(sizeof(*fib), GFP_KERNEL);
	if (!fib)
		return ERR_PTR(-ENOMEM);
	err = rhashtable_init(&fib->ht, &mlxsw_sp_fib_ht_params);
	if (err)
		goto err_rhashtable_init;
	INIT_LIST_HEAD(&fib->node_list);
	fib->proto = proto;
	fib->vr = vr;
	fib->lpm_tree = lpm_tree;
	mlxsw_sp_lpm_tree_hold(lpm_tree);
	err = mlxsw_sp_vr_lpm_tree_bind(mlxsw_sp, fib, lpm_tree->id);
	if (err)
		goto err_lpm_tree_bind;
	return fib;

err_lpm_tree_bind:
	mlxsw_sp_lpm_tree_put(mlxsw_sp, lpm_tree);
err_rhashtable_init:
	kfree(fib);
	return ERR_PTR(err);
}