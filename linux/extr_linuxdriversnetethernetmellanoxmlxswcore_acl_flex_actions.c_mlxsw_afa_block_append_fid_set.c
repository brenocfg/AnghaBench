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
struct netlink_ext_ack {int dummy; } ;
struct mlxsw_afa_block {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (char*) ; 
 int /*<<< orphan*/  MLXSW_AFA_VIRFWD_CODE ; 
 int /*<<< orphan*/  MLXSW_AFA_VIRFWD_FID_CMD_SET ; 
 int /*<<< orphan*/  MLXSW_AFA_VIRFWD_SIZE ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 int PTR_ERR (char*) ; 
 char* mlxsw_afa_block_append_action (struct mlxsw_afa_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_afa_virfwd_pack (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mlxsw_afa_block_append_fid_set(struct mlxsw_afa_block *block, u16 fid,
				   struct netlink_ext_ack *extack)
{
	char *act = mlxsw_afa_block_append_action(block,
						  MLXSW_AFA_VIRFWD_CODE,
						  MLXSW_AFA_VIRFWD_SIZE);
	if (IS_ERR(act)) {
		NL_SET_ERR_MSG_MOD(extack, "Cannot append fid_set action");
		return PTR_ERR(act);
	}
	mlxsw_afa_virfwd_pack(act, MLXSW_AFA_VIRFWD_FID_CMD_SET, fid);
	return 0;
}