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
struct mlxsw_sp {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_TIGCR_LEN ; 
 int /*<<< orphan*/  mlxsw_reg_tigcr_pack (char*,int,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tigcr ; 

__attribute__((used)) static int
mlxsw_sp_ipip_config_tigcr(struct mlxsw_sp *mlxsw_sp)
{
	char tigcr_pl[MLXSW_REG_TIGCR_LEN];

	mlxsw_reg_tigcr_pack(tigcr_pl, true, 0);
	return mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(tigcr), tigcr_pl);
}