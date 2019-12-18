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
typedef  int /*<<< orphan*/  u16 ;
struct mlxsw_sp_nve_config {int learning_en; int /*<<< orphan*/  ul_tb_id; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; TYPE_1__* nve; } ;
struct TYPE_2__ {int /*<<< orphan*/  ul_rif_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_TNGCR_LEN ; 
 int /*<<< orphan*/  mlxsw_reg_tngcr_underlay_rif_set (char*,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int mlxsw_sp2_nve_vxlan_learning_set (struct mlxsw_sp*,int) ; 
 int /*<<< orphan*/  mlxsw_sp_nve_vxlan_config_prepare (char*,struct mlxsw_sp_nve_config const*) ; 
 int mlxsw_sp_router_ul_rif_get (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_sp_router_ul_rif_put (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tngcr ; 

__attribute__((used)) static int
mlxsw_sp2_nve_vxlan_config_set(struct mlxsw_sp *mlxsw_sp,
			       const struct mlxsw_sp_nve_config *config)
{
	char tngcr_pl[MLXSW_REG_TNGCR_LEN];
	u16 ul_rif_index;
	int err;

	err = mlxsw_sp_router_ul_rif_get(mlxsw_sp, config->ul_tb_id,
					 &ul_rif_index);
	if (err)
		return err;
	mlxsw_sp->nve->ul_rif_index = ul_rif_index;

	err = mlxsw_sp2_nve_vxlan_learning_set(mlxsw_sp, config->learning_en);
	if (err)
		goto err_vxlan_learning_set;

	mlxsw_sp_nve_vxlan_config_prepare(tngcr_pl, config);
	mlxsw_reg_tngcr_underlay_rif_set(tngcr_pl, ul_rif_index);

	err = mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(tngcr), tngcr_pl);
	if (err)
		goto err_tngcr_write;

	return 0;

err_tngcr_write:
	mlxsw_sp2_nve_vxlan_learning_set(mlxsw_sp, false);
err_vxlan_learning_set:
	mlxsw_sp_router_ul_rif_put(mlxsw_sp, ul_rif_index);
	return err;
}