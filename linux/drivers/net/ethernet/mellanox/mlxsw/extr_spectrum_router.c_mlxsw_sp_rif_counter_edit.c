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
typedef  enum mlxsw_sp_rif_counter_dir { ____Placeholder_mlxsw_sp_rif_counter_dir } mlxsw_sp_rif_counter_dir ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_RITR_LEN ; 
 int MLXSW_SP_RIF_COUNTER_EGRESS ; 
 int mlxsw_reg_query (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_reg_ritr_counter_pack (char*,unsigned int,int,int) ; 
 int /*<<< orphan*/  mlxsw_reg_ritr_rif_pack (char*,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ritr ; 

__attribute__((used)) static int mlxsw_sp_rif_counter_edit(struct mlxsw_sp *mlxsw_sp, u16 rif_index,
				     unsigned int counter_index, bool enable,
				     enum mlxsw_sp_rif_counter_dir dir)
{
	char ritr_pl[MLXSW_REG_RITR_LEN];
	bool is_egress = false;
	int err;

	if (dir == MLXSW_SP_RIF_COUNTER_EGRESS)
		is_egress = true;
	mlxsw_reg_ritr_rif_pack(ritr_pl, rif_index);
	err = mlxsw_reg_query(mlxsw_sp->core, MLXSW_REG(ritr), ritr_pl);
	if (err)
		return err;

	mlxsw_reg_ritr_counter_pack(ritr_pl, counter_index, enable,
				    is_egress);
	return mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(ritr), ritr_pl);
}