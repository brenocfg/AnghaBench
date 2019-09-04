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
typedef  union vfpf_tlvs {int dummy; } vfpf_tlvs ;
typedef  union pfvf_tlvs {int dummy; } pfvf_tlvs ;
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_7__ {int size; struct qed_bulletin_content* p_virt; void* phys; } ;
struct TYPE_6__ {void* reply_phys; union pfvf_tlvs* reply_virt; void* req_phys; union vfpf_tlvs* req_virt; } ;
struct qed_vf_info {int b_init; size_t relative_vf_id; int abs_vf_id; int opaque_fid; size_t vport_id; int /*<<< orphan*/  num_vlan_filters; int /*<<< orphan*/  num_mac_filters; int /*<<< orphan*/  concrete_fid; TYPE_3__ bulletin; int /*<<< orphan*/  state; TYPE_2__ vf_mbx; } ;
struct qed_pf_iov {struct qed_vf_info* vfs_array; void* bulletins_phys; struct qed_bulletin_content* p_bulletins; void* mbx_reply_phys_addr; union pfvf_tlvs* mbx_reply_virt_addr; void* mbx_msg_phys_addr; union vfpf_tlvs* mbx_msg_virt_addr; } ;
struct TYPE_8__ {int opaque_fid; } ;
struct qed_hwfn {TYPE_4__ hw_info; struct qed_pf_iov* pf_iov_info; TYPE_1__* cdev; } ;
struct qed_hw_sriov_info {size_t total_vfs; int first_vf_in_pf; } ;
struct qed_bulletin_content {int dummy; } ;
typedef  void* dma_addr_t ;
struct TYPE_5__ {struct qed_hw_sriov_info* p_iov_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct qed_hwfn*,char*) ; 
 int /*<<< orphan*/  QED_ETH_VF_NUM_MAC_FILTERS ; 
 int /*<<< orphan*/  QED_ETH_VF_NUM_VLAN_FILTERS ; 
 int /*<<< orphan*/  VF_STOPPED ; 
 int /*<<< orphan*/  memset (struct qed_vf_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qed_vfid_to_concrete (struct qed_hwfn*,int) ; 

__attribute__((used)) static void qed_iov_setup_vfdb(struct qed_hwfn *p_hwfn)
{
	struct qed_hw_sriov_info *p_iov = p_hwfn->cdev->p_iov_info;
	struct qed_pf_iov *p_iov_info = p_hwfn->pf_iov_info;
	struct qed_bulletin_content *p_bulletin_virt;
	dma_addr_t req_p, rply_p, bulletin_p;
	union pfvf_tlvs *p_reply_virt_addr;
	union vfpf_tlvs *p_req_virt_addr;
	u8 idx = 0;

	memset(p_iov_info->vfs_array, 0, sizeof(p_iov_info->vfs_array));

	p_req_virt_addr = p_iov_info->mbx_msg_virt_addr;
	req_p = p_iov_info->mbx_msg_phys_addr;
	p_reply_virt_addr = p_iov_info->mbx_reply_virt_addr;
	rply_p = p_iov_info->mbx_reply_phys_addr;
	p_bulletin_virt = p_iov_info->p_bulletins;
	bulletin_p = p_iov_info->bulletins_phys;
	if (!p_req_virt_addr || !p_reply_virt_addr || !p_bulletin_virt) {
		DP_ERR(p_hwfn,
		       "qed_iov_setup_vfdb called without allocating mem first\n");
		return;
	}

	for (idx = 0; idx < p_iov->total_vfs; idx++) {
		struct qed_vf_info *vf = &p_iov_info->vfs_array[idx];
		u32 concrete;

		vf->vf_mbx.req_virt = p_req_virt_addr + idx;
		vf->vf_mbx.req_phys = req_p + idx * sizeof(union vfpf_tlvs);
		vf->vf_mbx.reply_virt = p_reply_virt_addr + idx;
		vf->vf_mbx.reply_phys = rply_p + idx * sizeof(union pfvf_tlvs);

		vf->state = VF_STOPPED;
		vf->b_init = false;

		vf->bulletin.phys = idx *
				    sizeof(struct qed_bulletin_content) +
				    bulletin_p;
		vf->bulletin.p_virt = p_bulletin_virt + idx;
		vf->bulletin.size = sizeof(struct qed_bulletin_content);

		vf->relative_vf_id = idx;
		vf->abs_vf_id = idx + p_iov->first_vf_in_pf;
		concrete = qed_vfid_to_concrete(p_hwfn, vf->abs_vf_id);
		vf->concrete_fid = concrete;
		vf->opaque_fid = (p_hwfn->hw_info.opaque_fid & 0xff) |
				 (vf->abs_vf_id << 8);
		vf->vport_id = idx + 1;

		vf->num_mac_filters = QED_ETH_VF_NUM_MAC_FILTERS;
		vf->num_vlan_filters = QED_ETH_VF_NUM_VLAN_FILTERS;
	}
}