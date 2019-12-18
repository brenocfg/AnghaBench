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
typedef  scalar_t__ u8 ;
struct vfpf_qid_tlv {scalar_t__ qid; } ;
struct TYPE_3__ {int capabilities; } ;
struct TYPE_4__ {TYPE_1__ vfdev_info; } ;
struct qed_iov_vf_mbx {int /*<<< orphan*/  req_virt; } ;
struct qed_vf_info {int /*<<< orphan*/  relative_vf_id; TYPE_2__ acquire; struct qed_iov_vf_mbx vf_mbx; } ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANNEL_TLV_QID ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ MAX_QUEUES_PER_QZONE ; 
 scalar_t__ QED_IOV_LEGACY_QID_RX ; 
 scalar_t__ QED_IOV_LEGACY_QID_TX ; 
 scalar_t__ QED_IOV_QID_INVALID ; 
 int /*<<< orphan*/  QED_MSG_IOV ; 
 int VFPF_ACQUIRE_CAP_QUEUE_QIDS ; 
 scalar_t__ qed_iov_search_list_tlvs (struct qed_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 qed_iov_vf_mbx_qid(struct qed_hwfn *p_hwfn,
			     struct qed_vf_info *p_vf, bool b_is_tx)
{
	struct qed_iov_vf_mbx *p_mbx = &p_vf->vf_mbx;
	struct vfpf_qid_tlv *p_qid_tlv;

	/* Search for the qid if the VF published its going to provide it */
	if (!(p_vf->acquire.vfdev_info.capabilities &
	      VFPF_ACQUIRE_CAP_QUEUE_QIDS)) {
		if (b_is_tx)
			return QED_IOV_LEGACY_QID_TX;
		else
			return QED_IOV_LEGACY_QID_RX;
	}

	p_qid_tlv = (struct vfpf_qid_tlv *)
		    qed_iov_search_list_tlvs(p_hwfn, p_mbx->req_virt,
					     CHANNEL_TLV_QID);
	if (!p_qid_tlv) {
		DP_VERBOSE(p_hwfn, QED_MSG_IOV,
			   "VF[%2x]: Failed to provide qid\n",
			   p_vf->relative_vf_id);

		return QED_IOV_QID_INVALID;
	}

	if (p_qid_tlv->qid >= MAX_QUEUES_PER_QZONE) {
		DP_VERBOSE(p_hwfn, QED_MSG_IOV,
			   "VF[%02x]: Provided qid out-of-bounds %02x\n",
			   p_vf->relative_vf_id, p_qid_tlv->qid);
		return QED_IOV_QID_INVALID;
	}

	return p_qid_tlv->qid;
}