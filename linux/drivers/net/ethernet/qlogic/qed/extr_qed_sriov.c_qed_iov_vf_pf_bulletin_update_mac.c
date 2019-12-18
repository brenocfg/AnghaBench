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
typedef  int /*<<< orphan*/  u8 ;
struct vfpf_bulletin_update_mac_tlv {int /*<<< orphan*/  mac; } ;
struct TYPE_4__ {int /*<<< orphan*/  is_trusted_configured; } ;
struct qed_iov_vf_mbx {TYPE_2__* req_virt; } ;
struct TYPE_6__ {struct qed_bulletin_content* p_virt; } ;
struct qed_vf_info {int /*<<< orphan*/  abs_vf_id; TYPE_1__ p_vf_info; struct qed_iov_vf_mbx vf_mbx; TYPE_3__ bulletin; } ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;
struct qed_bulletin_content {int /*<<< orphan*/  mac; } ;
struct pfvf_def_resp_tlv {int dummy; } ;
struct TYPE_5__ {struct vfpf_bulletin_update_mac_tlv bulletin_update_mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANNEL_TLV_BULLETIN_UPDATE_MAC ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int EINVAL ; 
 int /*<<< orphan*/  PFVF_STATUS_NOT_SUPPORTED ; 
 int /*<<< orphan*/  PFVF_STATUS_SUCCESS ; 
 int /*<<< orphan*/  QED_MSG_IOV ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_iov_prepare_resp (struct qed_hwfn*,struct qed_ptt*,struct qed_vf_info*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qed_iov_vf_pf_bulletin_update_mac(struct qed_hwfn *p_hwfn,
				  struct qed_ptt *p_ptt,
				  struct qed_vf_info *p_vf)
{
	struct qed_bulletin_content *p_bulletin = p_vf->bulletin.p_virt;
	struct qed_iov_vf_mbx *mbx = &p_vf->vf_mbx;
	struct vfpf_bulletin_update_mac_tlv *p_req;
	u8 status = PFVF_STATUS_SUCCESS;
	int rc = 0;

	if (!p_vf->p_vf_info.is_trusted_configured) {
		DP_VERBOSE(p_hwfn,
			   QED_MSG_IOV,
			   "Blocking bulletin update request from untrusted VF[%d]\n",
			   p_vf->abs_vf_id);
		status = PFVF_STATUS_NOT_SUPPORTED;
		rc = -EINVAL;
		goto send_status;
	}

	p_req = &mbx->req_virt->bulletin_update_mac;
	ether_addr_copy(p_bulletin->mac, p_req->mac);
	DP_VERBOSE(p_hwfn, QED_MSG_IOV,
		   "Updated bulletin of VF[%d] with requested MAC[%pM]\n",
		   p_vf->abs_vf_id, p_req->mac);

send_status:
	qed_iov_prepare_resp(p_hwfn, p_ptt, p_vf,
			     CHANNEL_TLV_BULLETIN_UPDATE_MAC,
			     sizeof(struct pfvf_def_resp_tlv), status);
	return rc;
}