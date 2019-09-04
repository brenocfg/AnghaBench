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
struct TYPE_7__ {int caps; int /*<<< orphan*/  fp_hsi_ver; int /*<<< orphan*/  vf_os; int /*<<< orphan*/  vf_id; } ;
struct TYPE_8__ {int /*<<< orphan*/  num_mc_filters; int /*<<< orphan*/  num_vlan_filters; int /*<<< orphan*/  num_mac_filters; int /*<<< orphan*/  num_sbs; int /*<<< orphan*/  num_txqs; int /*<<< orphan*/  num_rxqs; } ;
struct vfpf_acquire_tlv {TYPE_3__ vfdev_info; int /*<<< orphan*/  bulletin_addr; TYPE_4__ resc_request; } ;
struct bnx2x_virtf {int /*<<< orphan*/  cfg_flags; int /*<<< orphan*/  abs_vfid; int /*<<< orphan*/  bulletin_map; int /*<<< orphan*/  fp_hsi; } ;
struct bnx2x_vf_mbx {TYPE_2__* msg; } ;
struct bnx2x {int dummy; } ;
struct TYPE_5__ {struct vfpf_acquire_tlv acquire; } ;
struct TYPE_6__ {TYPE_1__ req; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MSG_IOV ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int EINVAL ; 
 int /*<<< orphan*/  ETH_FP_HSI_VERSION ; 
 int /*<<< orphan*/  ETH_FP_HSI_VER_2 ; 
 int VF_CAP_SUPPORT_EXT_BULLETIN ; 
 int VF_CAP_SUPPORT_VLAN_FILTER ; 
 int /*<<< orphan*/  VF_CFG_EXT_BULLETIN ; 
 int /*<<< orphan*/  VF_CFG_VLAN_FILTER ; 
 int bnx2x_vf_acquire (struct bnx2x*,struct bnx2x_virtf*,TYPE_4__*) ; 
 int bnx2x_vf_mbx_acquire_chk_dorq (struct bnx2x*,struct bnx2x_virtf*,struct bnx2x_vf_mbx*) ; 
 int /*<<< orphan*/  bnx2x_vf_mbx_acquire_resp (struct bnx2x*,struct bnx2x_virtf*,struct bnx2x_vf_mbx*,int) ; 
 scalar_t__ bnx2x_vf_mbx_is_windows_vm (struct bnx2x*,struct vfpf_acquire_tlv*) ; 
 int /*<<< orphan*/  max_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u8 ; 

__attribute__((used)) static void bnx2x_vf_mbx_acquire(struct bnx2x *bp, struct bnx2x_virtf *vf,
				 struct bnx2x_vf_mbx *mbx)
{
	int rc;
	struct vfpf_acquire_tlv *acquire = &mbx->msg->req.acquire;

	/* log vfdef info */
	DP(BNX2X_MSG_IOV,
	   "VF[%d] ACQUIRE: vfdev_info- vf_id %d, vf_os %d resources- n_rxq-%d, n_txq-%d, n_sbs-%d, n_macs-%d, n_vlans-%d, n_mcs-%d\n",
	   vf->abs_vfid, acquire->vfdev_info.vf_id, acquire->vfdev_info.vf_os,
	   acquire->resc_request.num_rxqs, acquire->resc_request.num_txqs,
	   acquire->resc_request.num_sbs, acquire->resc_request.num_mac_filters,
	   acquire->resc_request.num_vlan_filters,
	   acquire->resc_request.num_mc_filters);

	/* Prevent VFs with old drivers from loading, since they calculate
	 * CIDs incorrectly requiring a VF-flr [VM reboot] in order to recover
	 * while being upgraded.
	 */
	rc = bnx2x_vf_mbx_acquire_chk_dorq(bp, vf, mbx);
	if (rc) {
		DP(BNX2X_MSG_IOV,
		   "VF [%d] - Can't support acquire request due to doorbell mismatch. Please update VM driver\n",
		   vf->abs_vfid);
		goto out;
	}

	/* Verify the VF fastpath HSI can be supported by the loaded FW.
	 * Linux vfs should be oblivious to changes between v0 and v2.
	 */
	if (bnx2x_vf_mbx_is_windows_vm(bp, &mbx->msg->req.acquire))
		vf->fp_hsi = acquire->vfdev_info.fp_hsi_ver;
	else
		vf->fp_hsi = max_t(u8, acquire->vfdev_info.fp_hsi_ver,
				   ETH_FP_HSI_VER_2);
	if (vf->fp_hsi > ETH_FP_HSI_VERSION) {
		DP(BNX2X_MSG_IOV,
		   "VF [%d] - Can't support acquire request since VF requests a FW version which is too new [%02x > %02x]\n",
		   vf->abs_vfid, acquire->vfdev_info.fp_hsi_ver,
		   ETH_FP_HSI_VERSION);
		rc = -EINVAL;
		goto out;
	}

	/* acquire the resources */
	rc = bnx2x_vf_acquire(bp, vf, &acquire->resc_request);

	/* store address of vf's bulletin board */
	vf->bulletin_map = acquire->bulletin_addr;
	if (acquire->vfdev_info.caps & VF_CAP_SUPPORT_EXT_BULLETIN) {
		DP(BNX2X_MSG_IOV, "VF[%d] supports long bulletin boards\n",
		   vf->abs_vfid);
		vf->cfg_flags |= VF_CFG_EXT_BULLETIN;
	} else {
		vf->cfg_flags &= ~VF_CFG_EXT_BULLETIN;
	}

	if (acquire->vfdev_info.caps & VF_CAP_SUPPORT_VLAN_FILTER) {
		DP(BNX2X_MSG_IOV, "VF[%d] supports vlan filtering\n",
		   vf->abs_vfid);
		vf->cfg_flags |= VF_CFG_VLAN_FILTER;
	} else {
		vf->cfg_flags &= ~VF_CFG_VLAN_FILTER;
	}

out:
	/* response */
	bnx2x_vf_mbx_acquire_resp(bp, vf, mbx, rc);
}