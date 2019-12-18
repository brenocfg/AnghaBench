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
typedef  int /*<<< orphan*/  u16 ;
struct mlxsw_sp_acl_tcam_region {int /*<<< orphan*/  tcam_region_info; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_PRCR_LEN ; 
 int /*<<< orphan*/  MLXSW_REG_PRCR_OP_MOVE ; 
 int /*<<< orphan*/  mlxsw_reg_prcr_pack (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  prcr ; 

__attribute__((used)) static void
mlxsw_sp_acl_ctcam_region_move(struct mlxsw_sp *mlxsw_sp,
			       struct mlxsw_sp_acl_tcam_region *region,
			       u16 src_offset, u16 dst_offset, u16 size)
{
	char prcr_pl[MLXSW_REG_PRCR_LEN];

	mlxsw_reg_prcr_pack(prcr_pl, MLXSW_REG_PRCR_OP_MOVE,
			    region->tcam_region_info, src_offset,
			    region->tcam_region_info, dst_offset, size);
	mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(prcr), prcr_pl);
}