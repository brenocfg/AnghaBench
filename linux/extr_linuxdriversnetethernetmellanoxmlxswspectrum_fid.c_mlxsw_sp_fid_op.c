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
 int MLXSW_REG_SFMR_LEN ; 
 int /*<<< orphan*/  mlxsw_reg_sfmr_pack (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlxsw_sp_sfmr_op (int) ; 
 int /*<<< orphan*/  sfmr ; 

__attribute__((used)) static int mlxsw_sp_fid_op(struct mlxsw_sp *mlxsw_sp, u16 fid_index,
			   u16 fid_offset, bool valid)
{
	char sfmr_pl[MLXSW_REG_SFMR_LEN];

	mlxsw_reg_sfmr_pack(sfmr_pl, mlxsw_sp_sfmr_op(valid), fid_index,
			    fid_offset);
	return mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(sfmr), sfmr_pl);
}