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
struct mlxsw_sp_acl_atcam_region {int /*<<< orphan*/  cregion; } ;
struct mlxsw_sp_acl_atcam_entry {int /*<<< orphan*/  centry; } ;
struct mlxsw_sp_acl_atcam_chunk {int /*<<< orphan*/  cchunk; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __mlxsw_sp_acl_atcam_entry_del (struct mlxsw_sp*,struct mlxsw_sp_acl_atcam_region*,struct mlxsw_sp_acl_atcam_entry*) ; 
 scalar_t__ mlxsw_sp_acl_atcam_is_centry (struct mlxsw_sp_acl_atcam_entry*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_ctcam_entry_del (struct mlxsw_sp*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void mlxsw_sp_acl_atcam_entry_del(struct mlxsw_sp *mlxsw_sp,
				  struct mlxsw_sp_acl_atcam_region *aregion,
				  struct mlxsw_sp_acl_atcam_chunk *achunk,
				  struct mlxsw_sp_acl_atcam_entry *aentry)
{
	if (mlxsw_sp_acl_atcam_is_centry(aentry))
		mlxsw_sp_acl_ctcam_entry_del(mlxsw_sp, &aregion->cregion,
					     &achunk->cchunk, &aentry->centry);
	else
		__mlxsw_sp_acl_atcam_entry_del(mlxsw_sp, aregion, aentry);
}