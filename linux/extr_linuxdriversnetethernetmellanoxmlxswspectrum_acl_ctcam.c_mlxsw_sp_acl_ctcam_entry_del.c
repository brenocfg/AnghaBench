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
struct mlxsw_sp_acl_ctcam_region {int /*<<< orphan*/  parman; } ;
struct mlxsw_sp_acl_ctcam_entry {int /*<<< orphan*/  parman_item; } ;
struct mlxsw_sp_acl_ctcam_chunk {int /*<<< orphan*/  parman_prio; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp_acl_ctcam_region_entry_remove (struct mlxsw_sp*,struct mlxsw_sp_acl_ctcam_region*,struct mlxsw_sp_acl_ctcam_entry*) ; 
 int /*<<< orphan*/  parman_item_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void mlxsw_sp_acl_ctcam_entry_del(struct mlxsw_sp *mlxsw_sp,
				  struct mlxsw_sp_acl_ctcam_region *cregion,
				  struct mlxsw_sp_acl_ctcam_chunk *cchunk,
				  struct mlxsw_sp_acl_ctcam_entry *centry)
{
	mlxsw_sp_acl_ctcam_region_entry_remove(mlxsw_sp, cregion, centry);
	parman_item_remove(cregion->parman, &cchunk->parman_prio,
			   &centry->parman_item);
}