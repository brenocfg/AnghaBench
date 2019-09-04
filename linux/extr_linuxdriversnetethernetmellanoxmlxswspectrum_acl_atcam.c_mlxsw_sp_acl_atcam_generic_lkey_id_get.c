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
typedef  int /*<<< orphan*/  u8 ;
struct mlxsw_sp_acl_rule_info {int dummy; } ;
struct mlxsw_sp_acl_atcam_lkey_id {int dummy; } ;
struct mlxsw_sp_acl_atcam_region_generic {struct mlxsw_sp_acl_atcam_lkey_id dummy_lkey_id; } ;
struct mlxsw_sp_acl_atcam_region {struct mlxsw_sp_acl_atcam_region_generic* priv; } ;

/* Variables and functions */

__attribute__((used)) static struct mlxsw_sp_acl_atcam_lkey_id *
mlxsw_sp_acl_atcam_generic_lkey_id_get(struct mlxsw_sp_acl_atcam_region *aregion,
				       struct mlxsw_sp_acl_rule_info *rulei,
				       u8 erp_id)
{
	struct mlxsw_sp_acl_atcam_region_generic *region_generic;

	region_generic = aregion->priv;
	return &region_generic->dummy_lkey_id;
}