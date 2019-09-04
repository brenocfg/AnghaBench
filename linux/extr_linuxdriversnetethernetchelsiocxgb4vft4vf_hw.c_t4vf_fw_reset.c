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
struct fw_reset_cmd {void* retval_len16; void* op_to_write; } ;
struct adapter {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int FW_CMD_OP_V (int /*<<< orphan*/ ) ; 
 int FW_CMD_WRITE_F ; 
 int FW_LEN16 (struct fw_reset_cmd) ; 
 int /*<<< orphan*/  FW_RESET_CMD ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memset (struct fw_reset_cmd*,int /*<<< orphan*/ ,int) ; 
 int t4vf_wr_mbox (struct adapter*,struct fw_reset_cmd*,int,int /*<<< orphan*/ *) ; 

int t4vf_fw_reset(struct adapter *adapter)
{
	struct fw_reset_cmd cmd;

	memset(&cmd, 0, sizeof(cmd));
	cmd.op_to_write = cpu_to_be32(FW_CMD_OP_V(FW_RESET_CMD) |
				      FW_CMD_WRITE_F);
	cmd.retval_len16 = cpu_to_be32(FW_LEN16(cmd));
	return t4vf_wr_mbox(adapter, &cmd, sizeof(cmd), NULL);
}