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
typedef  int /*<<< orphan*/  u32 ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_PEFA_LEN ; 
 int /*<<< orphan*/  mlxsw_reg_pefa_pack (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlxsw_reg_pefa_unpack (char*,int*) ; 
 int mlxsw_reg_query (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pefa ; 

__attribute__((used)) static int mlxsw_sp2_act_kvdl_set_activity_get(void *priv, u32 kvdl_index,
					       bool *activity)
{
	struct mlxsw_sp *mlxsw_sp = priv;
	char pefa_pl[MLXSW_REG_PEFA_LEN];
	int err;

	mlxsw_reg_pefa_pack(pefa_pl, kvdl_index, true, NULL);
	err = mlxsw_reg_query(mlxsw_sp->core, MLXSW_REG(pefa), pefa_pl);
	if (err)
		return err;
	mlxsw_reg_pefa_unpack(pefa_pl, activity);
	return 0;
}