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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG_SFD_REC_ACTION_NOP ; 
 int __mlxsw_sp_port_fdb_uc_op (struct mlxsw_sp*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_sfd_rec_policy (int) ; 

__attribute__((used)) static int mlxsw_sp_port_fdb_uc_op(struct mlxsw_sp *mlxsw_sp, u8 local_port,
				   const char *mac, u16 fid, bool adding,
				   bool dynamic)
{
	return __mlxsw_sp_port_fdb_uc_op(mlxsw_sp, local_port, mac, fid, adding,
					 MLXSW_REG_SFD_REC_ACTION_NOP,
					 mlxsw_sp_sfd_rec_policy(dynamic));
}