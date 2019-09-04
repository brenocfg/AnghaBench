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
struct mlxsw_sp_vr {int dummy; } ;
struct mlxsw_sp_fib_node {int /*<<< orphan*/  entry_list; TYPE_1__* fib; } ;
struct mlxsw_sp {int dummy; } ;
struct TYPE_2__ {struct mlxsw_sp_vr* vr; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_fib_node_destroy (struct mlxsw_sp_fib_node*) ; 
 int /*<<< orphan*/  mlxsw_sp_fib_node_fini (struct mlxsw_sp*,struct mlxsw_sp_fib_node*) ; 
 int /*<<< orphan*/  mlxsw_sp_vr_put (struct mlxsw_sp*,struct mlxsw_sp_vr*) ; 

__attribute__((used)) static void mlxsw_sp_fib_node_put(struct mlxsw_sp *mlxsw_sp,
				  struct mlxsw_sp_fib_node *fib_node)
{
	struct mlxsw_sp_vr *vr = fib_node->fib->vr;

	if (!list_empty(&fib_node->entry_list))
		return;
	mlxsw_sp_fib_node_fini(mlxsw_sp, fib_node);
	mlxsw_sp_fib_node_destroy(fib_node);
	mlxsw_sp_vr_put(mlxsw_sp, vr);
}