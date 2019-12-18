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
struct mlxsw_sp_mr_ops {int (* init ) (struct mlxsw_sp*,int /*<<< orphan*/ ) ;scalar_t__ priv_size; } ;
struct mlxsw_sp_mr {int /*<<< orphan*/  stats_update_dw; int /*<<< orphan*/  priv; int /*<<< orphan*/  table_list; struct mlxsw_sp_mr_ops const* mr_ops; } ;
struct mlxsw_sp {struct mlxsw_sp_mr* mr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MLXSW_SP_MR_ROUTES_COUNTER_UPDATE_INTERVAL ; 
 int /*<<< orphan*/  kfree (struct mlxsw_sp_mr*) ; 
 struct mlxsw_sp_mr* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_core_schedule_dw (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  mlxsw_sp_mr_stats_update ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int stub1 (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 

int mlxsw_sp_mr_init(struct mlxsw_sp *mlxsw_sp,
		     const struct mlxsw_sp_mr_ops *mr_ops)
{
	struct mlxsw_sp_mr *mr;
	unsigned long interval;
	int err;

	mr = kzalloc(sizeof(*mr) + mr_ops->priv_size, GFP_KERNEL);
	if (!mr)
		return -ENOMEM;
	mr->mr_ops = mr_ops;
	mlxsw_sp->mr = mr;
	INIT_LIST_HEAD(&mr->table_list);

	err = mr_ops->init(mlxsw_sp, mr->priv);
	if (err)
		goto err;

	/* Create the delayed work for counter updates */
	INIT_DELAYED_WORK(&mr->stats_update_dw, mlxsw_sp_mr_stats_update);
	interval = msecs_to_jiffies(MLXSW_SP_MR_ROUTES_COUNTER_UPDATE_INTERVAL);
	mlxsw_core_schedule_dw(&mr->stats_update_dw, interval);
	return 0;
err:
	kfree(mr);
	return err;
}