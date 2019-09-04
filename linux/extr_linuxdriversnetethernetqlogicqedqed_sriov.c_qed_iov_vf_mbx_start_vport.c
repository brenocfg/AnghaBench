#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct vfpf_vport_start_tlv {int /*<<< orphan*/  max_buffers_per_cqe; int /*<<< orphan*/  inner_vlan_removal; int /*<<< orphan*/  tpa_mode; int /*<<< orphan*/  only_untagged; int /*<<< orphan*/  mtu; int /*<<< orphan*/ * sb_addr; } ;
struct TYPE_10__ {int /*<<< orphan*/  is_trusted_configured; } ;
struct TYPE_9__ {TYPE_3__* p_virt; } ;
struct TYPE_7__ {int /*<<< orphan*/  inner_vlan_removal; } ;
struct qed_iov_vf_mbx {TYPE_1__* req_virt; } ;
struct qed_vf_info {int num_sbs; int /*<<< orphan*/  req_spoofchk_val; int /*<<< orphan*/  vport_instance; TYPE_5__ p_vf_info; int /*<<< orphan*/  mtu; int /*<<< orphan*/  vport_id; int /*<<< orphan*/  opaque_fid; int /*<<< orphan*/  concrete_fid; TYPE_4__ bulletin; TYPE_2__ shadow_config; int /*<<< orphan*/  abs_vf_id; int /*<<< orphan*/ * igu_sbs; scalar_t__ relative_vf_id; int /*<<< orphan*/  state; struct qed_iov_vf_mbx vf_mbx; } ;
struct qed_sp_vport_start_params {int tx_switching; int drop_ttl0; int check_mac; int /*<<< orphan*/  mtu; int /*<<< orphan*/  max_buffers_per_cqe; int /*<<< orphan*/  vport_id; int /*<<< orphan*/  opaque_fid; int /*<<< orphan*/  concrete_fid; int /*<<< orphan*/  only_untagged; int /*<<< orphan*/  remove_inner_vlan; int /*<<< orphan*/  tpa_mode; int /*<<< orphan*/  member_0; } ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int /*<<< orphan*/  cdev; } ;
struct pfvf_def_resp_tlv {int dummy; } ;
struct TYPE_8__ {int valid_bitmap; int /*<<< orphan*/  default_only_untagged; } ;
struct TYPE_6__ {struct vfpf_vport_start_tlv start_vport; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHANNEL_TLV_VPORT_START ; 
 int /*<<< orphan*/  DP_ERR (struct qed_hwfn*,char*,int) ; 
 int /*<<< orphan*/  DP_NOTICE (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,scalar_t__,int) ; 
 int /*<<< orphan*/  PFVF_STATUS_FAILURE ; 
 int /*<<< orphan*/  PFVF_STATUS_SUCCESS ; 
 int /*<<< orphan*/  QED_MSG_IOV ; 
 int VFPF_BULLETIN_UNTAGGED_DEFAULT ; 
 int /*<<< orphan*/  VFPF_BULLETIN_UNTAGGED_DEFAULT_FORCED ; 
 int /*<<< orphan*/  VF_ENABLED ; 
 int /*<<< orphan*/  __qed_iov_spoofchk_set (struct qed_hwfn*,struct qed_vf_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_int_cau_conf_sb (struct qed_hwfn*,struct qed_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qed_iov_configure_vport_forced (struct qed_hwfn*,struct qed_vf_info*,int) ; 
 int /*<<< orphan*/  qed_iov_enable_vf_traffic (struct qed_hwfn*,struct qed_ptt*,struct qed_vf_info*) ; 
 struct qed_vf_info* qed_iov_get_vf_info (struct qed_hwfn*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qed_iov_prepare_resp (struct qed_hwfn*,struct qed_ptt*,struct qed_vf_info*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int qed_sp_eth_vport_start (struct qed_hwfn*,struct qed_sp_vport_start_params*) ; 

__attribute__((used)) static void qed_iov_vf_mbx_start_vport(struct qed_hwfn *p_hwfn,
				       struct qed_ptt *p_ptt,
				       struct qed_vf_info *vf)
{
	struct qed_sp_vport_start_params params = { 0 };
	struct qed_iov_vf_mbx *mbx = &vf->vf_mbx;
	struct vfpf_vport_start_tlv *start;
	u8 status = PFVF_STATUS_SUCCESS;
	struct qed_vf_info *vf_info;
	u64 *p_bitmap;
	int sb_id;
	int rc;

	vf_info = qed_iov_get_vf_info(p_hwfn, (u16) vf->relative_vf_id, true);
	if (!vf_info) {
		DP_NOTICE(p_hwfn->cdev,
			  "Failed to get VF info, invalid vfid [%d]\n",
			  vf->relative_vf_id);
		return;
	}

	vf->state = VF_ENABLED;
	start = &mbx->req_virt->start_vport;

	qed_iov_enable_vf_traffic(p_hwfn, p_ptt, vf);

	/* Initialize Status block in CAU */
	for (sb_id = 0; sb_id < vf->num_sbs; sb_id++) {
		if (!start->sb_addr[sb_id]) {
			DP_VERBOSE(p_hwfn, QED_MSG_IOV,
				   "VF[%d] did not fill the address of SB %d\n",
				   vf->relative_vf_id, sb_id);
			break;
		}

		qed_int_cau_conf_sb(p_hwfn, p_ptt,
				    start->sb_addr[sb_id],
				    vf->igu_sbs[sb_id], vf->abs_vf_id, 1);
	}

	vf->mtu = start->mtu;
	vf->shadow_config.inner_vlan_removal = start->inner_vlan_removal;

	/* Take into consideration configuration forced by hypervisor;
	 * If none is configured, use the supplied VF values [for old
	 * vfs that would still be fine, since they passed '0' as padding].
	 */
	p_bitmap = &vf_info->bulletin.p_virt->valid_bitmap;
	if (!(*p_bitmap & BIT(VFPF_BULLETIN_UNTAGGED_DEFAULT_FORCED))) {
		u8 vf_req = start->only_untagged;

		vf_info->bulletin.p_virt->default_only_untagged = vf_req;
		*p_bitmap |= 1 << VFPF_BULLETIN_UNTAGGED_DEFAULT;
	}

	params.tpa_mode = start->tpa_mode;
	params.remove_inner_vlan = start->inner_vlan_removal;
	params.tx_switching = true;

	params.only_untagged = vf_info->bulletin.p_virt->default_only_untagged;
	params.drop_ttl0 = false;
	params.concrete_fid = vf->concrete_fid;
	params.opaque_fid = vf->opaque_fid;
	params.vport_id = vf->vport_id;
	params.max_buffers_per_cqe = start->max_buffers_per_cqe;
	params.mtu = vf->mtu;

	/* Non trusted VFs should enable control frame filtering */
	params.check_mac = !vf->p_vf_info.is_trusted_configured;

	rc = qed_sp_eth_vport_start(p_hwfn, &params);
	if (rc) {
		DP_ERR(p_hwfn,
		       "qed_iov_vf_mbx_start_vport returned error %d\n", rc);
		status = PFVF_STATUS_FAILURE;
	} else {
		vf->vport_instance++;

		/* Force configuration if needed on the newly opened vport */
		qed_iov_configure_vport_forced(p_hwfn, vf, *p_bitmap);

		__qed_iov_spoofchk_set(p_hwfn, vf, vf->req_spoofchk_val);
	}
	qed_iov_prepare_resp(p_hwfn, p_ptt, vf, CHANNEL_TLV_VPORT_START,
			     sizeof(struct pfvf_def_resp_tlv), status);
}