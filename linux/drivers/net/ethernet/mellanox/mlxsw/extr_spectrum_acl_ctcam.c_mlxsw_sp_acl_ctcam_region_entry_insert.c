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
struct mlxsw_sp_acl_tcam_region {int /*<<< orphan*/  key_info; int /*<<< orphan*/  tcam_region_info; } ;
struct mlxsw_sp_acl_rule_info {int /*<<< orphan*/  act_block; int /*<<< orphan*/  values; } ;
struct mlxsw_sp_acl_ctcam_region {TYPE_2__* ops; struct mlxsw_sp_acl_tcam_region* region; } ;
struct TYPE_3__ {int /*<<< orphan*/  index; } ;
struct mlxsw_sp_acl_ctcam_entry {TYPE_1__ parman_item; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; int /*<<< orphan*/  acl; } ;
struct mlxsw_afk {int dummy; } ;
struct TYPE_4__ {int (* entry_insert ) (struct mlxsw_sp_acl_ctcam_region*,struct mlxsw_sp_acl_ctcam_entry*,char*) ;int /*<<< orphan*/  (* entry_remove ) (struct mlxsw_sp_acl_ctcam_region*,struct mlxsw_sp_acl_ctcam_entry*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_PTCE2_LEN ; 
 int /*<<< orphan*/  MLXSW_REG_PTCE2_OP_WRITE_WRITE ; 
 char* mlxsw_afa_block_first_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_afk_encode (struct mlxsw_afk*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_ptce2_flex_action_set_memcpy_to (char*,char*) ; 
 char* mlxsw_reg_ptce2_flex_key_blocks_data (char*) ; 
 char* mlxsw_reg_ptce2_mask_data (char*) ; 
 int /*<<< orphan*/  mlxsw_reg_ptce2_pack (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct mlxsw_afk* mlxsw_sp_acl_afk (int /*<<< orphan*/ ) ; 
 int mlxsw_sp_acl_tcam_priority_get (struct mlxsw_sp*,struct mlxsw_sp_acl_rule_info*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ptce2 ; 
 int stub1 (struct mlxsw_sp_acl_ctcam_region*,struct mlxsw_sp_acl_ctcam_entry*,char*) ; 
 int /*<<< orphan*/  stub2 (struct mlxsw_sp_acl_ctcam_region*,struct mlxsw_sp_acl_ctcam_entry*) ; 

__attribute__((used)) static int
mlxsw_sp_acl_ctcam_region_entry_insert(struct mlxsw_sp *mlxsw_sp,
				       struct mlxsw_sp_acl_ctcam_region *cregion,
				       struct mlxsw_sp_acl_ctcam_entry *centry,
				       struct mlxsw_sp_acl_rule_info *rulei,
				       bool fillup_priority)
{
	struct mlxsw_sp_acl_tcam_region *region = cregion->region;
	struct mlxsw_afk *afk = mlxsw_sp_acl_afk(mlxsw_sp->acl);
	char ptce2_pl[MLXSW_REG_PTCE2_LEN];
	char *act_set;
	u32 priority;
	char *mask;
	char *key;
	int err;

	err = mlxsw_sp_acl_tcam_priority_get(mlxsw_sp, rulei, &priority,
					     fillup_priority);
	if (err)
		return err;

	mlxsw_reg_ptce2_pack(ptce2_pl, true, MLXSW_REG_PTCE2_OP_WRITE_WRITE,
			     region->tcam_region_info,
			     centry->parman_item.index, priority);
	key = mlxsw_reg_ptce2_flex_key_blocks_data(ptce2_pl);
	mask = mlxsw_reg_ptce2_mask_data(ptce2_pl);
	mlxsw_afk_encode(afk, region->key_info, &rulei->values, key, mask);

	err = cregion->ops->entry_insert(cregion, centry, mask);
	if (err)
		return err;

	/* Only the first action set belongs here, the rest is in KVD */
	act_set = mlxsw_afa_block_first_set(rulei->act_block);
	mlxsw_reg_ptce2_flex_action_set_memcpy_to(ptce2_pl, act_set);

	err = mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(ptce2), ptce2_pl);
	if (err)
		goto err_ptce2_write;

	return 0;

err_ptce2_write:
	cregion->ops->entry_remove(cregion, centry);
	return err;
}