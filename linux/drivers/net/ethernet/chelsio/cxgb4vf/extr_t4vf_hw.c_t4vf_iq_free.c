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
struct fw_iq_cmd {void* fl1id; void* fl0id; void* iqid; void* type_to_iqandstindex; void* alloc_to_len16; void* op_to_vfn; } ;
struct adapter {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int FW_CMD_EXEC_F ; 
 int FW_CMD_OP_V (int /*<<< orphan*/ ) ; 
 int FW_CMD_REQUEST_F ; 
 int /*<<< orphan*/  FW_IQ_CMD ; 
 int FW_IQ_CMD_FREE_F ; 
 int FW_IQ_CMD_TYPE_V (unsigned int) ; 
 int FW_LEN16 (struct fw_iq_cmd) ; 
 void* cpu_to_be16 (unsigned int) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memset (struct fw_iq_cmd*,int /*<<< orphan*/ ,int) ; 
 int t4vf_wr_mbox (struct adapter*,struct fw_iq_cmd*,int,int /*<<< orphan*/ *) ; 

int t4vf_iq_free(struct adapter *adapter, unsigned int iqtype,
		 unsigned int iqid, unsigned int fl0id, unsigned int fl1id)
{
	struct fw_iq_cmd cmd;

	memset(&cmd, 0, sizeof(cmd));
	cmd.op_to_vfn = cpu_to_be32(FW_CMD_OP_V(FW_IQ_CMD) |
				    FW_CMD_REQUEST_F |
				    FW_CMD_EXEC_F);
	cmd.alloc_to_len16 = cpu_to_be32(FW_IQ_CMD_FREE_F |
					 FW_LEN16(cmd));
	cmd.type_to_iqandstindex =
		cpu_to_be32(FW_IQ_CMD_TYPE_V(iqtype));

	cmd.iqid = cpu_to_be16(iqid);
	cmd.fl0id = cpu_to_be16(fl0id);
	cmd.fl1id = cpu_to_be16(fl1id);
	return t4vf_wr_mbox(adapter, &cmd, sizeof(cmd), NULL);
}