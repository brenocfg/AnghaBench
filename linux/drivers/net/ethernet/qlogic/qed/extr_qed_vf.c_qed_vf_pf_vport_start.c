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
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct vfpf_vport_start_tlv {int tpa_mode; int /*<<< orphan*/ * sb_addr; void* only_untagged; void* max_buffers_per_cqe; void* inner_vlan_removal; void* vport_id; int /*<<< orphan*/  mtu; } ;
struct TYPE_5__ {int num_sbs; } ;
struct TYPE_6__ {TYPE_1__ resc; } ;
struct qed_vf_iov {TYPE_3__* pf2vf_reply; int /*<<< orphan*/  offset; struct qed_sb_info** sbs_info; TYPE_2__ acquire_resp; } ;
struct qed_sb_info {int /*<<< orphan*/  sb_phys; } ;
struct qed_hwfn {struct qed_vf_iov* vf_iov_info; } ;
struct TYPE_8__ {scalar_t__ status; } ;
struct pfvf_def_resp_tlv {TYPE_4__ hdr; } ;
struct channel_list_end_tlv {int dummy; } ;
typedef  enum qed_tpa_mode { ____Placeholder_qed_tpa_mode } qed_tpa_mode ;
struct TYPE_7__ {struct pfvf_def_resp_tlv default_resp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANNEL_TLV_LIST_END ; 
 int /*<<< orphan*/  CHANNEL_TLV_VPORT_START ; 
 int EINVAL ; 
 scalar_t__ PFVF_STATUS_SUCCESS ; 
 int /*<<< orphan*/  qed_add_tlv (struct qed_hwfn*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int qed_send_msg2pf (struct qed_hwfn*,scalar_t__*,int) ; 
 struct vfpf_vport_start_tlv* qed_vf_pf_prep (struct qed_hwfn*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qed_vf_pf_req_end (struct qed_hwfn*,int) ; 

int qed_vf_pf_vport_start(struct qed_hwfn *p_hwfn,
			  u8 vport_id,
			  u16 mtu,
			  u8 inner_vlan_removal,
			  enum qed_tpa_mode tpa_mode,
			  u8 max_buffers_per_cqe, u8 only_untagged)
{
	struct qed_vf_iov *p_iov = p_hwfn->vf_iov_info;
	struct vfpf_vport_start_tlv *req;
	struct pfvf_def_resp_tlv *resp;
	int rc, i;

	/* clear mailbox and prep first tlv */
	req = qed_vf_pf_prep(p_hwfn, CHANNEL_TLV_VPORT_START, sizeof(*req));

	req->mtu = mtu;
	req->vport_id = vport_id;
	req->inner_vlan_removal = inner_vlan_removal;
	req->tpa_mode = tpa_mode;
	req->max_buffers_per_cqe = max_buffers_per_cqe;
	req->only_untagged = only_untagged;

	/* status blocks */
	for (i = 0; i < p_hwfn->vf_iov_info->acquire_resp.resc.num_sbs; i++) {
		struct qed_sb_info *p_sb = p_hwfn->vf_iov_info->sbs_info[i];

		if (p_sb)
			req->sb_addr[i] = p_sb->sb_phys;
	}

	/* add list termination tlv */
	qed_add_tlv(p_hwfn, &p_iov->offset,
		    CHANNEL_TLV_LIST_END, sizeof(struct channel_list_end_tlv));

	resp = &p_iov->pf2vf_reply->default_resp;
	rc = qed_send_msg2pf(p_hwfn, &resp->hdr.status, sizeof(*resp));
	if (rc)
		goto exit;

	if (resp->hdr.status != PFVF_STATUS_SUCCESS) {
		rc = -EINVAL;
		goto exit;
	}

exit:
	qed_vf_pf_req_end(p_hwfn, rc);

	return rc;
}