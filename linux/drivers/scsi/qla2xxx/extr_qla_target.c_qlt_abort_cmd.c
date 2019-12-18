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
struct se_cmd {int /*<<< orphan*/  se_cmd_flags; struct se_cmd* t_state; struct qla_tgt_cmd* transport_state; int /*<<< orphan*/  tag; } ;
struct scsi_qla_host {struct qla_tgt_cmd* vp_idx; } ;
struct qla_tgt_cmd {int aborted; int /*<<< orphan*/  atio; int /*<<< orphan*/  qpair; int /*<<< orphan*/  cmd_lock; int /*<<< orphan*/  trc_flags; struct se_cmd se_cmd; struct qla_tgt* tgt; } ;
struct qla_tgt {struct scsi_qla_host* vha; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  TRC_ABORT ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,struct qla_tgt_cmd*,struct qla_tgt_cmd*,struct se_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg_tgt_mgt ; 
 int /*<<< orphan*/  qlt_send_term_exchange (int /*<<< orphan*/ ,struct qla_tgt_cmd*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int qlt_abort_cmd(struct qla_tgt_cmd *cmd)
{
	struct qla_tgt *tgt = cmd->tgt;
	struct scsi_qla_host *vha = tgt->vha;
	struct se_cmd *se_cmd = &cmd->se_cmd;
	unsigned long flags;

	ql_dbg(ql_dbg_tgt_mgt, vha, 0xf014,
	    "qla_target(%d): terminating exchange for aborted cmd=%p "
	    "(se_cmd=%p, tag=%llu)", vha->vp_idx, cmd, &cmd->se_cmd,
	    se_cmd->tag);

	spin_lock_irqsave(&cmd->cmd_lock, flags);
	if (cmd->aborted) {
		spin_unlock_irqrestore(&cmd->cmd_lock, flags);
		/*
		 * It's normal to see 2 calls in this path:
		 *  1) XFER Rdy completion + CMD_T_ABORT
		 *  2) TCM TMR - drain_state_list
		 */
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf016,
		    "multiple abort. %p transport_state %x, t_state %x, "
		    "se_cmd_flags %x\n", cmd, cmd->se_cmd.transport_state,
		    cmd->se_cmd.t_state, cmd->se_cmd.se_cmd_flags);
		return EIO;
	}
	cmd->aborted = 1;
	cmd->trc_flags |= TRC_ABORT;
	spin_unlock_irqrestore(&cmd->cmd_lock, flags);

	qlt_send_term_exchange(cmd->qpair, cmd, &cmd->atio, 0, 1);
	return 0;
}