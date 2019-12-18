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
struct fw_acl_vlan_cmd {int /*<<< orphan*/ * vlanid; int /*<<< orphan*/  en_to_len16; int /*<<< orphan*/  op_to_vfn; } ;
struct adapter {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  FW_ACL_VLAN_CMD ; 
 int FW_CMD_OP_V (int /*<<< orphan*/ ) ; 
 int FW_CMD_READ_F ; 
 int FW_CMD_REQUEST_F ; 
 scalar_t__ FW_LEN16 (struct fw_acl_vlan_cmd) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (unsigned int) ; 
 int /*<<< orphan*/  htonl (int) ; 
 int t4vf_wr_mbox (struct adapter*,struct fw_acl_vlan_cmd*,int,struct fw_acl_vlan_cmd*) ; 

int t4vf_get_vf_vlan_acl(struct adapter *adapter)
{
	struct fw_acl_vlan_cmd cmd;
	int vlan = 0;
	int ret = 0;

	cmd.op_to_vfn = htonl(FW_CMD_OP_V(FW_ACL_VLAN_CMD) |
			      FW_CMD_REQUEST_F | FW_CMD_READ_F);

	/* Note: Do not enable the ACL */
	cmd.en_to_len16 = cpu_to_be32((unsigned int)FW_LEN16(cmd));

	ret = t4vf_wr_mbox(adapter, &cmd, sizeof(cmd), &cmd);

	if (!ret)
		vlan = be16_to_cpu(cmd.vlanid[0]);

	return vlan;
}