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
struct mlxsw_sp_acl_atcam_region {int /*<<< orphan*/  entries_ht; } ;
struct mlxsw_sp_acl_atcam_entry {int /*<<< orphan*/  erp_mask; int /*<<< orphan*/  list; int /*<<< orphan*/  ht_node; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_atcam_entries_ht_params ; 
 int /*<<< orphan*/  mlxsw_sp_acl_atcam_region_entry_remove (struct mlxsw_sp*,struct mlxsw_sp_acl_atcam_region*,struct mlxsw_sp_acl_atcam_entry*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_erp_bf_remove (struct mlxsw_sp*,struct mlxsw_sp_acl_atcam_region*,int /*<<< orphan*/ ,struct mlxsw_sp_acl_atcam_entry*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_erp_mask_put (struct mlxsw_sp_acl_atcam_region*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
__mlxsw_sp_acl_atcam_entry_del(struct mlxsw_sp *mlxsw_sp,
			       struct mlxsw_sp_acl_atcam_region *aregion,
			       struct mlxsw_sp_acl_atcam_entry *aentry)
{
	mlxsw_sp_acl_atcam_region_entry_remove(mlxsw_sp, aregion, aentry);
	mlxsw_sp_acl_erp_bf_remove(mlxsw_sp, aregion, aentry->erp_mask, aentry);
	rhashtable_remove_fast(&aregion->entries_ht, &aentry->ht_node,
			       mlxsw_sp_acl_atcam_entries_ht_params);
	list_del(&aentry->list);
	mlxsw_sp_acl_erp_mask_put(aregion, aentry->erp_mask);
}