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
typedef  enum mlxsw_reg_svfa_mt { ____Placeholder_mlxsw_reg_svfa_mt } mlxsw_reg_svfa_mt ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_SVFA_LEN ; 
 int MLXSW_REG_SVFA_MT_VID_TO_FID ; 
 int /*<<< orphan*/  mlxsw_reg_svfa_pack (char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  svfa ; 

__attribute__((used)) static int mlxsw_sp_fid_vid_map(struct mlxsw_sp *mlxsw_sp, u16 fid_index,
				u16 vid, bool valid)
{
	enum mlxsw_reg_svfa_mt mt = MLXSW_REG_SVFA_MT_VID_TO_FID;
	char svfa_pl[MLXSW_REG_SVFA_LEN];

	mlxsw_reg_svfa_pack(svfa_pl, 0, mt, valid, fid_index, vid);
	return mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(svfa), svfa_pl);
}