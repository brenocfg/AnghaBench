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
struct netlink_ext_ack {int dummy; } ;
struct mlxsw_afa_block {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (char*) ; 
 int /*<<< orphan*/  MLXSW_AFA_VLAN_CMD_SET_OUTER ; 
 int /*<<< orphan*/  MLXSW_AFA_VLAN_CODE ; 
 int /*<<< orphan*/  MLXSW_AFA_VLAN_SIZE ; 
 int /*<<< orphan*/  MLXSW_AFA_VLAN_VLAN_TAG_CMD_NOP ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 int PTR_ERR (char*) ; 
 char* mlxsw_afa_block_append_action (struct mlxsw_afa_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_afa_vlan_pack (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mlxsw_afa_block_append_vlan_modify(struct mlxsw_afa_block *block,
				       u16 vid, u8 pcp, u8 et,
				       struct netlink_ext_ack *extack)
{
	char *act = mlxsw_afa_block_append_action(block,
						  MLXSW_AFA_VLAN_CODE,
						  MLXSW_AFA_VLAN_SIZE);

	if (IS_ERR(act)) {
		NL_SET_ERR_MSG_MOD(extack, "Cannot append vlan_modify action");
		return PTR_ERR(act);
	}
	mlxsw_afa_vlan_pack(act, MLXSW_AFA_VLAN_VLAN_TAG_CMD_NOP,
			    MLXSW_AFA_VLAN_CMD_SET_OUTER, vid,
			    MLXSW_AFA_VLAN_CMD_SET_OUTER, pcp,
			    MLXSW_AFA_VLAN_CMD_SET_OUTER, et);
	return 0;
}