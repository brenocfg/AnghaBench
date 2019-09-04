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
struct fw_eq_eth_cmd {void* eqid_pkd; void* alloc_to_len16; void* op_to_vfn; } ;
struct adapter {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int FW_CMD_EXEC_F ; 
 int FW_CMD_OP_V (int /*<<< orphan*/ ) ; 
 int FW_CMD_REQUEST_F ; 
 int /*<<< orphan*/  FW_EQ_ETH_CMD ; 
 int FW_EQ_ETH_CMD_EQID_V (unsigned int) ; 
 int FW_EQ_ETH_CMD_FREE_F ; 
 int FW_LEN16 (struct fw_eq_eth_cmd) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memset (struct fw_eq_eth_cmd*,int /*<<< orphan*/ ,int) ; 
 int t4vf_wr_mbox (struct adapter*,struct fw_eq_eth_cmd*,int,int /*<<< orphan*/ *) ; 

int t4vf_eth_eq_free(struct adapter *adapter, unsigned int eqid)
{
	struct fw_eq_eth_cmd cmd;

	memset(&cmd, 0, sizeof(cmd));
	cmd.op_to_vfn = cpu_to_be32(FW_CMD_OP_V(FW_EQ_ETH_CMD) |
				    FW_CMD_REQUEST_F |
				    FW_CMD_EXEC_F);
	cmd.alloc_to_len16 = cpu_to_be32(FW_EQ_ETH_CMD_FREE_F |
					 FW_LEN16(cmd));
	cmd.eqid_pkd = cpu_to_be32(FW_EQ_ETH_CMD_EQID_V(eqid));
	return t4vf_wr_mbox(adapter, &cmd, sizeof(cmd), NULL);
}