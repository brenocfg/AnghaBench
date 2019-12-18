#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  void* u16 ;
struct hwrm_func_resource_qcaps_output {int /*<<< orphan*/  vf_reservation_strategy; int /*<<< orphan*/  max_msix; int /*<<< orphan*/  max_stat_ctx; int /*<<< orphan*/  min_stat_ctx; int /*<<< orphan*/  max_vnics; int /*<<< orphan*/  min_vnics; int /*<<< orphan*/  max_l2_ctxs; int /*<<< orphan*/  min_l2_ctxs; int /*<<< orphan*/  max_hw_ring_grps; int /*<<< orphan*/  min_hw_ring_grps; int /*<<< orphan*/  max_rx_rings; int /*<<< orphan*/  min_rx_rings; int /*<<< orphan*/  max_tx_rings; int /*<<< orphan*/  min_tx_rings; int /*<<< orphan*/  max_cmpl_rings; int /*<<< orphan*/  min_cmpl_rings; int /*<<< orphan*/  max_rsscos_ctx; int /*<<< orphan*/  min_rsscos_ctx; int /*<<< orphan*/  max_tx_scheduler_inputs; } ;
struct hwrm_func_resource_qcaps_input {int /*<<< orphan*/  fid; int /*<<< orphan*/  member_0; } ;
struct bnxt_pf_info {scalar_t__ vf_resv_strategy; } ;
struct bnxt_hw_resc {void* max_rx_rings; void* max_hw_ring_grps; void* max_nqs; void* max_stat_ctxs; void* min_stat_ctxs; void* max_vnics; void* min_vnics; void* max_l2_ctxs; void* min_l2_ctxs; void* min_hw_ring_grps; void* min_rx_rings; void* max_tx_rings; void* min_tx_rings; void* max_cp_rings; void* min_cp_rings; void* max_rsscos_ctxs; void* min_rsscos_ctxs; void* max_tx_sch_inputs; } ;
struct bnxt {int flags; int /*<<< orphan*/  hwrm_cmd_lock; struct bnxt_pf_info pf; struct bnxt_hw_resc hw_resc; struct hwrm_func_resource_qcaps_output* hwrm_cmd_resp_addr; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int BNXT_FLAG_CHIP_P5 ; 
 scalar_t__ BNXT_PF (struct bnxt*) ; 
 scalar_t__ BNXT_VF_RESV_STRATEGY_MAXIMAL ; 
 scalar_t__ BNXT_VF_RESV_STRATEGY_MINIMAL_STATIC ; 
 int /*<<< orphan*/  HWRM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  HWRM_FUNC_RESOURCE_QCAPS ; 
 int _hwrm_send_message_silent (struct bnxt*,struct hwrm_func_resource_qcaps_input*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt*,struct hwrm_func_resource_qcaps_input*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 void* le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int bnxt_hwrm_func_resc_qcaps(struct bnxt *bp, bool all)
{
	struct hwrm_func_resource_qcaps_output *resp = bp->hwrm_cmd_resp_addr;
	struct hwrm_func_resource_qcaps_input req = {0};
	struct bnxt_hw_resc *hw_resc = &bp->hw_resc;
	int rc;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FUNC_RESOURCE_QCAPS, -1, -1);
	req.fid = cpu_to_le16(0xffff);

	mutex_lock(&bp->hwrm_cmd_lock);
	rc = _hwrm_send_message_silent(bp, &req, sizeof(req),
				       HWRM_CMD_TIMEOUT);
	if (rc)
		goto hwrm_func_resc_qcaps_exit;

	hw_resc->max_tx_sch_inputs = le16_to_cpu(resp->max_tx_scheduler_inputs);
	if (!all)
		goto hwrm_func_resc_qcaps_exit;

	hw_resc->min_rsscos_ctxs = le16_to_cpu(resp->min_rsscos_ctx);
	hw_resc->max_rsscos_ctxs = le16_to_cpu(resp->max_rsscos_ctx);
	hw_resc->min_cp_rings = le16_to_cpu(resp->min_cmpl_rings);
	hw_resc->max_cp_rings = le16_to_cpu(resp->max_cmpl_rings);
	hw_resc->min_tx_rings = le16_to_cpu(resp->min_tx_rings);
	hw_resc->max_tx_rings = le16_to_cpu(resp->max_tx_rings);
	hw_resc->min_rx_rings = le16_to_cpu(resp->min_rx_rings);
	hw_resc->max_rx_rings = le16_to_cpu(resp->max_rx_rings);
	hw_resc->min_hw_ring_grps = le16_to_cpu(resp->min_hw_ring_grps);
	hw_resc->max_hw_ring_grps = le16_to_cpu(resp->max_hw_ring_grps);
	hw_resc->min_l2_ctxs = le16_to_cpu(resp->min_l2_ctxs);
	hw_resc->max_l2_ctxs = le16_to_cpu(resp->max_l2_ctxs);
	hw_resc->min_vnics = le16_to_cpu(resp->min_vnics);
	hw_resc->max_vnics = le16_to_cpu(resp->max_vnics);
	hw_resc->min_stat_ctxs = le16_to_cpu(resp->min_stat_ctx);
	hw_resc->max_stat_ctxs = le16_to_cpu(resp->max_stat_ctx);

	if (bp->flags & BNXT_FLAG_CHIP_P5) {
		u16 max_msix = le16_to_cpu(resp->max_msix);

		hw_resc->max_nqs = max_msix;
		hw_resc->max_hw_ring_grps = hw_resc->max_rx_rings;
	}

	if (BNXT_PF(bp)) {
		struct bnxt_pf_info *pf = &bp->pf;

		pf->vf_resv_strategy =
			le16_to_cpu(resp->vf_reservation_strategy);
		if (pf->vf_resv_strategy > BNXT_VF_RESV_STRATEGY_MINIMAL_STATIC)
			pf->vf_resv_strategy = BNXT_VF_RESV_STRATEGY_MAXIMAL;
	}
hwrm_func_resc_qcaps_exit:
	mutex_unlock(&bp->hwrm_cmd_lock);
	return rc;
}