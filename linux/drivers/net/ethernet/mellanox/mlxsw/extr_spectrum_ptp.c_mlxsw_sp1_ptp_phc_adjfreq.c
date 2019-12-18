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
struct mlxsw_sp_ptp_clock {struct mlxsw_core* core; } ;
struct mlxsw_core {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_MTUTC_LEN ; 
 int /*<<< orphan*/  MLXSW_REG_MTUTC_OPERATION_ADJUST_FREQ ; 
 int /*<<< orphan*/  mlxsw_reg_mtutc_pack (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (struct mlxsw_core*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtutc ; 

__attribute__((used)) static int
mlxsw_sp1_ptp_phc_adjfreq(struct mlxsw_sp_ptp_clock *clock, int freq_adj)
{
	struct mlxsw_core *mlxsw_core = clock->core;
	char mtutc_pl[MLXSW_REG_MTUTC_LEN];

	mlxsw_reg_mtutc_pack(mtutc_pl, MLXSW_REG_MTUTC_OPERATION_ADJUST_FREQ,
			     freq_adj, 0);
	return mlxsw_reg_write(mlxsw_core, MLXSW_REG(mtutc), mtutc_pl);
}