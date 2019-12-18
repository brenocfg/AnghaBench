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
struct mlxsw_sp1_ptp_shaper_params {int /*<<< orphan*/  egr_timestamp_inc; int /*<<< orphan*/  ing_timestamp_inc; int /*<<< orphan*/  port_to_shaper_credits; int /*<<< orphan*/  shaper_bs; int /*<<< orphan*/  shaper_inc; int /*<<< orphan*/  shaper_time_mantissa; int /*<<< orphan*/  shaper_time_exp; int /*<<< orphan*/  port_speed; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_QPSC_LEN ; 
 int MLXSW_SP1_PTP_SHAPER_PARAMS_LEN ; 
 int /*<<< orphan*/  mlxsw_reg_qpsc_pack (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct mlxsw_sp1_ptp_shaper_params* mlxsw_sp1_ptp_shaper_params ; 
 int /*<<< orphan*/  qpsc ; 

__attribute__((used)) static int mlxsw_sp1_ptp_shaper_params_set(struct mlxsw_sp *mlxsw_sp)
{
	const struct mlxsw_sp1_ptp_shaper_params *params;
	char qpsc_pl[MLXSW_REG_QPSC_LEN];
	int i, err;

	for (i = 0; i < MLXSW_SP1_PTP_SHAPER_PARAMS_LEN; i++) {
		params = &mlxsw_sp1_ptp_shaper_params[i];
		mlxsw_reg_qpsc_pack(qpsc_pl, params->port_speed,
				    params->shaper_time_exp,
				    params->shaper_time_mantissa,
				    params->shaper_inc, params->shaper_bs,
				    params->port_to_shaper_credits,
				    params->ing_timestamp_inc,
				    params->egr_timestamp_inc);
		err = mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(qpsc), qpsc_pl);
		if (err)
			return err;
	}

	return 0;
}