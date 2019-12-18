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
typedef  int /*<<< orphan*/  vf_params ;
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct vfpf_start_txq_tlv {size_t tx_qid; int /*<<< orphan*/  pbl_size; int /*<<< orphan*/  pbl_addr; int /*<<< orphan*/  sb_index; int /*<<< orphan*/  hw_sb; } ;
struct qed_vf_queue {TYPE_2__* cids; int /*<<< orphan*/  fw_tx_qid; } ;
struct qed_iov_vf_mbx {TYPE_1__* req_virt; } ;
struct qed_vf_info {int /*<<< orphan*/  relative_vf_id; int /*<<< orphan*/  opaque_fid; scalar_t__ abs_vf_id; int /*<<< orphan*/  vport_id; struct qed_vf_queue* vf_queues; struct qed_iov_vf_mbx vf_mbx; } ;
struct qed_sb_info {size_t vf_qid; size_t vf_legacy; size_t qid_usage_idx; int /*<<< orphan*/  vfid; int /*<<< orphan*/  sb_idx; struct qed_sb_info* p_sb; int /*<<< orphan*/  igu_sb_id; scalar_t__ stats_id; int /*<<< orphan*/  vport_id; int /*<<< orphan*/  queue_id; } ;
struct qed_queue_start_common_params {size_t vf_qid; size_t vf_legacy; size_t qid_usage_idx; int /*<<< orphan*/  vfid; int /*<<< orphan*/  sb_idx; struct qed_queue_start_common_params* p_sb; int /*<<< orphan*/  igu_sb_id; scalar_t__ stats_id; int /*<<< orphan*/  vport_id; int /*<<< orphan*/  queue_id; } ;
struct qed_queue_cid_vf_params {size_t vf_qid; size_t vf_legacy; size_t qid_usage_idx; int /*<<< orphan*/  vfid; int /*<<< orphan*/  sb_idx; struct qed_queue_cid_vf_params* p_sb; int /*<<< orphan*/  igu_sb_id; scalar_t__ stats_id; int /*<<< orphan*/  vport_id; int /*<<< orphan*/  queue_id; } ;
struct qed_queue_cid {int /*<<< orphan*/  cid; } ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;
typedef  int /*<<< orphan*/  sb_dummy ;
typedef  int /*<<< orphan*/  params ;
struct TYPE_4__ {int b_is_tx; struct qed_queue_cid* p_cid; } ;
struct TYPE_3__ {struct vfpf_start_txq_tlv start_txq; } ;

/* Variables and functions */
 size_t PFVF_STATUS_FAILURE ; 
 size_t PFVF_STATUS_NO_RESOURCE ; 
 size_t PFVF_STATUS_SUCCESS ; 
 size_t QED_IOV_QID_INVALID ; 
 int /*<<< orphan*/  QED_IOV_VALIDATE_Q_NA ; 
 int /*<<< orphan*/  memset (struct qed_sb_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qed_eth_queue_cid_release (struct qed_hwfn*,struct qed_queue_cid*) ; 
 struct qed_queue_cid* qed_eth_queue_to_cid (struct qed_hwfn*,int /*<<< orphan*/ ,struct qed_sb_info*,int,struct qed_sb_info*) ; 
 int qed_eth_txq_start_ramrod (struct qed_hwfn*,struct qed_queue_cid*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_get_cm_pq_idx_vf (struct qed_hwfn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_iov_validate_sb (struct qed_hwfn*,struct qed_vf_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_iov_validate_txq (struct qed_hwfn*,struct qed_vf_info*,size_t,int /*<<< orphan*/ ) ; 
 size_t qed_iov_vf_mbx_qid (struct qed_hwfn*,struct qed_vf_info*,int) ; 
 int /*<<< orphan*/  qed_iov_vf_mbx_start_txq_resp (struct qed_hwfn*,struct qed_ptt*,struct qed_vf_info*,int /*<<< orphan*/ ,size_t) ; 
 size_t qed_vf_calculate_legacy (struct qed_vf_info*) ; 

__attribute__((used)) static void qed_iov_vf_mbx_start_txq(struct qed_hwfn *p_hwfn,
				     struct qed_ptt *p_ptt,
				     struct qed_vf_info *vf)
{
	struct qed_queue_start_common_params params;
	struct qed_queue_cid_vf_params vf_params;
	struct qed_iov_vf_mbx *mbx = &vf->vf_mbx;
	u8 status = PFVF_STATUS_NO_RESOURCE;
	struct vfpf_start_txq_tlv *req;
	struct qed_vf_queue *p_queue;
	struct qed_queue_cid *p_cid;
	struct qed_sb_info sb_dummy;
	u8 qid_usage_idx, vf_legacy;
	u32 cid = 0;
	int rc;
	u16 pq;

	memset(&params, 0, sizeof(params));
	req = &mbx->req_virt->start_txq;

	if (!qed_iov_validate_txq(p_hwfn, vf, req->tx_qid,
				  QED_IOV_VALIDATE_Q_NA) ||
	    !qed_iov_validate_sb(p_hwfn, vf, req->hw_sb))
		goto out;

	qid_usage_idx = qed_iov_vf_mbx_qid(p_hwfn, vf, true);
	if (qid_usage_idx == QED_IOV_QID_INVALID)
		goto out;

	p_queue = &vf->vf_queues[req->tx_qid];
	if (p_queue->cids[qid_usage_idx].p_cid)
		goto out;

	vf_legacy = qed_vf_calculate_legacy(vf);

	/* Acquire a new queue-cid */
	params.queue_id = p_queue->fw_tx_qid;
	params.vport_id = vf->vport_id;
	params.stats_id = vf->abs_vf_id + 0x10;

	/* Since IGU index is passed via sb_info, construct a dummy one */
	memset(&sb_dummy, 0, sizeof(sb_dummy));
	sb_dummy.igu_sb_id = req->hw_sb;
	params.p_sb = &sb_dummy;
	params.sb_idx = req->sb_index;

	memset(&vf_params, 0, sizeof(vf_params));
	vf_params.vfid = vf->relative_vf_id;
	vf_params.vf_qid = (u8)req->tx_qid;
	vf_params.vf_legacy = vf_legacy;
	vf_params.qid_usage_idx = qid_usage_idx;

	p_cid = qed_eth_queue_to_cid(p_hwfn, vf->opaque_fid,
				     &params, false, &vf_params);
	if (!p_cid)
		goto out;

	pq = qed_get_cm_pq_idx_vf(p_hwfn, vf->relative_vf_id);
	rc = qed_eth_txq_start_ramrod(p_hwfn, p_cid,
				      req->pbl_addr, req->pbl_size, pq);
	if (rc) {
		status = PFVF_STATUS_FAILURE;
		qed_eth_queue_cid_release(p_hwfn, p_cid);
	} else {
		status = PFVF_STATUS_SUCCESS;
		p_queue->cids[qid_usage_idx].p_cid = p_cid;
		p_queue->cids[qid_usage_idx].b_is_tx = true;
		cid = p_cid->cid;
	}

out:
	qed_iov_vf_mbx_start_txq_resp(p_hwfn, p_ptt, vf, cid, status);
}