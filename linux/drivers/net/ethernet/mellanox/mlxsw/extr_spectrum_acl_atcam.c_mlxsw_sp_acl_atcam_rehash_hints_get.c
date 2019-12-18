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
struct mlxsw_sp_acl_atcam_region {int dummy; } ;

/* Variables and functions */
 void* mlxsw_sp_acl_erp_rehash_hints_get (struct mlxsw_sp_acl_atcam_region*) ; 

void *
mlxsw_sp_acl_atcam_rehash_hints_get(struct mlxsw_sp_acl_atcam_region *aregion)
{
	return mlxsw_sp_acl_erp_rehash_hints_get(aregion);
}