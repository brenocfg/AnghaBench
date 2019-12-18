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
struct objagg_stats {scalar_t__ root_count; } ;
struct objagg_hints {int dummy; } ;
struct mlxsw_sp_acl_erp_table {int /*<<< orphan*/  objagg_lock; int /*<<< orphan*/  objagg; } ;
struct mlxsw_sp_acl_atcam_region {struct mlxsw_sp_acl_erp_table* erp_table; } ;
struct mlxsw_sp {TYPE_1__* bus_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct objagg_stats const*) ; 
 int PTR_ERR (struct objagg_stats const*) ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct objagg_stats* objagg_hints_stats_get (struct objagg_hints*) ; 
 struct objagg_stats* objagg_stats_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  objagg_stats_put (struct objagg_stats const*) ; 

__attribute__((used)) static int
mlxsw_sp_acl_erp_hints_check(struct mlxsw_sp *mlxsw_sp,
			     struct mlxsw_sp_acl_atcam_region *aregion,
			     struct objagg_hints *hints, bool *p_rehash_needed)
{
	struct mlxsw_sp_acl_erp_table *erp_table = aregion->erp_table;
	const struct objagg_stats *ostats;
	const struct objagg_stats *hstats;
	int err;

	*p_rehash_needed = false;

	mutex_lock(&erp_table->objagg_lock);
	ostats = objagg_stats_get(erp_table->objagg);
	mutex_unlock(&erp_table->objagg_lock);
	if (IS_ERR(ostats)) {
		dev_err_ratelimited(mlxsw_sp->bus_info->dev, "Failed to get ERP stats\n");
		return PTR_ERR(ostats);
	}

	hstats = objagg_hints_stats_get(hints);
	if (IS_ERR(hstats)) {
		dev_err_ratelimited(mlxsw_sp->bus_info->dev, "Failed to get ERP hints stats\n");
		err = PTR_ERR(hstats);
		goto err_hints_stats_get;
	}

	/* Very basic criterion for now. */
	if (hstats->root_count < ostats->root_count)
		*p_rehash_needed = true;

	err = 0;

	objagg_stats_put(hstats);
err_hints_stats_get:
	objagg_stats_put(ostats);
	return err;
}