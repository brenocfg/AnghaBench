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
struct mlxsw_sp_acl_tcam_vchunk {scalar_t__ ref_count; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_vchunk_destroy (struct mlxsw_sp*,struct mlxsw_sp_acl_tcam_vchunk*) ; 

__attribute__((used)) static void
mlxsw_sp_acl_tcam_vchunk_put(struct mlxsw_sp *mlxsw_sp,
			     struct mlxsw_sp_acl_tcam_vchunk *vchunk)
{
	if (--vchunk->ref_count)
		return;
	mlxsw_sp_acl_tcam_vchunk_destroy(mlxsw_sp, vchunk);
}