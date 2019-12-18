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
typedef  int /*<<< orphan*/  u32 ;
struct mlxsw_sp_acl {int /*<<< orphan*/  tcam; } ;
struct mlxsw_sp {struct mlxsw_sp_acl* acl; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp_acl_tcam_vregion_rehash_intrvl_get (struct mlxsw_sp*,int /*<<< orphan*/ *) ; 

u32 mlxsw_sp_acl_region_rehash_intrvl_get(struct mlxsw_sp *mlxsw_sp)
{
	struct mlxsw_sp_acl *acl = mlxsw_sp->acl;

	return mlxsw_sp_acl_tcam_vregion_rehash_intrvl_get(mlxsw_sp,
							   &acl->tcam);
}