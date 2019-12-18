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
struct mlxsw_sp {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_MTPPPC_LEN ; 
 int /*<<< orphan*/  mlxsw_reg_mtpppc_pack (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtpppc ; 

__attribute__((used)) static int mlxsw_sp1_ptp_mtpppc_set(struct mlxsw_sp *mlxsw_sp,
				    u16 ing_types, u16 egr_types)
{
	char mtpppc_pl[MLXSW_REG_MTPPPC_LEN];

	mlxsw_reg_mtpppc_pack(mtpppc_pl, ing_types, egr_types);
	return mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(mtpppc), mtpppc_pl);
}