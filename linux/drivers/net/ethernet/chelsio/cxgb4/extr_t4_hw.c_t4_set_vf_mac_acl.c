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
struct fw_acl_mac_cmd {unsigned int nmac; int /*<<< orphan*/  macaddr0; int /*<<< orphan*/  macaddr1; int /*<<< orphan*/  macaddr2; int /*<<< orphan*/  macaddr3; void* en_to_len16; void* op_to_vfn; } ;
struct adapter {int pf; int /*<<< orphan*/  mbox; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  FW_ACL_MAC_CMD ; 
 unsigned int FW_ACL_MAC_CMD_PFN_V (int) ; 
 unsigned int FW_ACL_MAC_CMD_VFN_V (unsigned int) ; 
 unsigned int FW_CMD_OP_V (int /*<<< orphan*/ ) ; 
 unsigned int FW_CMD_REQUEST_F ; 
 unsigned int FW_CMD_WRITE_F ; 
 scalar_t__ FW_LEN16 (struct fw_acl_mac_cmd) ; 
 void* cpu_to_be32 (unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct fw_acl_mac_cmd*,int /*<<< orphan*/ ,int) ; 
 int t4_wr_mbox (struct adapter*,int /*<<< orphan*/ ,struct fw_acl_mac_cmd*,int,struct fw_acl_mac_cmd*) ; 

int t4_set_vf_mac_acl(struct adapter *adapter, unsigned int vf,
		      unsigned int naddr, u8 *addr)
{
	struct fw_acl_mac_cmd cmd;

	memset(&cmd, 0, sizeof(cmd));
	cmd.op_to_vfn = cpu_to_be32(FW_CMD_OP_V(FW_ACL_MAC_CMD) |
				    FW_CMD_REQUEST_F |
				    FW_CMD_WRITE_F |
				    FW_ACL_MAC_CMD_PFN_V(adapter->pf) |
				    FW_ACL_MAC_CMD_VFN_V(vf));

	/* Note: Do not enable the ACL */
	cmd.en_to_len16 = cpu_to_be32((unsigned int)FW_LEN16(cmd));
	cmd.nmac = naddr;

	switch (adapter->pf) {
	case 3:
		memcpy(cmd.macaddr3, addr, sizeof(cmd.macaddr3));
		break;
	case 2:
		memcpy(cmd.macaddr2, addr, sizeof(cmd.macaddr2));
		break;
	case 1:
		memcpy(cmd.macaddr1, addr, sizeof(cmd.macaddr1));
		break;
	case 0:
		memcpy(cmd.macaddr0, addr, sizeof(cmd.macaddr0));
		break;
	}

	return t4_wr_mbox(adapter, adapter->mbox, &cmd, sizeof(cmd), &cmd);
}