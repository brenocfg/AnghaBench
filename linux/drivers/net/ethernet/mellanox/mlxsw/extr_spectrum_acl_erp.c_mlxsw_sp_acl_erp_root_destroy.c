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
struct mlxsw_sp_acl_erp_table {TYPE_1__* ops; } ;
struct mlxsw_sp_acl_atcam_region {struct mlxsw_sp_acl_erp_table* erp_table; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* erp_destroy ) (struct mlxsw_sp_acl_erp_table*,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct mlxsw_sp_acl_erp_table*,void*) ; 

__attribute__((used)) static void mlxsw_sp_acl_erp_root_destroy(void *priv, void *root_priv)
{
	struct mlxsw_sp_acl_atcam_region *aregion = priv;
	struct mlxsw_sp_acl_erp_table *erp_table = aregion->erp_table;

	erp_table->ops->erp_destroy(erp_table, root_priv);
}