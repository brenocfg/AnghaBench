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
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_SFD_REC_ACTION_FORWARD_IP_ROUTER ; 
 int /*<<< orphan*/  MLXSW_REG_SFD_REC_POLICY_STATIC_ENTRY ; 
 int __mlxsw_sp_port_fdb_uc_op (struct mlxsw_sp*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mlxsw_sp_rif_fdb_op(struct mlxsw_sp *mlxsw_sp, const char *mac, u16 fid,
			bool adding)
{
	return __mlxsw_sp_port_fdb_uc_op(mlxsw_sp, 0, mac, fid, adding,
					 MLXSW_REG_SFD_REC_ACTION_FORWARD_IP_ROUTER,
					 MLXSW_REG_SFD_REC_POLICY_STATIC_ENTRY);
}