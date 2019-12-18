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
struct mlxsw_sp_prefix_usage {int dummy; } ;
struct mlxsw_sp_lpm_tree {scalar_t__* prefix_ref_count; int /*<<< orphan*/  prefix_usage; } ;
struct TYPE_2__ {size_t prefix_len; } ;
struct mlxsw_sp_fib_node {TYPE_1__ key; struct mlxsw_sp_fib* fib; } ;
struct mlxsw_sp_fib {int /*<<< orphan*/  proto; struct mlxsw_sp_lpm_tree* lpm_tree; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mlxsw_sp_lpm_tree*) ; 
 struct mlxsw_sp_lpm_tree* mlxsw_sp_lpm_tree_get (struct mlxsw_sp*,struct mlxsw_sp_prefix_usage*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_lpm_tree_put (struct mlxsw_sp*,struct mlxsw_sp_lpm_tree*) ; 
 int /*<<< orphan*/  mlxsw_sp_prefix_usage_clear (struct mlxsw_sp_prefix_usage*,size_t) ; 
 int /*<<< orphan*/  mlxsw_sp_prefix_usage_cpy (struct mlxsw_sp_prefix_usage*,int /*<<< orphan*/ *) ; 
 int mlxsw_sp_vrs_lpm_tree_replace (struct mlxsw_sp*,struct mlxsw_sp_fib*,struct mlxsw_sp_lpm_tree*) ; 

__attribute__((used)) static void mlxsw_sp_fib_lpm_tree_unlink(struct mlxsw_sp *mlxsw_sp,
					 struct mlxsw_sp_fib_node *fib_node)
{
	struct mlxsw_sp_lpm_tree *lpm_tree = fib_node->fib->lpm_tree;
	struct mlxsw_sp_prefix_usage req_prefix_usage;
	struct mlxsw_sp_fib *fib = fib_node->fib;
	int err;

	if (--lpm_tree->prefix_ref_count[fib_node->key.prefix_len] != 0)
		return;
	/* Try to construct a new LPM tree from the current prefix usage
	 * minus the unused one. If we fail, continue using the old one.
	 */
	mlxsw_sp_prefix_usage_cpy(&req_prefix_usage, &lpm_tree->prefix_usage);
	mlxsw_sp_prefix_usage_clear(&req_prefix_usage,
				    fib_node->key.prefix_len);
	lpm_tree = mlxsw_sp_lpm_tree_get(mlxsw_sp, &req_prefix_usage,
					 fib->proto);
	if (IS_ERR(lpm_tree))
		return;

	err = mlxsw_sp_vrs_lpm_tree_replace(mlxsw_sp, fib, lpm_tree);
	if (err)
		goto err_lpm_tree_replace;

	return;

err_lpm_tree_replace:
	mlxsw_sp_lpm_tree_put(mlxsw_sp, lpm_tree);
}