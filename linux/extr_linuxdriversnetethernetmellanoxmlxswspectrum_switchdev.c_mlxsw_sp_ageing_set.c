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
typedef  int /*<<< orphan*/  u32 ;
struct mlxsw_sp {TYPE_1__* bridge; int /*<<< orphan*/  core; } ;
struct TYPE_2__ {int /*<<< orphan*/  ageing_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_SFDAT_LEN ; 
 int /*<<< orphan*/  mlxsw_reg_sfdat_pack (char*,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sfdat ; 

__attribute__((used)) static int mlxsw_sp_ageing_set(struct mlxsw_sp *mlxsw_sp, u32 ageing_time)
{
	char sfdat_pl[MLXSW_REG_SFDAT_LEN];
	int err;

	mlxsw_reg_sfdat_pack(sfdat_pl, ageing_time);
	err = mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(sfdat), sfdat_pl);
	if (err)
		return err;
	mlxsw_sp->bridge->ageing_time = ageing_time;
	return 0;
}