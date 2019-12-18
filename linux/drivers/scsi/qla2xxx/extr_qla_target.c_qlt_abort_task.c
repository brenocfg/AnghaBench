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
struct TYPE_6__ {int /*<<< orphan*/  qla_tgt; } ;
struct scsi_qla_host {TYPE_3__ vha_tgt; int /*<<< orphan*/  vp_idx; struct qla_hw_data* hw; } ;
struct TYPE_5__ {int /*<<< orphan*/  sess_lock; TYPE_1__* tgt_ops; } ;
struct qla_hw_data {TYPE_2__ tgt; } ;
struct imm_ntfy_from_isp {int dummy; } ;
struct fc_port {int dummy; } ;
struct atio_from_isp {int dummy; } ;
struct TYPE_4__ {struct fc_port* (* find_sess_by_loop_id ) (struct scsi_qla_host*,int) ;} ;

/* Variables and functions */
 int GET_TARGET_ID (struct qla_hw_data*,struct atio_from_isp*) ; 
 int /*<<< orphan*/  QLA_TGT_SESS_WORK_ABORT ; 
 int __qlt_abort_task (struct scsi_qla_host*,struct imm_ntfy_from_isp*,struct fc_port*) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg_tgt_mgt ; 
 int qlt_sched_sess_work (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct imm_ntfy_from_isp*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct fc_port* stub1 (struct scsi_qla_host*,int) ; 

__attribute__((used)) static int qlt_abort_task(struct scsi_qla_host *vha,
	struct imm_ntfy_from_isp *iocb)
{
	struct qla_hw_data *ha = vha->hw;
	struct fc_port *sess;
	int loop_id;
	unsigned long flags;

	loop_id = GET_TARGET_ID(ha, (struct atio_from_isp *)iocb);

	spin_lock_irqsave(&ha->tgt.sess_lock, flags);
	sess = ha->tgt.tgt_ops->find_sess_by_loop_id(vha, loop_id);
	spin_unlock_irqrestore(&ha->tgt.sess_lock, flags);

	if (sess == NULL) {
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf025,
		    "qla_target(%d): task abort for unexisting "
		    "session\n", vha->vp_idx);
		return qlt_sched_sess_work(vha->vha_tgt.qla_tgt,
		    QLA_TGT_SESS_WORK_ABORT, iocb, sizeof(*iocb));
	}

	return __qlt_abort_task(vha, iocb, sess);
}