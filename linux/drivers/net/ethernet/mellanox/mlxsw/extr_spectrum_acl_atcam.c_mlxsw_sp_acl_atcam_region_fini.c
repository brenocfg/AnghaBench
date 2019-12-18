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
struct mlxsw_sp_acl_atcam_region {int /*<<< orphan*/  entries_list; int /*<<< orphan*/  entries_ht; TYPE_1__* ops; int /*<<< orphan*/  cregion; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* fini ) (struct mlxsw_sp_acl_atcam_region*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_ctcam_region_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_erp_region_fini (struct mlxsw_sp_acl_atcam_region*) ; 
 int /*<<< orphan*/  rhashtable_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct mlxsw_sp_acl_atcam_region*) ; 

void mlxsw_sp_acl_atcam_region_fini(struct mlxsw_sp_acl_atcam_region *aregion)
{
	mlxsw_sp_acl_ctcam_region_fini(&aregion->cregion);
	mlxsw_sp_acl_erp_region_fini(aregion);
	aregion->ops->fini(aregion);
	rhashtable_destroy(&aregion->entries_ht);
	WARN_ON(!list_empty(&aregion->entries_list));
}