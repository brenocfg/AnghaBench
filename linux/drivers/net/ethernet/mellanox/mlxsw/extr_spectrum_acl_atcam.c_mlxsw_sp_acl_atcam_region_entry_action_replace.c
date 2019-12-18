#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct mlxsw_sp_acl_tcam_region {int /*<<< orphan*/  tcam_region_info; } ;
struct mlxsw_sp_acl_rule_info {int /*<<< orphan*/  act_block; } ;
struct mlxsw_sp_acl_atcam_region {struct mlxsw_sp_acl_tcam_region* region; } ;
struct mlxsw_sp_acl_atcam_lkey_id {int /*<<< orphan*/  id; int /*<<< orphan*/  refcnt; } ;
struct TYPE_2__ {int /*<<< orphan*/  value; int /*<<< orphan*/  mask; int /*<<< orphan*/  start; } ;
struct mlxsw_sp_acl_atcam_entry {TYPE_1__ delta_info; int /*<<< orphan*/  enc_key; int /*<<< orphan*/  erp_mask; struct mlxsw_sp_acl_atcam_lkey_id* lkey_id; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_PTCE3_LEN ; 
 int /*<<< orphan*/  MLXSW_REG_PTCE3_OP_WRITE_UPDATE ; 
 int /*<<< orphan*/  mlxsw_afa_block_first_kvdl_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_ptce3_pack (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_erp_mask_erp_id (int /*<<< orphan*/ ) ; 
 int mlxsw_sp_acl_tcam_priority_get (struct mlxsw_sp*,struct mlxsw_sp_acl_rule_info*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ptce3 ; 
 int refcount_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mlxsw_sp_acl_atcam_region_entry_action_replace(struct mlxsw_sp *mlxsw_sp,
					       struct mlxsw_sp_acl_atcam_region *aregion,
					       struct mlxsw_sp_acl_atcam_entry *aentry,
					       struct mlxsw_sp_acl_rule_info *rulei)
{
	struct mlxsw_sp_acl_atcam_lkey_id *lkey_id = aentry->lkey_id;
	u8 erp_id = mlxsw_sp_acl_erp_mask_erp_id(aentry->erp_mask);
	struct mlxsw_sp_acl_tcam_region *region = aregion->region;
	char ptce3_pl[MLXSW_REG_PTCE3_LEN];
	u32 kvdl_index, priority;
	int err;

	err = mlxsw_sp_acl_tcam_priority_get(mlxsw_sp, rulei, &priority, true);
	if (err)
		return err;
	kvdl_index = mlxsw_afa_block_first_kvdl_index(rulei->act_block);
	mlxsw_reg_ptce3_pack(ptce3_pl, true, MLXSW_REG_PTCE3_OP_WRITE_UPDATE,
			     priority, region->tcam_region_info,
			     aentry->enc_key, erp_id,
			     aentry->delta_info.start,
			     aentry->delta_info.mask,
			     aentry->delta_info.value,
			     refcount_read(&lkey_id->refcnt) != 1, lkey_id->id,
			     kvdl_index);
	return mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(ptce3), ptce3_pl);
}