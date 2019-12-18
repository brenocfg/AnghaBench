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
struct mlxsw_sp_fib_node {struct mlxsw_sp_fib* fib; } ;
struct mlxsw_sp_fib {int dummy; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int mlxsw_sp_fib_lpm_tree_link (struct mlxsw_sp*,struct mlxsw_sp_fib_node*) ; 
 int mlxsw_sp_fib_node_insert (struct mlxsw_sp_fib*,struct mlxsw_sp_fib_node*) ; 
 int /*<<< orphan*/  mlxsw_sp_fib_node_remove (struct mlxsw_sp_fib*,struct mlxsw_sp_fib_node*) ; 

__attribute__((used)) static int mlxsw_sp_fib_node_init(struct mlxsw_sp *mlxsw_sp,
				  struct mlxsw_sp_fib_node *fib_node,
				  struct mlxsw_sp_fib *fib)
{
	int err;

	err = mlxsw_sp_fib_node_insert(fib, fib_node);
	if (err)
		return err;
	fib_node->fib = fib;

	err = mlxsw_sp_fib_lpm_tree_link(mlxsw_sp, fib_node);
	if (err)
		goto err_fib_lpm_tree_link;

	return 0;

err_fib_lpm_tree_link:
	fib_node->fib = NULL;
	mlxsw_sp_fib_node_remove(fib, fib_node);
	return err;
}