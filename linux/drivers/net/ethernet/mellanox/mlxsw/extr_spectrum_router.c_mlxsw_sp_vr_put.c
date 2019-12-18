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
struct mlxsw_sp_vr {int /*<<< orphan*/ * mr_table; TYPE_2__* fib6; TYPE_1__* fib4; int /*<<< orphan*/  rif_count; } ;
struct mlxsw_sp {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  node_list; } ;
struct TYPE_3__ {int /*<<< orphan*/  node_list; } ;

/* Variables and functions */
 size_t MLXSW_SP_L3_PROTO_IPV4 ; 
 size_t MLXSW_SP_L3_PROTO_IPV6 ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ mlxsw_sp_mr_table_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_vr_destroy (struct mlxsw_sp*,struct mlxsw_sp_vr*) ; 

__attribute__((used)) static void mlxsw_sp_vr_put(struct mlxsw_sp *mlxsw_sp, struct mlxsw_sp_vr *vr)
{
	if (!vr->rif_count && list_empty(&vr->fib4->node_list) &&
	    list_empty(&vr->fib6->node_list) &&
	    mlxsw_sp_mr_table_empty(vr->mr_table[MLXSW_SP_L3_PROTO_IPV4]) &&
	    mlxsw_sp_mr_table_empty(vr->mr_table[MLXSW_SP_L3_PROTO_IPV6]))
		mlxsw_sp_vr_destroy(mlxsw_sp, vr);
}