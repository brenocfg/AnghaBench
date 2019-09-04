#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct mlxsw_sp_acl_tcam_region {int /*<<< orphan*/  id; struct mlxsw_sp* mlxsw_sp; } ;
struct TYPE_4__ {int /*<<< orphan*/  bitmap; } ;
struct mlxsw_sp_acl_erp_table {TYPE_2__ master_mask; TYPE_1__* aregion; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;
struct TYPE_3__ {struct mlxsw_sp_acl_tcam_region* region; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_PERCR_LEN ; 
 int /*<<< orphan*/  MLXSW_SP_ACL_TCAM_MASK_LEN ; 
 int /*<<< orphan*/  bitmap_to_arr32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* mlxsw_reg_percr_master_mask_data (char*) ; 
 int /*<<< orphan*/  mlxsw_reg_percr_pack (char*,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  percr ; 

__attribute__((used)) static int
mlxsw_sp_acl_erp_master_mask_update(struct mlxsw_sp_acl_erp_table *erp_table)
{
	struct mlxsw_sp_acl_tcam_region *region = erp_table->aregion->region;
	struct mlxsw_sp *mlxsw_sp = region->mlxsw_sp;
	char percr_pl[MLXSW_REG_PERCR_LEN];
	char *master_mask;

	mlxsw_reg_percr_pack(percr_pl, region->id);
	master_mask = mlxsw_reg_percr_master_mask_data(percr_pl);
	bitmap_to_arr32((u32 *) master_mask, erp_table->master_mask.bitmap,
			MLXSW_SP_ACL_TCAM_MASK_LEN);

	return mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(percr), percr_pl);
}