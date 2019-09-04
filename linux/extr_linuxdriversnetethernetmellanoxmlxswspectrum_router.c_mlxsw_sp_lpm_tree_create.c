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
struct mlxsw_sp_prefix_usage {int dummy; } ;
struct mlxsw_sp_lpm_tree {int proto; int ref_count; int /*<<< orphan*/  prefix_ref_count; int /*<<< orphan*/  prefix_usage; } ;
struct mlxsw_sp {int dummy; } ;
typedef  enum mlxsw_sp_l3proto { ____Placeholder_mlxsw_sp_l3proto } mlxsw_sp_l3proto ;

/* Variables and functions */
 int EBUSY ; 
 struct mlxsw_sp_lpm_tree* ERR_PTR (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct mlxsw_sp_prefix_usage*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int mlxsw_sp_lpm_tree_alloc (struct mlxsw_sp*,struct mlxsw_sp_lpm_tree*) ; 
 struct mlxsw_sp_lpm_tree* mlxsw_sp_lpm_tree_find_unused (struct mlxsw_sp*) ; 
 int /*<<< orphan*/  mlxsw_sp_lpm_tree_free (struct mlxsw_sp*,struct mlxsw_sp_lpm_tree*) ; 
 int mlxsw_sp_lpm_tree_left_struct_set (struct mlxsw_sp*,struct mlxsw_sp_prefix_usage*,struct mlxsw_sp_lpm_tree*) ; 

__attribute__((used)) static struct mlxsw_sp_lpm_tree *
mlxsw_sp_lpm_tree_create(struct mlxsw_sp *mlxsw_sp,
			 struct mlxsw_sp_prefix_usage *prefix_usage,
			 enum mlxsw_sp_l3proto proto)
{
	struct mlxsw_sp_lpm_tree *lpm_tree;
	int err;

	lpm_tree = mlxsw_sp_lpm_tree_find_unused(mlxsw_sp);
	if (!lpm_tree)
		return ERR_PTR(-EBUSY);
	lpm_tree->proto = proto;
	err = mlxsw_sp_lpm_tree_alloc(mlxsw_sp, lpm_tree);
	if (err)
		return ERR_PTR(err);

	err = mlxsw_sp_lpm_tree_left_struct_set(mlxsw_sp, prefix_usage,
						lpm_tree);
	if (err)
		goto err_left_struct_set;
	memcpy(&lpm_tree->prefix_usage, prefix_usage,
	       sizeof(lpm_tree->prefix_usage));
	memset(&lpm_tree->prefix_ref_count, 0,
	       sizeof(lpm_tree->prefix_ref_count));
	lpm_tree->ref_count = 1;
	return lpm_tree;

err_left_struct_set:
	mlxsw_sp_lpm_tree_free(mlxsw_sp, lpm_tree);
	return ERR_PTR(err);
}