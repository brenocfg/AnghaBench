#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct se_tmr_req {int dummy; } ;
struct iscsi_tm_rsp {int /*<<< orphan*/  response; void* max_cmdsn; void* exp_cmdsn; void* statsn; int /*<<< orphan*/  itt; int /*<<< orphan*/  flags; int /*<<< orphan*/  opcode; } ;
struct iscsi_conn {int /*<<< orphan*/  cid; TYPE_2__* sess; int /*<<< orphan*/  stat_sn; } ;
struct TYPE_3__ {struct se_tmr_req* se_tmr_req; } ;
struct iscsi_cmd {scalar_t__ stat_sn; int /*<<< orphan*/  init_task_tag; TYPE_1__ se_cmd; } ;
struct TYPE_4__ {int /*<<< orphan*/  max_cmd_sn; scalar_t__ exp_cmd_sn; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_FLAG_CMD_FINAL ; 
 int /*<<< orphan*/  ISCSI_OP_SCSI_TMFUNC_RSP ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 void* cpu_to_be32 (scalar_t__) ; 
 int /*<<< orphan*/  iscsit_convert_tcm_tmr_rsp (struct se_tmr_req*) ; 
 int /*<<< orphan*/  iscsit_increment_maxcmdsn (struct iscsi_cmd*,TYPE_2__*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
iscsit_build_task_mgt_rsp(struct iscsi_cmd *cmd, struct iscsi_conn *conn,
			  struct iscsi_tm_rsp *hdr)
{
	struct se_tmr_req *se_tmr = cmd->se_cmd.se_tmr_req;

	hdr->opcode		= ISCSI_OP_SCSI_TMFUNC_RSP;
	hdr->flags		= ISCSI_FLAG_CMD_FINAL;
	hdr->response		= iscsit_convert_tcm_tmr_rsp(se_tmr);
	hdr->itt		= cmd->init_task_tag;
	cmd->stat_sn		= conn->stat_sn++;
	hdr->statsn		= cpu_to_be32(cmd->stat_sn);

	iscsit_increment_maxcmdsn(cmd, conn->sess);
	hdr->exp_cmdsn		= cpu_to_be32(conn->sess->exp_cmd_sn);
	hdr->max_cmdsn		= cpu_to_be32((u32) atomic_read(&conn->sess->max_cmd_sn));

	pr_debug("Built Task Management Response ITT: 0x%08x,"
		" StatSN: 0x%08x, Response: 0x%02x, CID: %hu\n",
		cmd->init_task_tag, cmd->stat_sn, hdr->response, conn->cid);
}