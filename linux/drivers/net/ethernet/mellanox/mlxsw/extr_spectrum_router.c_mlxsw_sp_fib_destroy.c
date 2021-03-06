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
struct mlxsw_sp_fib {int /*<<< orphan*/  ht; int /*<<< orphan*/  node_list; int /*<<< orphan*/  lpm_tree; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_fib*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_lpm_tree_put (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_vr_lpm_tree_unbind (struct mlxsw_sp*,struct mlxsw_sp_fib*) ; 
 int /*<<< orphan*/  rhashtable_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlxsw_sp_fib_destroy(struct mlxsw_sp *mlxsw_sp,
				 struct mlxsw_sp_fib *fib)
{
	mlxsw_sp_vr_lpm_tree_unbind(mlxsw_sp, fib);
	mlxsw_sp_lpm_tree_put(mlxsw_sp, fib->lpm_tree);
	WARN_ON(!list_empty(&fib->node_list));
	rhashtable_destroy(&fib->ht);
	kfree(fib);
}