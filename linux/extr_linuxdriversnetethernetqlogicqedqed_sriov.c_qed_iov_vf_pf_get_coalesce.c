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
struct vfpf_read_coal_req_tlv {size_t qid; scalar_t__ is_rx; } ;
struct qed_vf_queue {TYPE_2__* cids; } ;
struct qed_iov_vf_mbx {int /*<<< orphan*/ * offset; TYPE_1__* req_virt; scalar_t__ reply_virt; } ;
struct qed_vf_info {struct qed_vf_queue* vf_queues; int /*<<< orphan*/  abs_vf_id; struct qed_iov_vf_mbx vf_mbx; } ;
struct qed_queue_cid {int dummy; } ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;
struct pfvf_read_coal_resp_tlv {size_t coal; } ;
struct channel_list_end_tlv {int dummy; } ;
struct TYPE_4__ {struct qed_queue_cid* p_cid; int /*<<< orphan*/  b_is_tx; } ;
struct TYPE_3__ {struct vfpf_read_coal_req_tlv read_coal_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANNEL_TLV_COALESCE_READ ; 
 int /*<<< orphan*/  CHANNEL_TLV_LIST_END ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,size_t) ; 
 size_t MAX_QUEUES_PER_QZONE ; 
 int /*<<< orphan*/  PFVF_STATUS_FAILURE ; 
 int /*<<< orphan*/  PFVF_STATUS_SUCCESS ; 
 int /*<<< orphan*/  QED_IOV_VALIDATE_Q_ENABLE ; 
 int /*<<< orphan*/  QED_MSG_IOV ; 
 struct pfvf_read_coal_resp_tlv* qed_add_tlv (struct qed_hwfn*,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 
 int qed_get_rxq_coalesce (struct qed_hwfn*,struct qed_ptt*,struct qed_queue_cid*,size_t*) ; 
 int qed_get_txq_coalesce (struct qed_hwfn*,struct qed_ptt*,struct qed_queue_cid*,size_t*) ; 
 struct qed_queue_cid* qed_iov_get_vf_rx_queue_cid (struct qed_vf_queue*) ; 
 int /*<<< orphan*/  qed_iov_send_response (struct qed_hwfn*,struct qed_ptt*,struct qed_vf_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_iov_validate_rxq (struct qed_hwfn*,struct qed_vf_info*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_iov_validate_txq (struct qed_hwfn*,struct qed_vf_info*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qed_iov_vf_pf_get_coalesce(struct qed_hwfn *p_hwfn,
				       struct qed_ptt *p_ptt,
				       struct qed_vf_info *p_vf)
{
	struct qed_iov_vf_mbx *mbx = &p_vf->vf_mbx;
	struct pfvf_read_coal_resp_tlv *p_resp;
	struct vfpf_read_coal_req_tlv *req;
	u8 status = PFVF_STATUS_FAILURE;
	struct qed_vf_queue *p_queue;
	struct qed_queue_cid *p_cid;
	u16 coal = 0, qid, i;
	bool b_is_rx;
	int rc = 0;

	mbx->offset = (u8 *)mbx->reply_virt;
	req = &mbx->req_virt->read_coal_req;

	qid = req->qid;
	b_is_rx = req->is_rx ? true : false;

	if (b_is_rx) {
		if (!qed_iov_validate_rxq(p_hwfn, p_vf, qid,
					  QED_IOV_VALIDATE_Q_ENABLE)) {
			DP_VERBOSE(p_hwfn, QED_MSG_IOV,
				   "VF[%d]: Invalid Rx queue_id = %d\n",
				   p_vf->abs_vf_id, qid);
			goto send_resp;
		}

		p_cid = qed_iov_get_vf_rx_queue_cid(&p_vf->vf_queues[qid]);
		rc = qed_get_rxq_coalesce(p_hwfn, p_ptt, p_cid, &coal);
		if (rc)
			goto send_resp;
	} else {
		if (!qed_iov_validate_txq(p_hwfn, p_vf, qid,
					  QED_IOV_VALIDATE_Q_ENABLE)) {
			DP_VERBOSE(p_hwfn, QED_MSG_IOV,
				   "VF[%d]: Invalid Tx queue_id = %d\n",
				   p_vf->abs_vf_id, qid);
			goto send_resp;
		}
		for (i = 0; i < MAX_QUEUES_PER_QZONE; i++) {
			p_queue = &p_vf->vf_queues[qid];
			if ((!p_queue->cids[i].p_cid) ||
			    (!p_queue->cids[i].b_is_tx))
				continue;

			p_cid = p_queue->cids[i].p_cid;

			rc = qed_get_txq_coalesce(p_hwfn, p_ptt, p_cid, &coal);
			if (rc)
				goto send_resp;
			break;
		}
	}

	status = PFVF_STATUS_SUCCESS;

send_resp:
	p_resp = qed_add_tlv(p_hwfn, &mbx->offset, CHANNEL_TLV_COALESCE_READ,
			     sizeof(*p_resp));
	p_resp->coal = coal;

	qed_add_tlv(p_hwfn, &mbx->offset, CHANNEL_TLV_LIST_END,
		    sizeof(struct channel_list_end_tlv));

	qed_iov_send_response(p_hwfn, p_ptt, p_vf, sizeof(*p_resp), status);
}