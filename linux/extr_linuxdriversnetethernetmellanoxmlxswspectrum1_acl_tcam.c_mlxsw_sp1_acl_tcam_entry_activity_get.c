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
struct mlxsw_sp1_acl_tcam_region {int /*<<< orphan*/  region; } ;
struct mlxsw_sp1_acl_tcam_entry {int /*<<< orphan*/  centry; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int mlxsw_sp1_acl_tcam_region_entry_activity_get (struct mlxsw_sp*,int /*<<< orphan*/ ,unsigned int,int*) ; 
 unsigned int mlxsw_sp_acl_ctcam_entry_offset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mlxsw_sp1_acl_tcam_entry_activity_get(struct mlxsw_sp *mlxsw_sp,
				      void *region_priv, void *entry_priv,
				      bool *activity)
{
	struct mlxsw_sp1_acl_tcam_region *region = region_priv;
	struct mlxsw_sp1_acl_tcam_entry *entry = entry_priv;
	unsigned int offset;

	offset = mlxsw_sp_acl_ctcam_entry_offset(&entry->centry);
	return mlxsw_sp1_acl_tcam_region_entry_activity_get(mlxsw_sp,
							    region->region,
							    offset, activity);
}