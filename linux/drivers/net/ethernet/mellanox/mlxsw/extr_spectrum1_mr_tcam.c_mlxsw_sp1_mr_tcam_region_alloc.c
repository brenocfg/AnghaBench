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
struct mlxsw_sp1_mr_tcam_region {int /*<<< orphan*/  rtar_key_type; struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_RTAR_LEN ; 
 int /*<<< orphan*/  MLXSW_REG_RTAR_OP_ALLOCATE ; 
 int /*<<< orphan*/  MLXSW_SP1_MR_TCAM_REGION_BASE_COUNT ; 
 int /*<<< orphan*/  mlxsw_reg_rtar_pack (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rtar ; 

__attribute__((used)) static int
mlxsw_sp1_mr_tcam_region_alloc(struct mlxsw_sp1_mr_tcam_region *mr_tcam_region)
{
	struct mlxsw_sp *mlxsw_sp = mr_tcam_region->mlxsw_sp;
	char rtar_pl[MLXSW_REG_RTAR_LEN];

	mlxsw_reg_rtar_pack(rtar_pl, MLXSW_REG_RTAR_OP_ALLOCATE,
			    mr_tcam_region->rtar_key_type,
			    MLXSW_SP1_MR_TCAM_REGION_BASE_COUNT);
	return mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(rtar), rtar_pl);
}