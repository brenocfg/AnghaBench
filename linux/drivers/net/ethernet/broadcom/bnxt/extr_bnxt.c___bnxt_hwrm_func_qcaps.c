#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct hwrm_func_qcaps_output {int /*<<< orphan*/  mac_address; int /*<<< orphan*/  fid; int /*<<< orphan*/  max_rx_wm_flows; int /*<<< orphan*/  max_rx_em_flows; int /*<<< orphan*/  max_tx_wm_flows; int /*<<< orphan*/  max_tx_em_flows; int /*<<< orphan*/  max_decap_records; int /*<<< orphan*/  max_encap_records; int /*<<< orphan*/  max_vfs; int /*<<< orphan*/  first_vf_id; int /*<<< orphan*/  port_id; int /*<<< orphan*/  max_stat_ctx; int /*<<< orphan*/  max_vnics; int /*<<< orphan*/  max_l2_ctxs; int /*<<< orphan*/  max_hw_ring_grps; int /*<<< orphan*/  max_rx_rings; int /*<<< orphan*/  max_tx_rings; int /*<<< orphan*/  max_cmpl_rings; int /*<<< orphan*/  max_rsscos_ctx; int /*<<< orphan*/  flags; } ;
struct hwrm_func_qcaps_input {int /*<<< orphan*/  fid; int /*<<< orphan*/  member_0; } ;
struct bnxt_vf_info {int /*<<< orphan*/  mac_addr; void* fw_fid; } ;
struct bnxt_pf_info {void* max_rx_wm_flows; void* max_rx_em_flows; void* max_tx_wm_flows; void* max_tx_em_flows; void* max_decap_records; void* max_encap_records; void* max_vfs; void* first_vf_id; int /*<<< orphan*/  mac_addr; void* port_id; void* fw_fid; } ;
struct bnxt_hw_resc {void* max_stat_ctxs; void* max_vnics; void* max_l2_ctxs; void* max_tx_rings; void* max_hw_ring_grps; void* max_rx_rings; void* max_cp_rings; void* max_rsscos_ctxs; } ;
struct bnxt {int /*<<< orphan*/  hwrm_cmd_lock; struct bnxt_vf_info vf; int /*<<< orphan*/  flags; TYPE_1__* dev; struct bnxt_pf_info pf; scalar_t__ tx_push_thresh; int /*<<< orphan*/  fw_cap; struct bnxt_hw_resc hw_resc; struct hwrm_func_qcaps_output* hwrm_cmd_resp_addr; } ;
typedef  int /*<<< orphan*/  req ;
struct TYPE_2__ {void* dev_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_FLAG_ROCEV1_CAP ; 
 int /*<<< orphan*/  BNXT_FLAG_ROCEV2_CAP ; 
 int /*<<< orphan*/  BNXT_FLAG_WOL_CAP ; 
 int /*<<< orphan*/  BNXT_FW_CAP_ERROR_RECOVERY ; 
 int /*<<< orphan*/  BNXT_FW_CAP_ERR_RECOVER_RELOAD ; 
 int /*<<< orphan*/  BNXT_FW_CAP_EXT_STATS_SUPPORTED ; 
 int /*<<< orphan*/  BNXT_FW_CAP_PCIE_STATS_SUPPORTED ; 
 scalar_t__ BNXT_PF (struct bnxt*) ; 
 scalar_t__ BNXT_TX_PUSH_THRESH ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int FUNC_QCAPS_RESP_FLAGS_ERROR_RECOVERY_CAPABLE ; 
 int FUNC_QCAPS_RESP_FLAGS_ERR_RECOVER_RELOAD ; 
 int FUNC_QCAPS_RESP_FLAGS_EXT_STATS_SUPPORTED ; 
 int FUNC_QCAPS_RESP_FLAGS_PCIE_STATS_SUPPORTED ; 
 int FUNC_QCAPS_RESP_FLAGS_PUSH_MODE_SUPPORTED ; 
 int FUNC_QCAPS_RESP_FLAGS_ROCE_V1_SUPPORTED ; 
 int FUNC_QCAPS_RESP_FLAGS_ROCE_V2_SUPPORTED ; 
 int FUNC_QCAPS_RESP_FLAGS_WOL_MAGICPKT_SUPPORTED ; 
 int /*<<< orphan*/  HWRM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  HWRM_FUNC_QCAPS ; 
 int _hwrm_send_message (struct bnxt*,struct hwrm_func_qcaps_input*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt*,struct hwrm_func_qcaps_input*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __bnxt_hwrm_func_qcaps(struct bnxt *bp)
{
	int rc = 0;
	struct hwrm_func_qcaps_input req = {0};
	struct hwrm_func_qcaps_output *resp = bp->hwrm_cmd_resp_addr;
	struct bnxt_hw_resc *hw_resc = &bp->hw_resc;
	u32 flags;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FUNC_QCAPS, -1, -1);
	req.fid = cpu_to_le16(0xffff);

	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message(bp, &req, sizeof(req), HWRM_CMD_TIMEOUT);
	if (rc)
		goto hwrm_func_qcaps_exit;

	flags = le32_to_cpu(resp->flags);
	if (flags & FUNC_QCAPS_RESP_FLAGS_ROCE_V1_SUPPORTED)
		bp->flags |= BNXT_FLAG_ROCEV1_CAP;
	if (flags & FUNC_QCAPS_RESP_FLAGS_ROCE_V2_SUPPORTED)
		bp->flags |= BNXT_FLAG_ROCEV2_CAP;
	if (flags & FUNC_QCAPS_RESP_FLAGS_PCIE_STATS_SUPPORTED)
		bp->fw_cap |= BNXT_FW_CAP_PCIE_STATS_SUPPORTED;
	if (flags & FUNC_QCAPS_RESP_FLAGS_EXT_STATS_SUPPORTED)
		bp->fw_cap |= BNXT_FW_CAP_EXT_STATS_SUPPORTED;
	if (flags &  FUNC_QCAPS_RESP_FLAGS_ERROR_RECOVERY_CAPABLE)
		bp->fw_cap |= BNXT_FW_CAP_ERROR_RECOVERY;
	if (flags & FUNC_QCAPS_RESP_FLAGS_ERR_RECOVER_RELOAD)
		bp->fw_cap |= BNXT_FW_CAP_ERR_RECOVER_RELOAD;

	bp->tx_push_thresh = 0;
	if (flags & FUNC_QCAPS_RESP_FLAGS_PUSH_MODE_SUPPORTED)
		bp->tx_push_thresh = BNXT_TX_PUSH_THRESH;

	hw_resc->max_rsscos_ctxs = le16_to_cpu(resp->max_rsscos_ctx);
	hw_resc->max_cp_rings = le16_to_cpu(resp->max_cmpl_rings);
	hw_resc->max_tx_rings = le16_to_cpu(resp->max_tx_rings);
	hw_resc->max_rx_rings = le16_to_cpu(resp->max_rx_rings);
	hw_resc->max_hw_ring_grps = le32_to_cpu(resp->max_hw_ring_grps);
	if (!hw_resc->max_hw_ring_grps)
		hw_resc->max_hw_ring_grps = hw_resc->max_tx_rings;
	hw_resc->max_l2_ctxs = le16_to_cpu(resp->max_l2_ctxs);
	hw_resc->max_vnics = le16_to_cpu(resp->max_vnics);
	hw_resc->max_stat_ctxs = le16_to_cpu(resp->max_stat_ctx);

	if (BNXT_PF(bp)) {
		struct bnxt_pf_info *pf = &bp->pf;

		pf->fw_fid = le16_to_cpu(resp->fid);
		pf->port_id = le16_to_cpu(resp->port_id);
		bp->dev->dev_port = pf->port_id;
		memcpy(pf->mac_addr, resp->mac_address, ETH_ALEN);
		pf->first_vf_id = le16_to_cpu(resp->first_vf_id);
		pf->max_vfs = le16_to_cpu(resp->max_vfs);
		pf->max_encap_records = le32_to_cpu(resp->max_encap_records);
		pf->max_decap_records = le32_to_cpu(resp->max_decap_records);
		pf->max_tx_em_flows = le32_to_cpu(resp->max_tx_em_flows);
		pf->max_tx_wm_flows = le32_to_cpu(resp->max_tx_wm_flows);
		pf->max_rx_em_flows = le32_to_cpu(resp->max_rx_em_flows);
		pf->max_rx_wm_flows = le32_to_cpu(resp->max_rx_wm_flows);
		bp->flags &= ~BNXT_FLAG_WOL_CAP;
		if (flags & FUNC_QCAPS_RESP_FLAGS_WOL_MAGICPKT_SUPPORTED)
			bp->flags |= BNXT_FLAG_WOL_CAP;
	} else {
#ifdef CONFIG_BNXT_SRIOV
		struct bnxt_vf_info *vf = &bp->vf;

		vf->fw_fid = le16_to_cpu(resp->fid);
		memcpy(vf->mac_addr, resp->mac_address, ETH_ALEN);
#endif
	}

hwrm_func_qcaps_exit:
	mutex_unlock(&bp->hwrm_cmd_lock);
	return rc;
}