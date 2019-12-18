#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  online; } ;
struct scsi_qla_host {struct qla_hw_data* hw; TYPE_1__ flags; } ;
struct TYPE_17__ {scalar_t__ entry_type; } ;
struct TYPE_18__ {TYPE_4__ raw; } ;
struct TYPE_19__ {TYPE_5__ u; } ;
struct TYPE_15__ {int status_subcode; } ;
struct TYPE_16__ {TYPE_2__ isp24; } ;
struct TYPE_12__ {TYPE_3__ u; } ;
struct TYPE_20__ {TYPE_6__ atio; TYPE_10__ imm_ntfy; } ;
struct qla_tgt_mgmt_cmd {int /*<<< orphan*/  fc_tm_rsp; TYPE_7__ orig_iocb; TYPE_11__* sess; int /*<<< orphan*/  flags; int /*<<< orphan*/  reset_count; struct qla_qpair* qpair; } ;
struct qla_qpair {int /*<<< orphan*/  qp_lock_ptr; int /*<<< orphan*/  chip_reset; } ;
struct TYPE_22__ {TYPE_8__* tgt_ops; } ;
struct qla_hw_data {TYPE_9__ tgt; int /*<<< orphan*/  base_qpair; } ;
struct TYPE_21__ {int /*<<< orphan*/  (* free_mcmd ) (struct qla_tgt_mgmt_cmd*) ;} ;
struct TYPE_13__ {struct qla_tgt_mgmt_cmd* port_name; struct scsi_qla_host* vha; } ;

/* Variables and functions */
 scalar_t__ ABTS_RECV_24XX ; 
#define  ELS_LOGO 130 
#define  ELS_PRLO 129 
#define  ELS_TPRLO 128 
 int /*<<< orphan*/  QLA24XX_MGMT_SEND_NACK ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,struct qla_tgt_mgmt_cmd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ql_dbg_async ; 
 int /*<<< orphan*/  ql_dbg_disc ; 
 int /*<<< orphan*/  ql_dbg_tgt_mgt ; 
 int /*<<< orphan*/  qla2x00_reset_active (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  qlt_24xx_send_task_mgmt_ctio (struct qla_qpair*,struct qla_tgt_mgmt_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlt_build_abts_resp_iocb (struct qla_tgt_mgmt_cmd*) ; 
 int /*<<< orphan*/  qlt_schedule_sess_for_deletion (TYPE_11__*) ; 
 int /*<<< orphan*/  qlt_send_notify_ack (int /*<<< orphan*/ ,TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct qla_tgt_mgmt_cmd*) ; 
 int /*<<< orphan*/  stub2 (struct qla_tgt_mgmt_cmd*) ; 

void qlt_xmit_tm_rsp(struct qla_tgt_mgmt_cmd *mcmd)
{
	struct scsi_qla_host *vha = mcmd->sess->vha;
	struct qla_hw_data *ha = vha->hw;
	unsigned long flags;
	struct qla_qpair *qpair = mcmd->qpair;
	bool free_mcmd = true;

	ql_dbg(ql_dbg_tgt_mgt, vha, 0xf013,
	    "TM response mcmd (%p) status %#x state %#x",
	    mcmd, mcmd->fc_tm_rsp, mcmd->flags);

	spin_lock_irqsave(qpair->qp_lock_ptr, flags);

	if (!vha->flags.online || mcmd->reset_count != qpair->chip_reset) {
		/*
		 * Either the port is not online or this request was from
		 * previous life, just abort the processing.
		 */
		ql_dbg(ql_dbg_async, vha, 0xe100,
			"RESET-TMR online/active/old-count/new-count = %d/%d/%d/%d.\n",
			vha->flags.online, qla2x00_reset_active(vha),
			mcmd->reset_count, qpair->chip_reset);
		ha->tgt.tgt_ops->free_mcmd(mcmd);
		spin_unlock_irqrestore(qpair->qp_lock_ptr, flags);
		return;
	}

	if (mcmd->flags == QLA24XX_MGMT_SEND_NACK) {
		switch (mcmd->orig_iocb.imm_ntfy.u.isp24.status_subcode) {
		case ELS_LOGO:
		case ELS_PRLO:
		case ELS_TPRLO:
			ql_dbg(ql_dbg_disc, vha, 0x2106,
			    "TM response logo %8phC status %#x state %#x",
			    mcmd->sess->port_name, mcmd->fc_tm_rsp,
			    mcmd->flags);
			qlt_schedule_sess_for_deletion(mcmd->sess);
			break;
		default:
			qlt_send_notify_ack(vha->hw->base_qpair,
			    &mcmd->orig_iocb.imm_ntfy, 0, 0, 0, 0, 0, 0);
			break;
		}
	} else {
		if (mcmd->orig_iocb.atio.u.raw.entry_type == ABTS_RECV_24XX) {
			qlt_build_abts_resp_iocb(mcmd);
			free_mcmd = false;
		} else
			qlt_24xx_send_task_mgmt_ctio(qpair, mcmd,
			    mcmd->fc_tm_rsp);
	}
	/*
	 * Make the callback for ->free_mcmd() to queue_work() and invoke
	 * target_put_sess_cmd() to drop cmd_kref to 1.  The final
	 * target_put_sess_cmd() call will be made from TFO->check_stop_free()
	 * -> tcm_qla2xxx_check_stop_free() to release the TMR associated se_cmd
	 * descriptor after TFO->queue_tm_rsp() -> tcm_qla2xxx_queue_tm_rsp() ->
	 * qlt_xmit_tm_rsp() returns here..
	 */
	if (free_mcmd)
		ha->tgt.tgt_ops->free_mcmd(mcmd);

	spin_unlock_irqrestore(qpair->qp_lock_ptr, flags);
}