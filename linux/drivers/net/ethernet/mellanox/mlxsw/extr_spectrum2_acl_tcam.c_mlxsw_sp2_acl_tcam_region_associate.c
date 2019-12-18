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
struct mlxsw_sp_acl_tcam_region {int /*<<< orphan*/  id; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int mlxsw_sp_acl_atcam_region_associate (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mlxsw_sp2_acl_tcam_region_associate(struct mlxsw_sp *mlxsw_sp,
				    struct mlxsw_sp_acl_tcam_region *region)
{
	return mlxsw_sp_acl_atcam_region_associate(mlxsw_sp, region->id);
}