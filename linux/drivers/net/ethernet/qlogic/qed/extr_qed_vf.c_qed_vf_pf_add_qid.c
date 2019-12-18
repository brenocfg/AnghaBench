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
struct vfpf_qid_tlv {int /*<<< orphan*/  qid; } ;
struct TYPE_3__ {int capabilities; } ;
struct TYPE_4__ {TYPE_1__ pfdev_info; } ;
struct qed_vf_iov {int /*<<< orphan*/  offset; TYPE_2__ acquire_resp; } ;
struct qed_queue_cid {int /*<<< orphan*/  qid_usage_idx; } ;
struct qed_hwfn {struct qed_vf_iov* vf_iov_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANNEL_TLV_QID ; 
 int PFVF_ACQUIRE_CAP_QUEUE_QIDS ; 
 struct vfpf_qid_tlv* qed_add_tlv (struct qed_hwfn*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void qed_vf_pf_add_qid(struct qed_hwfn *p_hwfn,
			      struct qed_queue_cid *p_cid)
{
	struct qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
	struct vfpf_qid_tlv *p_qid_tlv;

	/* Only add QIDs for the queue if it was negotiated with PF */
	if (!(p_iov->acquire_resp.pfdev_info.capabilities &
	      PFVF_ACQUIRE_CAP_QUEUE_QIDS))
		return;

	p_qid_tlv = qed_add_tlv(p_hwfn, &p_iov->offset,
				CHANNEL_TLV_QID, sizeof(*p_qid_tlv));
	p_qid_tlv->qid = p_cid->qid_usage_idx;
}