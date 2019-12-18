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
 int /*<<< orphan*/  MLXSW_REG_SFDF_FLUSH_PER_NVE_AND_FID ; 
 int MLXSW_REG_SFDF_LEN ; 
 int /*<<< orphan*/  mlxsw_reg_sfdf_fid_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_sfdf_pack (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sfdf ; 

__attribute__((used)) static void mlxsw_sp_nve_fdb_flush_by_fid(struct mlxsw_sp *mlxsw_sp,
					  u16 fid_index)
{
	char sfdf_pl[MLXSW_REG_SFDF_LEN];

	mlxsw_reg_sfdf_pack(sfdf_pl, MLXSW_REG_SFDF_FLUSH_PER_NVE_AND_FID);
	mlxsw_reg_sfdf_fid_set(sfdf_pl, fid_index);
	mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(sfdf), sfdf_pl);
}