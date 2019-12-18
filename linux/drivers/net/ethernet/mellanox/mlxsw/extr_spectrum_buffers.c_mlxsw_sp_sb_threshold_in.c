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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct netlink_ext_ack {int dummy; } ;
struct mlxsw_sp_sb_pr {scalar_t__ mode; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MLXSW_REG_SBPR_MODE_DYNAMIC ; 
 int MLXSW_REG_SBXX_DYN_MAX_BUFF_MAX ; 
 int MLXSW_REG_SBXX_DYN_MAX_BUFF_MIN ; 
 int MLXSW_SP_SB_THRESHOLD_TO_ALPHA_OFFSET ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 int mlxsw_sp_bytes_cells (struct mlxsw_sp*,int) ; 
 struct mlxsw_sp_sb_pr* mlxsw_sp_sb_pr_get (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlxsw_sp_sb_threshold_in(struct mlxsw_sp *mlxsw_sp, u16 pool_index,
				    u32 threshold, u32 *p_max_buff,
				    struct netlink_ext_ack *extack)
{
	struct mlxsw_sp_sb_pr *pr = mlxsw_sp_sb_pr_get(mlxsw_sp, pool_index);

	if (pr->mode == MLXSW_REG_SBPR_MODE_DYNAMIC) {
		int val;

		val = threshold + MLXSW_SP_SB_THRESHOLD_TO_ALPHA_OFFSET;
		if (val < MLXSW_REG_SBXX_DYN_MAX_BUFF_MIN ||
		    val > MLXSW_REG_SBXX_DYN_MAX_BUFF_MAX) {
			NL_SET_ERR_MSG_MOD(extack, "Invalid dynamic threshold value");
			return -EINVAL;
		}
		*p_max_buff = val;
	} else {
		*p_max_buff = mlxsw_sp_bytes_cells(mlxsw_sp, threshold);
	}
	return 0;
}