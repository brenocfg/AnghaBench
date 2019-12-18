#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct se_cmd {TYPE_3__* se_tfo; TYPE_2__* se_tmr_req; int /*<<< orphan*/  tag; } ;
struct srpt_send_ioctx {struct se_cmd cmd; } ;
struct TYPE_4__ {int offset; struct srp_tsk_mgmt* buf; } ;
struct srpt_recv_ioctx {TYPE_1__ ioctx; } ;
struct srpt_rdma_ch {struct se_session* sess; } ;
struct srp_tsk_mgmt {int /*<<< orphan*/  task_tag; int /*<<< orphan*/  lun; int /*<<< orphan*/  tsk_mgmt_func; int /*<<< orphan*/  tag; } ;
struct se_session {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* queue_tm_rsp ) (struct se_cmd*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  response; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SRPT_STATE_MGMT ; 
 int /*<<< orphan*/  TARGET_SCF_ACK_KREF ; 
 int /*<<< orphan*/  TMR_FUNCTION_REJECTED ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct srpt_rdma_ch*,struct se_session*) ; 
 int /*<<< orphan*/  scsilun_to_int (int /*<<< orphan*/ *) ; 
 int srp_tmr_to_tcm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srpt_set_cmd_state (struct srpt_send_ioctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct se_cmd*) ; 
 int target_submit_tmr (struct se_cmd*,struct se_session*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct srp_tsk_mgmt*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void srpt_handle_tsk_mgmt(struct srpt_rdma_ch *ch,
				 struct srpt_recv_ioctx *recv_ioctx,
				 struct srpt_send_ioctx *send_ioctx)
{
	struct srp_tsk_mgmt *srp_tsk;
	struct se_cmd *cmd;
	struct se_session *sess = ch->sess;
	int tcm_tmr;
	int rc;

	BUG_ON(!send_ioctx);

	srp_tsk = recv_ioctx->ioctx.buf + recv_ioctx->ioctx.offset;
	cmd = &send_ioctx->cmd;

	pr_debug("recv tsk_mgmt fn %d for task_tag %lld and cmd tag %lld ch %p sess %p\n",
		 srp_tsk->tsk_mgmt_func, srp_tsk->task_tag, srp_tsk->tag, ch,
		 ch->sess);

	srpt_set_cmd_state(send_ioctx, SRPT_STATE_MGMT);
	send_ioctx->cmd.tag = srp_tsk->tag;
	tcm_tmr = srp_tmr_to_tcm(srp_tsk->tsk_mgmt_func);
	rc = target_submit_tmr(&send_ioctx->cmd, sess, NULL,
			       scsilun_to_int(&srp_tsk->lun), srp_tsk, tcm_tmr,
			       GFP_KERNEL, srp_tsk->task_tag,
			       TARGET_SCF_ACK_KREF);
	if (rc != 0) {
		send_ioctx->cmd.se_tmr_req->response = TMR_FUNCTION_REJECTED;
		cmd->se_tfo->queue_tm_rsp(cmd);
	}
	return;
}