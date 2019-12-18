#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct scsi_qla_host {int /*<<< orphan*/  vp_idx; struct qla_hw_data* hw; } ;
struct TYPE_7__ {int /*<<< orphan*/  sess_lock; TYPE_2__* tgt_ops; } ;
struct qla_hw_data {int /*<<< orphan*/  base_qpair; TYPE_3__ tgt; } ;
struct fc_port {scalar_t__ deleted; } ;
struct TYPE_8__ {int /*<<< orphan*/  al_pa; int /*<<< orphan*/  area; int /*<<< orphan*/  domain; } ;
struct TYPE_5__ {TYPE_4__ s_id; int /*<<< orphan*/  parameter; } ;
struct abts_recv_from_24xx {scalar_t__ exchange_addr_to_abort; TYPE_1__ fcp_hdr_le; } ;
typedef  int /*<<< orphan*/  be_id_t ;
struct TYPE_6__ {struct fc_port* (* find_sess_by_s_id ) (struct scsi_qla_host*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ABTS_PARAM_ABORT_SEQ ; 
 scalar_t__ ATIO_EXCHANGE_ADDRESS_UNKNOWN ; 
 int /*<<< orphan*/  FCP_TMF_REJECTED ; 
 int __qlt_24xx_handle_abts (struct scsi_qla_host*,struct abts_recv_from_24xx*,struct fc_port*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le_id_to_be (TYPE_4__) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ql_dbg_tgt_mgt ; 
 int /*<<< orphan*/  qlt_24xx_send_abts_resp (int /*<<< orphan*/ ,struct abts_recv_from_24xx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct fc_port* stub1 (struct scsi_qla_host*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qlt_24xx_handle_abts(struct scsi_qla_host *vha,
	struct abts_recv_from_24xx *abts)
{
	struct qla_hw_data *ha = vha->hw;
	struct fc_port *sess;
	uint32_t tag = abts->exchange_addr_to_abort;
	be_id_t s_id;
	int rc;
	unsigned long flags;

	if (le32_to_cpu(abts->fcp_hdr_le.parameter) & ABTS_PARAM_ABORT_SEQ) {
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf053,
		    "qla_target(%d): ABTS: Abort Sequence not "
		    "supported\n", vha->vp_idx);
		qlt_24xx_send_abts_resp(ha->base_qpair, abts, FCP_TMF_REJECTED,
		    false);
		return;
	}

	if (tag == ATIO_EXCHANGE_ADDRESS_UNKNOWN) {
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf010,
		    "qla_target(%d): ABTS: Unknown Exchange "
		    "Address received\n", vha->vp_idx);
		qlt_24xx_send_abts_resp(ha->base_qpair, abts, FCP_TMF_REJECTED,
		    false);
		return;
	}

	ql_dbg(ql_dbg_tgt_mgt, vha, 0xf011,
	    "qla_target(%d): task abort (s_id=%x:%x:%x, "
	    "tag=%d, param=%x)\n", vha->vp_idx, abts->fcp_hdr_le.s_id.domain,
	    abts->fcp_hdr_le.s_id.area, abts->fcp_hdr_le.s_id.al_pa, tag,
	    le32_to_cpu(abts->fcp_hdr_le.parameter));

	s_id = le_id_to_be(abts->fcp_hdr_le.s_id);

	spin_lock_irqsave(&ha->tgt.sess_lock, flags);
	sess = ha->tgt.tgt_ops->find_sess_by_s_id(vha, s_id);
	if (!sess) {
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf012,
		    "qla_target(%d): task abort for non-existent session\n",
		    vha->vp_idx);
		spin_unlock_irqrestore(&ha->tgt.sess_lock, flags);

		qlt_24xx_send_abts_resp(ha->base_qpair, abts, FCP_TMF_REJECTED,
			    false);
		return;
	}
	spin_unlock_irqrestore(&ha->tgt.sess_lock, flags);


	if (sess->deleted) {
		qlt_24xx_send_abts_resp(ha->base_qpair, abts, FCP_TMF_REJECTED,
		    false);
		return;
	}

	rc = __qlt_24xx_handle_abts(vha, abts, sess);
	if (rc != 0) {
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf054,
		    "qla_target(%d): __qlt_24xx_handle_abts() failed: %d\n",
		    vha->vp_idx, rc);
		qlt_24xx_send_abts_resp(ha->base_qpair, abts, FCP_TMF_REJECTED,
		    false);
		return;
	}
}