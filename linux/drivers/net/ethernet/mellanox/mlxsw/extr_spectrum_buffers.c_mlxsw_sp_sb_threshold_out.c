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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct mlxsw_sp_sb_pr {scalar_t__ mode; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 scalar_t__ MLXSW_REG_SBPR_MODE_DYNAMIC ; 
 scalar_t__ MLXSW_SP_SB_THRESHOLD_TO_ALPHA_OFFSET ; 
 scalar_t__ mlxsw_sp_cells_bytes (struct mlxsw_sp*,scalar_t__) ; 
 struct mlxsw_sp_sb_pr* mlxsw_sp_sb_pr_get (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 mlxsw_sp_sb_threshold_out(struct mlxsw_sp *mlxsw_sp, u16 pool_index,
				     u32 max_buff)
{
	struct mlxsw_sp_sb_pr *pr = mlxsw_sp_sb_pr_get(mlxsw_sp, pool_index);

	if (pr->mode == MLXSW_REG_SBPR_MODE_DYNAMIC)
		return max_buff - MLXSW_SP_SB_THRESHOLD_TO_ALPHA_OFFSET;
	return mlxsw_sp_cells_bytes(mlxsw_sp, max_buff);
}