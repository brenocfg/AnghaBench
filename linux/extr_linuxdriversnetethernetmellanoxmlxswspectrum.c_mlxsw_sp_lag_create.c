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
 int MLXSW_REG_SLDR_LEN ; 
 int /*<<< orphan*/  mlxsw_reg_sldr_lag_create_pack (char*,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sldr ; 

__attribute__((used)) static int mlxsw_sp_lag_create(struct mlxsw_sp *mlxsw_sp, u16 lag_id)
{
	char sldr_pl[MLXSW_REG_SLDR_LEN];

	mlxsw_reg_sldr_lag_create_pack(sldr_pl, lag_id);
	return mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(sldr), sldr_pl);
}