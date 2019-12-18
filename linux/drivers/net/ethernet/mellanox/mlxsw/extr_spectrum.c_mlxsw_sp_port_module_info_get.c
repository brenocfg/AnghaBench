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
typedef  int /*<<< orphan*/  u8 ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_PMLP_LEN ; 
 int /*<<< orphan*/  mlxsw_reg_pmlp_module_get (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_pmlp_pack (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_pmlp_tx_lane_get (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_pmlp_width_get (char*) ; 
 int mlxsw_reg_query (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pmlp ; 

__attribute__((used)) static int mlxsw_sp_port_module_info_get(struct mlxsw_sp *mlxsw_sp,
					 u8 local_port, u8 *p_module,
					 u8 *p_width, u8 *p_lane)
{
	char pmlp_pl[MLXSW_REG_PMLP_LEN];
	int err;

	mlxsw_reg_pmlp_pack(pmlp_pl, local_port);
	err = mlxsw_reg_query(mlxsw_sp->core, MLXSW_REG(pmlp), pmlp_pl);
	if (err)
		return err;
	*p_module = mlxsw_reg_pmlp_module_get(pmlp_pl, 0);
	*p_width = mlxsw_reg_pmlp_width_get(pmlp_pl);
	*p_lane = mlxsw_reg_pmlp_tx_lane_get(pmlp_pl, 0);
	return 0;
}