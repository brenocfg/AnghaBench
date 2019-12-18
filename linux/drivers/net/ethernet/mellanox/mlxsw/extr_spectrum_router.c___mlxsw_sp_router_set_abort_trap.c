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
typedef  int /*<<< orphan*/  u8 ;
struct mlxsw_sp_vr {int /*<<< orphan*/  id; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; TYPE_1__* router; } ;
typedef  enum mlxsw_reg_ralxx_protocol { ____Placeholder_mlxsw_reg_ralxx_protocol } mlxsw_reg_ralxx_protocol ;
struct TYPE_2__ {struct mlxsw_sp_vr* vrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_VRS ; 
 int MLXSW_CORE_RES_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_RALST_LEN ; 
 int MLXSW_REG_RALTA_LEN ; 
 int MLXSW_REG_RALTB_LEN ; 
 int MLXSW_REG_RALUE_LEN ; 
 int /*<<< orphan*/  MLXSW_REG_RALUE_OP_WRITE_WRITE ; 
 int /*<<< orphan*/  mlxsw_reg_ralst_pack (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_ralta_pack (char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_raltb_pack (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_ralue_act_ip2me_pack (char*) ; 
 int /*<<< orphan*/  mlxsw_reg_ralue_pack (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ralst ; 
 int /*<<< orphan*/  ralta ; 
 int /*<<< orphan*/  raltb ; 
 int /*<<< orphan*/  ralue ; 

__attribute__((used)) static int __mlxsw_sp_router_set_abort_trap(struct mlxsw_sp *mlxsw_sp,
					    enum mlxsw_reg_ralxx_protocol proto,
					    u8 tree_id)
{
	char ralta_pl[MLXSW_REG_RALTA_LEN];
	char ralst_pl[MLXSW_REG_RALST_LEN];
	int i, err;

	mlxsw_reg_ralta_pack(ralta_pl, true, proto, tree_id);
	err = mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(ralta), ralta_pl);
	if (err)
		return err;

	mlxsw_reg_ralst_pack(ralst_pl, 0xff, tree_id);
	err = mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(ralst), ralst_pl);
	if (err)
		return err;

	for (i = 0; i < MLXSW_CORE_RES_GET(mlxsw_sp->core, MAX_VRS); i++) {
		struct mlxsw_sp_vr *vr = &mlxsw_sp->router->vrs[i];
		char raltb_pl[MLXSW_REG_RALTB_LEN];
		char ralue_pl[MLXSW_REG_RALUE_LEN];

		mlxsw_reg_raltb_pack(raltb_pl, vr->id, proto, tree_id);
		err = mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(raltb),
				      raltb_pl);
		if (err)
			return err;

		mlxsw_reg_ralue_pack(ralue_pl, proto,
				     MLXSW_REG_RALUE_OP_WRITE_WRITE, vr->id, 0);
		mlxsw_reg_ralue_act_ip2me_pack(ralue_pl);
		err = mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(ralue),
				      ralue_pl);
		if (err)
			return err;
	}

	return 0;
}