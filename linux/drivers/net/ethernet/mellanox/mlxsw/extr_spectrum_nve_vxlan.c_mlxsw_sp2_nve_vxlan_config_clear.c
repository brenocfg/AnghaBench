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
struct mlxsw_sp {TYPE_1__* nve; int /*<<< orphan*/  core; } ;
struct TYPE_2__ {int /*<<< orphan*/  ul_rif_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_TNGCR_LEN ; 
 int /*<<< orphan*/  MLXSW_REG_TNGCR_TYPE_VXLAN ; 
 int /*<<< orphan*/  mlxsw_reg_tngcr_pack (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_sp2_nve_vxlan_learning_set (struct mlxsw_sp*,int) ; 
 int /*<<< orphan*/  mlxsw_sp_router_ul_rif_put (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tngcr ; 

__attribute__((used)) static void mlxsw_sp2_nve_vxlan_config_clear(struct mlxsw_sp *mlxsw_sp)
{
	char tngcr_pl[MLXSW_REG_TNGCR_LEN];

	mlxsw_reg_tngcr_pack(tngcr_pl, MLXSW_REG_TNGCR_TYPE_VXLAN, false, 0);
	mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(tngcr), tngcr_pl);
	mlxsw_sp2_nve_vxlan_learning_set(mlxsw_sp, false);
	mlxsw_sp_router_ul_rif_put(mlxsw_sp, mlxsw_sp->nve->ul_rif_index);
}