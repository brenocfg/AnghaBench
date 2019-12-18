#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_10__ {TYPE_1__* qla_tgt; } ;
struct scsi_qla_host {int /*<<< orphan*/  vp_idx; TYPE_2__ vha_tgt; struct qla_hw_data* hw; } ;
struct TYPE_16__ {int /*<<< orphan*/  cpuid; } ;
struct TYPE_11__ {int /*<<< orphan*/  imm_ntfy; } ;
struct qla_tgt_mgmt_cmd {int tmr_func; int flags; int /*<<< orphan*/  work; TYPE_8__ se_cmd; int /*<<< orphan*/  qpair; int /*<<< orphan*/  unpacked_lun; struct scsi_qla_host* vha; int /*<<< orphan*/  reset_count; TYPE_3__ orig_iocb; struct fc_port* sess; } ;
struct qla_qpair_hint {int /*<<< orphan*/  cpuid; int /*<<< orphan*/  qpair; } ;
struct qla_hw_data {TYPE_4__* base_qpair; } ;
struct fc_port {struct scsi_qla_host* vha; } ;
struct TYPE_13__ {int /*<<< orphan*/  s_id; } ;
struct TYPE_14__ {TYPE_5__ fcp_hdr; } ;
struct TYPE_15__ {TYPE_6__ isp24; } ;
struct atio_from_isp {TYPE_7__ u; } ;
struct TYPE_12__ {int /*<<< orphan*/  chip_reset; } ;
struct TYPE_9__ {struct qla_qpair_hint* qphints; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  QLA_TGT_ABORT_ALL 135 
#define  QLA_TGT_ABORT_TS 134 
#define  QLA_TGT_CLEAR_ACA 133 
#define  QLA_TGT_CLEAR_TS 132 
#define  QLA_TGT_LUN_RESET 131 
#define  QLA_TGT_NEXUS_LOSS 130 
#define  QLA_TGT_NEXUS_LOSS_SESS 129 
#define  QLA_TGT_TARGET_RESET 128 
 int /*<<< orphan*/  abort_cmds_for_lun (struct scsi_qla_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,int) ; 
 struct qla_tgt_mgmt_cmd* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct qla_tgt_mgmt_cmd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg_tgt_tmr ; 
 int /*<<< orphan*/  qla_tgt_mgmt_cmd_mempool ; 
 int /*<<< orphan*/  qla_tgt_wq ; 
 int /*<<< orphan*/  qlt_do_tmr_work ; 
 struct qla_qpair_hint* qlt_find_qphint (struct scsi_qla_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work_on (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qlt_issue_task_mgmt(struct fc_port *sess, u64 lun,
	int fn, void *iocb, int flags)
{
	struct scsi_qla_host *vha = sess->vha;
	struct qla_hw_data *ha = vha->hw;
	struct qla_tgt_mgmt_cmd *mcmd;
	struct atio_from_isp *a = (struct atio_from_isp *)iocb;
	struct qla_qpair_hint *h = &vha->vha_tgt.qla_tgt->qphints[0];

	mcmd = mempool_alloc(qla_tgt_mgmt_cmd_mempool, GFP_ATOMIC);
	if (!mcmd) {
		ql_dbg(ql_dbg_tgt_tmr, vha, 0x10009,
		    "qla_target(%d): Allocation of management "
		    "command failed, some commands and their data could "
		    "leak\n", vha->vp_idx);
		return -ENOMEM;
	}
	memset(mcmd, 0, sizeof(*mcmd));
	mcmd->sess = sess;

	if (iocb) {
		memcpy(&mcmd->orig_iocb.imm_ntfy, iocb,
		    sizeof(mcmd->orig_iocb.imm_ntfy));
	}
	mcmd->tmr_func = fn;
	mcmd->flags = flags;
	mcmd->reset_count = ha->base_qpair->chip_reset;
	mcmd->qpair = h->qpair;
	mcmd->vha = vha;
	mcmd->se_cmd.cpuid = h->cpuid;
	mcmd->unpacked_lun = lun;

	switch (fn) {
	case QLA_TGT_LUN_RESET:
	case QLA_TGT_CLEAR_TS:
	case QLA_TGT_ABORT_TS:
		abort_cmds_for_lun(vha, lun, a->u.isp24.fcp_hdr.s_id);
		/* fall through */
	case QLA_TGT_CLEAR_ACA:
		h = qlt_find_qphint(vha, mcmd->unpacked_lun);
		mcmd->qpair = h->qpair;
		mcmd->se_cmd.cpuid = h->cpuid;
		break;

	case QLA_TGT_TARGET_RESET:
	case QLA_TGT_NEXUS_LOSS_SESS:
	case QLA_TGT_NEXUS_LOSS:
	case QLA_TGT_ABORT_ALL:
	default:
		/* no-op */
		break;
	}

	INIT_WORK(&mcmd->work, qlt_do_tmr_work);
	queue_work_on(mcmd->se_cmd.cpuid, qla_tgt_wq,
	    &mcmd->work);

	return 0;
}