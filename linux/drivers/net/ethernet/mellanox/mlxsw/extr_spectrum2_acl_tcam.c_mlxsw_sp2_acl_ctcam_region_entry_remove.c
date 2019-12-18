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
struct mlxsw_sp_acl_ctcam_region {int dummy; } ;
struct mlxsw_sp_acl_ctcam_entry {int dummy; } ;
struct mlxsw_sp_acl_atcam_region {int dummy; } ;
struct mlxsw_sp_acl_atcam_entry {int /*<<< orphan*/  erp_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp_acl_erp_mask_put (struct mlxsw_sp_acl_atcam_region*,int /*<<< orphan*/ ) ; 
 struct mlxsw_sp_acl_atcam_entry* mlxsw_sp_acl_tcam_centry_aentry (struct mlxsw_sp_acl_ctcam_entry*) ; 
 struct mlxsw_sp_acl_atcam_region* mlxsw_sp_acl_tcam_cregion_aregion (struct mlxsw_sp_acl_ctcam_region*) ; 

__attribute__((used)) static void
mlxsw_sp2_acl_ctcam_region_entry_remove(struct mlxsw_sp_acl_ctcam_region *cregion,
					struct mlxsw_sp_acl_ctcam_entry *centry)
{
	struct mlxsw_sp_acl_atcam_region *aregion;
	struct mlxsw_sp_acl_atcam_entry *aentry;

	aregion = mlxsw_sp_acl_tcam_cregion_aregion(cregion);
	aentry = mlxsw_sp_acl_tcam_centry_aentry(centry);

	mlxsw_sp_acl_erp_mask_put(aregion, aentry->erp_mask);
}