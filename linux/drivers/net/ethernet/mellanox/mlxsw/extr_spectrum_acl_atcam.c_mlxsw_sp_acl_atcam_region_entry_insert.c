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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct mlxsw_sp_acl_tcam_region {int /*<<< orphan*/  tcam_region_info; } ;
struct mlxsw_sp_acl_rule_info {int /*<<< orphan*/  act_block; } ;
struct mlxsw_sp_acl_atcam_region {TYPE_2__* ops; struct mlxsw_sp_acl_tcam_region* region; } ;
struct mlxsw_sp_acl_atcam_lkey_id {int /*<<< orphan*/  id; int /*<<< orphan*/  refcnt; } ;
struct TYPE_3__ {int /*<<< orphan*/  value; int /*<<< orphan*/  mask; int /*<<< orphan*/  start; } ;
struct mlxsw_sp_acl_atcam_entry {TYPE_1__ delta_info; int /*<<< orphan*/  enc_key; struct mlxsw_sp_acl_atcam_lkey_id* lkey_id; int /*<<< orphan*/  erp_mask; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* lkey_id_put ) (struct mlxsw_sp_acl_atcam_region*,struct mlxsw_sp_acl_atcam_lkey_id*) ;struct mlxsw_sp_acl_atcam_lkey_id* (* lkey_id_get ) (struct mlxsw_sp_acl_atcam_region*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mlxsw_sp_acl_atcam_lkey_id*) ; 
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_PTCE3_LEN ; 
 int /*<<< orphan*/  MLXSW_REG_PTCE3_OP_WRITE_WRITE ; 
 int PTR_ERR (struct mlxsw_sp_acl_atcam_lkey_id*) ; 
 int /*<<< orphan*/  mlxsw_afa_block_first_kvdl_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_ptce3_pack (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_sp_acl_erp_mask_erp_id (int /*<<< orphan*/ ) ; 
 int mlxsw_sp_acl_tcam_priority_get (struct mlxsw_sp*,struct mlxsw_sp_acl_rule_info*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ptce3 ; 
 int refcount_read (int /*<<< orphan*/ *) ; 
 struct mlxsw_sp_acl_atcam_lkey_id* stub1 (struct mlxsw_sp_acl_atcam_region*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct mlxsw_sp_acl_atcam_region*,struct mlxsw_sp_acl_atcam_lkey_id*) ; 

__attribute__((used)) static int
mlxsw_sp_acl_atcam_region_entry_insert(struct mlxsw_sp *mlxsw_sp,
				       struct mlxsw_sp_acl_atcam_region *aregion,
				       struct mlxsw_sp_acl_atcam_entry *aentry,
				       struct mlxsw_sp_acl_rule_info *rulei)
{
	struct mlxsw_sp_acl_tcam_region *region = aregion->region;
	u8 erp_id = mlxsw_sp_acl_erp_mask_erp_id(aentry->erp_mask);
	struct mlxsw_sp_acl_atcam_lkey_id *lkey_id;
	char ptce3_pl[MLXSW_REG_PTCE3_LEN];
	u32 kvdl_index, priority;
	int err;

	err = mlxsw_sp_acl_tcam_priority_get(mlxsw_sp, rulei, &priority, true);
	if (err)
		return err;

	lkey_id = aregion->ops->lkey_id_get(aregion, aentry->enc_key, erp_id);
	if (IS_ERR(lkey_id))
		return PTR_ERR(lkey_id);
	aentry->lkey_id = lkey_id;

	kvdl_index = mlxsw_afa_block_first_kvdl_index(rulei->act_block);
	mlxsw_reg_ptce3_pack(ptce3_pl, true, MLXSW_REG_PTCE3_OP_WRITE_WRITE,
			     priority, region->tcam_region_info,
			     aentry->enc_key, erp_id,
			     aentry->delta_info.start,
			     aentry->delta_info.mask,
			     aentry->delta_info.value,
			     refcount_read(&lkey_id->refcnt) != 1, lkey_id->id,
			     kvdl_index);
	err = mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(ptce3), ptce3_pl);
	if (err)
		goto err_ptce3_write;

	return 0;

err_ptce3_write:
	aregion->ops->lkey_id_put(aregion, lkey_id);
	return err;
}