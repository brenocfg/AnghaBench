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
struct mlxsw_sp1_mr_tcam_region {int /*<<< orphan*/  rtar_key_type; struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_RRCR_LEN ; 
 int /*<<< orphan*/  MLXSW_REG_RRCR_OP_MOVE ; 
 int /*<<< orphan*/  mlxsw_reg_rrcr_pack (char*,int /*<<< orphan*/ ,unsigned long,unsigned long,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rrcr ; 

__attribute__((used)) static void mlxsw_sp1_mr_tcam_region_parman_move(void *priv,
						 unsigned long from_index,
						 unsigned long to_index,
						 unsigned long count)
{
	struct mlxsw_sp1_mr_tcam_region *mr_tcam_region = priv;
	struct mlxsw_sp *mlxsw_sp = mr_tcam_region->mlxsw_sp;
	char rrcr_pl[MLXSW_REG_RRCR_LEN];

	mlxsw_reg_rrcr_pack(rrcr_pl, MLXSW_REG_RRCR_OP_MOVE,
			    from_index, count,
			    mr_tcam_region->rtar_key_type, to_index);
	mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(rrcr), rrcr_pl);
}