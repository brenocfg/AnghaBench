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
struct objagg_obj {int dummy; } ;
struct mlxsw_sp_acl_erp_table {int /*<<< orphan*/  objagg_lock; int /*<<< orphan*/  objagg; } ;
struct mlxsw_sp_acl_erp_mask {int dummy; } ;
struct mlxsw_sp_acl_atcam_region {struct mlxsw_sp_acl_erp_table* erp_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  objagg_obj_put (int /*<<< orphan*/ ,struct objagg_obj*) ; 

void mlxsw_sp_acl_erp_mask_put(struct mlxsw_sp_acl_atcam_region *aregion,
			       struct mlxsw_sp_acl_erp_mask *erp_mask)
{
	struct objagg_obj *objagg_obj = (struct objagg_obj *) erp_mask;
	struct mlxsw_sp_acl_erp_table *erp_table = aregion->erp_table;

	mutex_lock(&erp_table->objagg_lock);
	objagg_obj_put(erp_table->objagg, objagg_obj);
	mutex_unlock(&erp_table->objagg_lock);
}