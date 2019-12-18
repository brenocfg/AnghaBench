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
struct TYPE_2__ {int /*<<< orphan*/  max; int /*<<< orphan*/  cur; } ;
struct mlxsw_sp_sb_pm {TYPE_1__ occ; } ;
struct mlxsw_core {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_reg_sbpm_unpack (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlxsw_sp_sb_pm_occ_query_cb(struct mlxsw_core *mlxsw_core,
					char *sbpm_pl, size_t sbpm_pl_len,
					unsigned long cb_priv)
{
	struct mlxsw_sp_sb_pm *pm = (struct mlxsw_sp_sb_pm *) cb_priv;

	mlxsw_reg_sbpm_unpack(sbpm_pl, &pm->occ.cur, &pm->occ.max);
}