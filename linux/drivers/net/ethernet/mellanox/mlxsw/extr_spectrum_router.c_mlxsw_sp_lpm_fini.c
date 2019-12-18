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
struct mlxsw_sp_lpm_tree {int dummy; } ;
struct mlxsw_sp {TYPE_2__* router; } ;
struct TYPE_3__ {int /*<<< orphan*/  trees; struct mlxsw_sp_lpm_tree** proto_trees; } ;
struct TYPE_4__ {TYPE_1__ lpm; } ;

/* Variables and functions */
 size_t MLXSW_SP_L3_PROTO_IPV4 ; 
 size_t MLXSW_SP_L3_PROTO_IPV6 ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_lpm_tree_put (struct mlxsw_sp*,struct mlxsw_sp_lpm_tree*) ; 

__attribute__((used)) static void mlxsw_sp_lpm_fini(struct mlxsw_sp *mlxsw_sp)
{
	struct mlxsw_sp_lpm_tree *lpm_tree;

	lpm_tree = mlxsw_sp->router->lpm.proto_trees[MLXSW_SP_L3_PROTO_IPV6];
	mlxsw_sp_lpm_tree_put(mlxsw_sp, lpm_tree);

	lpm_tree = mlxsw_sp->router->lpm.proto_trees[MLXSW_SP_L3_PROTO_IPV4];
	mlxsw_sp_lpm_tree_put(mlxsw_sp, lpm_tree);

	kfree(mlxsw_sp->router->lpm.trees);
}