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
struct mlxsw_sp_acl_erp {int dummy; } ;
struct mlxsw_sp_acl_ctcam_region {int dummy; } ;
struct mlxsw_sp_acl_ctcam_entry {int dummy; } ;
struct mlxsw_sp_acl_atcam_region {int dummy; } ;
struct mlxsw_sp_acl_atcam_entry {struct mlxsw_sp_acl_erp* erp; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mlxsw_sp_acl_erp*) ; 
 int PTR_ERR (struct mlxsw_sp_acl_erp*) ; 
 struct mlxsw_sp_acl_erp* mlxsw_sp_acl_erp_get (struct mlxsw_sp_acl_atcam_region*,char const*,int) ; 
 struct mlxsw_sp_acl_atcam_entry* mlxsw_sp_acl_tcam_centry_aentry (struct mlxsw_sp_acl_ctcam_entry*) ; 
 struct mlxsw_sp_acl_atcam_region* mlxsw_sp_acl_tcam_cregion_aregion (struct mlxsw_sp_acl_ctcam_region*) ; 

__attribute__((used)) static int
mlxsw_sp2_acl_ctcam_region_entry_insert(struct mlxsw_sp_acl_ctcam_region *cregion,
					struct mlxsw_sp_acl_ctcam_entry *centry,
					const char *mask)
{
	struct mlxsw_sp_acl_atcam_region *aregion;
	struct mlxsw_sp_acl_atcam_entry *aentry;
	struct mlxsw_sp_acl_erp *erp;

	aregion = mlxsw_sp_acl_tcam_cregion_aregion(cregion);
	aentry = mlxsw_sp_acl_tcam_centry_aentry(centry);

	erp = mlxsw_sp_acl_erp_get(aregion, mask, true);
	if (IS_ERR(erp))
		return PTR_ERR(erp);
	aentry->erp = erp;

	return 0;
}