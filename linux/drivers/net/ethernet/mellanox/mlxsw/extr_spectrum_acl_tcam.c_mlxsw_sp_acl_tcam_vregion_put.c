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
struct mlxsw_sp_acl_tcam_vregion {scalar_t__ ref_count; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_vregion_destroy (struct mlxsw_sp*,struct mlxsw_sp_acl_tcam_vregion*) ; 

__attribute__((used)) static void
mlxsw_sp_acl_tcam_vregion_put(struct mlxsw_sp *mlxsw_sp,
			      struct mlxsw_sp_acl_tcam_vregion *vregion)
{
	if (--vregion->ref_count)
		return;
	mlxsw_sp_acl_tcam_vregion_destroy(mlxsw_sp, vregion);
}