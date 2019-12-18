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
struct se_cmd {int /*<<< orphan*/  pi_err; } ;
struct isert_device {int /*<<< orphan*/  ib_device; } ;
struct isert_conn {int /*<<< orphan*/  conn; struct isert_device* device; } ;
struct TYPE_6__ {TYPE_2__* reg; } ;
struct isert_cmd {TYPE_3__ rw; struct iscsi_cmd* iscsi_cmd; } ;
struct iser_tx_desc {int dummy; } ;
struct iscsi_cmd {int /*<<< orphan*/  istate_lock; int /*<<< orphan*/  i_state; int /*<<< orphan*/  cmd_flags; scalar_t__ write_data_done; struct se_cmd se_cmd; } ;
struct ib_wc {scalar_t__ status; int /*<<< orphan*/  wr_cqe; TYPE_1__* qp; } ;
struct ib_cq {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  mr; } ;
struct TYPE_4__ {struct isert_conn* qp_context; } ;

/* Variables and functions */
 scalar_t__ IB_WC_SUCCESS ; 
 scalar_t__ IB_WC_WR_FLUSH_ERR ; 
 int /*<<< orphan*/  ICF_GOT_LAST_DATAOUT ; 
 int /*<<< orphan*/  ISTATE_RECEIVED_LAST_DATAOUT ; 
 struct iser_tx_desc* cqe_to_tx_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsit_cause_connection_reinstatement (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsit_stop_dataout_timer (struct iscsi_cmd*) ; 
 int isert_check_pi_status (struct se_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isert_completion_put (struct iser_tx_desc*,struct isert_cmd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  isert_dbg (char*,struct isert_cmd*) ; 
 int /*<<< orphan*/  isert_print_wc (struct ib_wc*,char*) ; 
 scalar_t__ isert_prot_cmd (struct isert_conn*,struct se_cmd*) ; 
 int /*<<< orphan*/  isert_rdma_rw_ctx_destroy (struct isert_cmd*,struct isert_conn*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  target_execute_cmd (struct se_cmd*) ; 
 int /*<<< orphan*/  transport_generic_request_failure (struct se_cmd*,int /*<<< orphan*/ ) ; 
 struct isert_cmd* tx_desc_to_cmd (struct iser_tx_desc*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
isert_rdma_read_done(struct ib_cq *cq, struct ib_wc *wc)
{
	struct isert_conn *isert_conn = wc->qp->qp_context;
	struct isert_device *device = isert_conn->device;
	struct iser_tx_desc *desc = cqe_to_tx_desc(wc->wr_cqe);
	struct isert_cmd *isert_cmd = tx_desc_to_cmd(desc);
	struct iscsi_cmd *cmd = isert_cmd->iscsi_cmd;
	struct se_cmd *se_cmd = &cmd->se_cmd;
	int ret = 0;

	if (unlikely(wc->status != IB_WC_SUCCESS)) {
		isert_print_wc(wc, "rdma read");
		if (wc->status != IB_WC_WR_FLUSH_ERR)
			iscsit_cause_connection_reinstatement(isert_conn->conn, 0);
		isert_completion_put(desc, isert_cmd, device->ib_device, true);
		return;
	}

	isert_dbg("Cmd %p\n", isert_cmd);

	iscsit_stop_dataout_timer(cmd);

	if (isert_prot_cmd(isert_conn, se_cmd))
		ret = isert_check_pi_status(se_cmd, isert_cmd->rw.reg->mr);
	isert_rdma_rw_ctx_destroy(isert_cmd, isert_conn);
	cmd->write_data_done = 0;

	isert_dbg("Cmd: %p RDMA_READ comp calling execute_cmd\n", isert_cmd);
	spin_lock_bh(&cmd->istate_lock);
	cmd->cmd_flags |= ICF_GOT_LAST_DATAOUT;
	cmd->i_state = ISTATE_RECEIVED_LAST_DATAOUT;
	spin_unlock_bh(&cmd->istate_lock);

	/*
	 * transport_generic_request_failure() will drop the extra
	 * se_cmd->cmd_kref reference after T10-PI error, and handle
	 * any non-zero ->queue_status() callback error retries.
	 */
	if (ret)
		transport_generic_request_failure(se_cmd, se_cmd->pi_err);
	else
		target_execute_cmd(se_cmd);
}