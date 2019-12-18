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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u16 ;
struct vfpf_update_coalesce {size_t rx_coal; size_t tx_coal; size_t qid; } ;
struct qed_vf_queue {TYPE_2__* cids; int /*<<< orphan*/  fw_rx_qid; } ;
struct qed_iov_vf_mbx {TYPE_1__* req_virt; } ;
struct qed_vf_info {size_t rx_coal; size_t tx_coal; int /*<<< orphan*/  abs_vf_id; struct qed_vf_queue* vf_queues; struct qed_iov_vf_mbx vf_mbx; } ;
struct qed_queue_cid {int dummy; } ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;
struct pfvf_def_resp_tlv {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  p_cid; int /*<<< orphan*/  b_is_tx; } ;
struct TYPE_3__ {struct vfpf_update_coalesce update_coalesce; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANNEL_TLV_COALESCE_UPDATE ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int MAX_QUEUES_PER_QZONE ; 
 int /*<<< orphan*/  PFVF_STATUS_FAILURE ; 
 int /*<<< orphan*/  PFVF_STATUS_SUCCESS ; 
 int /*<<< orphan*/  QED_IOV_VALIDATE_Q_ENABLE ; 
 int /*<<< orphan*/  QED_MSG_IOV ; 
 struct qed_queue_cid* qed_iov_get_vf_rx_queue_cid (struct qed_vf_queue*) ; 
 int /*<<< orphan*/  qed_iov_prepare_resp (struct qed_hwfn*,struct qed_ptt*,struct qed_vf_info*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_iov_validate_rxq (struct qed_hwfn*,struct qed_vf_info*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_iov_validate_txq (struct qed_hwfn*,struct qed_vf_info*,size_t,int /*<<< orphan*/ ) ; 
 int qed_set_rxq_coalesce (struct qed_hwfn*,struct qed_ptt*,size_t,struct qed_queue_cid*) ; 
 int qed_set_txq_coalesce (struct qed_hwfn*,struct qed_ptt*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qed_iov_vf_pf_set_coalesce(struct qed_hwfn *p_hwfn,
				       struct qed_ptt *p_ptt,
				       struct qed_vf_info *vf)
{
	struct qed_iov_vf_mbx *mbx = &vf->vf_mbx;
	struct vfpf_update_coalesce *req;
	u8 status = PFVF_STATUS_FAILURE;
	struct qed_queue_cid *p_cid;
	u16 rx_coal, tx_coal;
	int rc = 0, i;
	u16 qid;

	req = &mbx->req_virt->update_coalesce;

	rx_coal = req->rx_coal;
	tx_coal = req->tx_coal;
	qid = req->qid;

	if (!qed_iov_validate_rxq(p_hwfn, vf, qid,
				  QED_IOV_VALIDATE_Q_ENABLE) && rx_coal) {
		DP_VERBOSE(p_hwfn, QED_MSG_IOV,
			   "VF[%d]: Invalid Rx queue_id = %d\n",
			   vf->abs_vf_id, qid);
		goto out;
	}

	if (!qed_iov_validate_txq(p_hwfn, vf, qid,
				  QED_IOV_VALIDATE_Q_ENABLE) && tx_coal) {
		DP_VERBOSE(p_hwfn, QED_MSG_IOV,
			   "VF[%d]: Invalid Tx queue_id = %d\n",
			   vf->abs_vf_id, qid);
		goto out;
	}

	DP_VERBOSE(p_hwfn,
		   QED_MSG_IOV,
		   "VF[%d]: Setting coalesce for VF rx_coal = %d, tx_coal = %d at queue = %d\n",
		   vf->abs_vf_id, rx_coal, tx_coal, qid);

	if (rx_coal) {
		p_cid = qed_iov_get_vf_rx_queue_cid(&vf->vf_queues[qid]);

		rc = qed_set_rxq_coalesce(p_hwfn, p_ptt, rx_coal, p_cid);
		if (rc) {
			DP_VERBOSE(p_hwfn,
				   QED_MSG_IOV,
				   "VF[%d]: Unable to set rx queue = %d coalesce\n",
				   vf->abs_vf_id, vf->vf_queues[qid].fw_rx_qid);
			goto out;
		}
		vf->rx_coal = rx_coal;
	}

	if (tx_coal) {
		struct qed_vf_queue *p_queue = &vf->vf_queues[qid];

		for (i = 0; i < MAX_QUEUES_PER_QZONE; i++) {
			if (!p_queue->cids[i].p_cid)
				continue;

			if (!p_queue->cids[i].b_is_tx)
				continue;

			rc = qed_set_txq_coalesce(p_hwfn, p_ptt, tx_coal,
						  p_queue->cids[i].p_cid);

			if (rc) {
				DP_VERBOSE(p_hwfn,
					   QED_MSG_IOV,
					   "VF[%d]: Unable to set tx queue coalesce\n",
					   vf->abs_vf_id);
				goto out;
			}
		}
		vf->tx_coal = tx_coal;
	}

	status = PFVF_STATUS_SUCCESS;
out:
	qed_iov_prepare_resp(p_hwfn, p_ptt, vf, CHANNEL_TLV_COALESCE_UPDATE,
			     sizeof(struct pfvf_def_resp_tlv), status);
}