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
struct mlxsw_sp_acl_tcam_region {int /*<<< orphan*/  key_info; } ;
struct mlxsw_sp_acl_atcam_region {int type; int /*<<< orphan*/  ops; struct mlxsw_sp_acl_tcam_region* region; } ;
typedef  enum mlxsw_sp_acl_atcam_region_type { ____Placeholder_mlxsw_sp_acl_atcam_region_type } mlxsw_sp_acl_atcam_region_type ;

/* Variables and functions */
 int MLXSW_SP_ACL_ATCAM_REGION_TYPE_12KB ; 
 int MLXSW_SP_ACL_ATCAM_REGION_TYPE_2KB ; 
 int MLXSW_SP_ACL_ATCAM_REGION_TYPE_4KB ; 
 int MLXSW_SP_ACL_ATCAM_REGION_TYPE_8KB ; 
 unsigned int mlxsw_afk_key_info_blocks_count_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mlxsw_sp_acl_atcam_region_ops_arr ; 

__attribute__((used)) static void
mlxsw_sp_acl_atcam_region_type_init(struct mlxsw_sp_acl_atcam_region *aregion)
{
	struct mlxsw_sp_acl_tcam_region *region = aregion->region;
	enum mlxsw_sp_acl_atcam_region_type region_type;
	unsigned int blocks_count;

	/* We already know the blocks count can not exceed the maximum
	 * blocks count.
	 */
	blocks_count = mlxsw_afk_key_info_blocks_count_get(region->key_info);
	if (blocks_count <= 2)
		region_type = MLXSW_SP_ACL_ATCAM_REGION_TYPE_2KB;
	else if (blocks_count <= 4)
		region_type = MLXSW_SP_ACL_ATCAM_REGION_TYPE_4KB;
	else if (blocks_count <= 8)
		region_type = MLXSW_SP_ACL_ATCAM_REGION_TYPE_8KB;
	else
		region_type = MLXSW_SP_ACL_ATCAM_REGION_TYPE_12KB;

	aregion->type = region_type;
	aregion->ops = mlxsw_sp_acl_atcam_region_ops_arr[region_type];
}