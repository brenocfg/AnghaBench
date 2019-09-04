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
struct mlxsw_sp_mr {int /*<<< orphan*/  priv; TYPE_1__* mr_ops; int /*<<< orphan*/  stats_update_dw; } ;
struct mlxsw_sp {struct mlxsw_sp_mr* mr; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* fini ) (struct mlxsw_sp*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_mr*) ; 
 int /*<<< orphan*/  stub1 (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 

void mlxsw_sp_mr_fini(struct mlxsw_sp *mlxsw_sp)
{
	struct mlxsw_sp_mr *mr = mlxsw_sp->mr;

	cancel_delayed_work_sync(&mr->stats_update_dw);
	mr->mr_ops->fini(mlxsw_sp, mr->priv);
	kfree(mr);
}