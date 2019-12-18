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
struct mlxsw_sp_acl_ctcam_region {TYPE_1__* region; } ;
struct TYPE_4__ {int /*<<< orphan*/  index; } ;
struct mlxsw_sp_acl_ctcam_entry {TYPE_2__ parman_item; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;
struct mlxsw_afa_block {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  tcam_region_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_PTCE2_LEN ; 
 int /*<<< orphan*/  MLXSW_REG_PTCE2_OP_WRITE_UPDATE ; 
 char* mlxsw_afa_block_first_set (struct mlxsw_afa_block*) ; 
 int /*<<< orphan*/  mlxsw_reg_ptce2_flex_action_set_memcpy_to (char*,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_ptce2_pack (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ptce2 ; 

__attribute__((used)) static int
mlxsw_sp_acl_ctcam_region_entry_action_replace(struct mlxsw_sp *mlxsw_sp,
					       struct mlxsw_sp_acl_ctcam_region *cregion,
					       struct mlxsw_sp_acl_ctcam_entry *centry,
					       struct mlxsw_afa_block *afa_block,
					       unsigned int priority)
{
	char ptce2_pl[MLXSW_REG_PTCE2_LEN];
	char *act_set;

	mlxsw_reg_ptce2_pack(ptce2_pl, true, MLXSW_REG_PTCE2_OP_WRITE_UPDATE,
			     cregion->region->tcam_region_info,
			     centry->parman_item.index, priority);

	act_set = mlxsw_afa_block_first_set(afa_block);
	mlxsw_reg_ptce2_flex_action_set_memcpy_to(ptce2_pl, act_set);

	return mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(ptce2), ptce2_pl);
}