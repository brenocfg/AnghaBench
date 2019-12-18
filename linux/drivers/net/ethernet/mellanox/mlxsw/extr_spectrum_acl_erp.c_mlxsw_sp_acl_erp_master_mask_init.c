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
struct mlxsw_sp_acl_atcam_region {TYPE_1__* region; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; struct mlxsw_sp* mlxsw_sp; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_PERCR_LEN ; 
 int /*<<< orphan*/  mlxsw_reg_percr_pack (char*,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  percr ; 

__attribute__((used)) static int
mlxsw_sp_acl_erp_master_mask_init(struct mlxsw_sp_acl_atcam_region *aregion)
{
	struct mlxsw_sp *mlxsw_sp = aregion->region->mlxsw_sp;
	char percr_pl[MLXSW_REG_PERCR_LEN];

	mlxsw_reg_percr_pack(percr_pl, aregion->region->id);
	return mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(percr), percr_pl);
}