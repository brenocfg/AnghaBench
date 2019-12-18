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
struct mlxsw_sp_nve_config {int /*<<< orphan*/  learning_en; int /*<<< orphan*/  ul_tb_id; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_TNGCR_LEN ; 
 int /*<<< orphan*/  mlxsw_reg_tngcr_learn_enable_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_tngcr_underlay_virtual_router_set (char*,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_sp_nve_vxlan_config_prepare (char*,struct mlxsw_sp_nve_config const*) ; 
 int mlxsw_sp_router_tb_id_vr_id (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tngcr ; 

__attribute__((used)) static int
mlxsw_sp1_nve_vxlan_config_set(struct mlxsw_sp *mlxsw_sp,
			       const struct mlxsw_sp_nve_config *config)
{
	char tngcr_pl[MLXSW_REG_TNGCR_LEN];
	u16 ul_vr_id;
	int err;

	err = mlxsw_sp_router_tb_id_vr_id(mlxsw_sp, config->ul_tb_id,
					  &ul_vr_id);
	if (err)
		return err;

	mlxsw_sp_nve_vxlan_config_prepare(tngcr_pl, config);
	mlxsw_reg_tngcr_learn_enable_set(tngcr_pl, config->learning_en);
	mlxsw_reg_tngcr_underlay_virtual_router_set(tngcr_pl, ul_vr_id);

	return mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(tngcr), tngcr_pl);
}