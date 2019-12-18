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
struct fw_vi_enable_cmd {int /*<<< orphan*/  blinkdur; void* ien_to_len16; void* op_to_viid; } ;
struct adapter {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int FW_CMD_EXEC_F ; 
 int FW_CMD_OP_V (int /*<<< orphan*/ ) ; 
 int FW_CMD_REQUEST_F ; 
 int FW_LEN16 (struct fw_vi_enable_cmd) ; 
 int /*<<< orphan*/  FW_VI_ENABLE_CMD ; 
 int FW_VI_ENABLE_CMD_LED_F ; 
 int FW_VI_ENABLE_CMD_VIID_V (unsigned int) ; 
 int /*<<< orphan*/  cpu_to_be16 (unsigned int) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memset (struct fw_vi_enable_cmd*,int /*<<< orphan*/ ,int) ; 
 int t4vf_wr_mbox (struct adapter*,struct fw_vi_enable_cmd*,int,int /*<<< orphan*/ *) ; 

int t4vf_identify_port(struct adapter *adapter, unsigned int viid,
		       unsigned int nblinks)
{
	struct fw_vi_enable_cmd cmd;

	memset(&cmd, 0, sizeof(cmd));
	cmd.op_to_viid = cpu_to_be32(FW_CMD_OP_V(FW_VI_ENABLE_CMD) |
				     FW_CMD_REQUEST_F |
				     FW_CMD_EXEC_F |
				     FW_VI_ENABLE_CMD_VIID_V(viid));
	cmd.ien_to_len16 = cpu_to_be32(FW_VI_ENABLE_CMD_LED_F |
				       FW_LEN16(cmd));
	cmd.blinkdur = cpu_to_be16(nblinks);
	return t4vf_wr_mbox(adapter, &cmd, sizeof(cmd), NULL);
}