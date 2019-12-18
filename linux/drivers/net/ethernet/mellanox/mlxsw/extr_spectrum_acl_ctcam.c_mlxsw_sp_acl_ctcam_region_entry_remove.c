#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mlxsw_sp_acl_ctcam_region {TYPE_3__* ops; TYPE_1__* region; } ;
struct TYPE_5__ {int /*<<< orphan*/  index; } ;
struct mlxsw_sp_acl_ctcam_entry {TYPE_2__ parman_item; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* entry_remove ) (struct mlxsw_sp_acl_ctcam_region*,struct mlxsw_sp_acl_ctcam_entry*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  tcam_region_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_PTCE2_LEN ; 
 int /*<<< orphan*/  MLXSW_REG_PTCE2_OP_WRITE_WRITE ; 
 int /*<<< orphan*/  mlxsw_reg_ptce2_pack (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ptce2 ; 
 int /*<<< orphan*/  stub1 (struct mlxsw_sp_acl_ctcam_region*,struct mlxsw_sp_acl_ctcam_entry*) ; 

__attribute__((used)) static void
mlxsw_sp_acl_ctcam_region_entry_remove(struct mlxsw_sp *mlxsw_sp,
				       struct mlxsw_sp_acl_ctcam_region *cregion,
				       struct mlxsw_sp_acl_ctcam_entry *centry)
{
	char ptce2_pl[MLXSW_REG_PTCE2_LEN];

	mlxsw_reg_ptce2_pack(ptce2_pl, false, MLXSW_REG_PTCE2_OP_WRITE_WRITE,
			     cregion->region->tcam_region_info,
			     centry->parman_item.index, 0);
	mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(ptce2), ptce2_pl);
	cregion->ops->entry_remove(cregion, centry);
}