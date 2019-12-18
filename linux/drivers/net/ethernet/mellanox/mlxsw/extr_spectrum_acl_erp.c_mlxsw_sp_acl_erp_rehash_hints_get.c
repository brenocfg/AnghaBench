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
typedef  void objagg_hints ;
struct mlxsw_sp_acl_erp_table {int /*<<< orphan*/  objagg_lock; int /*<<< orphan*/  objagg; } ;
struct mlxsw_sp_acl_atcam_region {TYPE_2__* region; struct mlxsw_sp_acl_erp_table* erp_table; } ;
struct mlxsw_sp {TYPE_1__* bus_info; } ;
struct TYPE_4__ {struct mlxsw_sp* mlxsw_sp; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EAGAIN ; 
 void* ERR_CAST (void*) ; 
 void* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  OBJAGG_OPT_ALGO_SIMPLE_GREEDY ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ ,char*) ; 
 int mlxsw_sp_acl_erp_hints_check (struct mlxsw_sp*,struct mlxsw_sp_acl_atcam_region*,void*,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 void* objagg_hints_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  objagg_hints_put (void*) ; 

void *
mlxsw_sp_acl_erp_rehash_hints_get(struct mlxsw_sp_acl_atcam_region *aregion)
{
	struct mlxsw_sp_acl_erp_table *erp_table = aregion->erp_table;
	struct mlxsw_sp *mlxsw_sp = aregion->region->mlxsw_sp;
	struct objagg_hints *hints;
	bool rehash_needed;
	int err;

	mutex_lock(&erp_table->objagg_lock);
	hints = objagg_hints_get(erp_table->objagg,
				 OBJAGG_OPT_ALGO_SIMPLE_GREEDY);
	mutex_unlock(&erp_table->objagg_lock);
	if (IS_ERR(hints)) {
		dev_err_ratelimited(mlxsw_sp->bus_info->dev, "Failed to create ERP hints\n");
		return ERR_CAST(hints);
	}
	err = mlxsw_sp_acl_erp_hints_check(mlxsw_sp, aregion, hints,
					   &rehash_needed);
	if (err)
		goto errout;

	if (!rehash_needed) {
		err = -EAGAIN;
		goto errout;
	}
	return hints;

errout:
	objagg_hints_put(hints);
	return ERR_PTR(err);
}