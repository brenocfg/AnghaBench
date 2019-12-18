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
typedef  int u32 ;
struct tcs_request {int num_cmds; struct tcs_cmd* cmds; scalar_t__ wait_for_compl; } ;
struct tcs_cmd {int wait; int addr; int data; } ;
struct rsc_drv {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int CMD_MSGID_LEN ; 
 int CMD_MSGID_RESP_REQ ; 
 int CMD_MSGID_WRITE ; 
 int /*<<< orphan*/  RSC_DRV_CMD_ADDR ; 
 int /*<<< orphan*/  RSC_DRV_CMD_DATA ; 
 int /*<<< orphan*/  RSC_DRV_CMD_ENABLE ; 
 int /*<<< orphan*/  RSC_DRV_CMD_MSGID ; 
 int /*<<< orphan*/  RSC_DRV_CMD_WAIT_FOR_CMPL ; 
 int read_tcs_reg (struct rsc_drv*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_rpmh_send_msg (struct rsc_drv*,int,int,int,struct tcs_cmd*) ; 
 int /*<<< orphan*/  write_tcs_cmd (struct rsc_drv*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  write_tcs_reg (struct rsc_drv*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void __tcs_buffer_write(struct rsc_drv *drv, int tcs_id, int cmd_id,
			       const struct tcs_request *msg)
{
	u32 msgid, cmd_msgid;
	u32 cmd_enable = 0;
	u32 cmd_complete;
	struct tcs_cmd *cmd;
	int i, j;

	cmd_msgid = CMD_MSGID_LEN;
	cmd_msgid |= msg->wait_for_compl ? CMD_MSGID_RESP_REQ : 0;
	cmd_msgid |= CMD_MSGID_WRITE;

	cmd_complete = read_tcs_reg(drv, RSC_DRV_CMD_WAIT_FOR_CMPL, tcs_id, 0);

	for (i = 0, j = cmd_id; i < msg->num_cmds; i++, j++) {
		cmd = &msg->cmds[i];
		cmd_enable |= BIT(j);
		cmd_complete |= cmd->wait << j;
		msgid = cmd_msgid;
		msgid |= cmd->wait ? CMD_MSGID_RESP_REQ : 0;

		write_tcs_cmd(drv, RSC_DRV_CMD_MSGID, tcs_id, j, msgid);
		write_tcs_cmd(drv, RSC_DRV_CMD_ADDR, tcs_id, j, cmd->addr);
		write_tcs_cmd(drv, RSC_DRV_CMD_DATA, tcs_id, j, cmd->data);
		trace_rpmh_send_msg(drv, tcs_id, j, msgid, cmd);
	}

	write_tcs_reg(drv, RSC_DRV_CMD_WAIT_FOR_CMPL, tcs_id, cmd_complete);
	cmd_enable |= read_tcs_reg(drv, RSC_DRV_CMD_ENABLE, tcs_id, 0);
	write_tcs_reg(drv, RSC_DRV_CMD_ENABLE, tcs_id, cmd_enable);
}