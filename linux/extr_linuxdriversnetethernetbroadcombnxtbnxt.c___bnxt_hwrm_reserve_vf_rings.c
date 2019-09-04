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
typedef  int u32 ;
struct hwrm_func_vf_cfg_input {int /*<<< orphan*/  enables; void* num_vnics; void* num_cmpl_rings; void* num_stat_ctxs; void* num_hw_ring_grps; void* num_rx_rings; void* num_tx_rings; } ;
struct bnxt {int dummy; } ;

/* Variables and functions */
 int FUNC_VF_CFG_REQ_ENABLES_NUM_CMPL_RINGS ; 
 int FUNC_VF_CFG_REQ_ENABLES_NUM_HW_RING_GRPS ; 
 int FUNC_VF_CFG_REQ_ENABLES_NUM_RX_RINGS ; 
 int FUNC_VF_CFG_REQ_ENABLES_NUM_STAT_CTXS ; 
 int FUNC_VF_CFG_REQ_ENABLES_NUM_TX_RINGS ; 
 int FUNC_VF_CFG_REQ_ENABLES_NUM_VNICS ; 
 int /*<<< orphan*/  HWRM_FUNC_VF_CFG ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt*,struct hwrm_func_vf_cfg_input*,int /*<<< orphan*/ ,int,int) ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 

__attribute__((used)) static void
__bnxt_hwrm_reserve_vf_rings(struct bnxt *bp,
			     struct hwrm_func_vf_cfg_input *req, int tx_rings,
			     int rx_rings, int ring_grps, int cp_rings,
			     int vnics)
{
	u32 enables = 0;

	bnxt_hwrm_cmd_hdr_init(bp, req, HWRM_FUNC_VF_CFG, -1, -1);
	enables |= tx_rings ? FUNC_VF_CFG_REQ_ENABLES_NUM_TX_RINGS : 0;
	enables |= rx_rings ? FUNC_VF_CFG_REQ_ENABLES_NUM_RX_RINGS : 0;
	enables |= cp_rings ? FUNC_VF_CFG_REQ_ENABLES_NUM_CMPL_RINGS |
			      FUNC_VF_CFG_REQ_ENABLES_NUM_STAT_CTXS : 0;
	enables |= ring_grps ? FUNC_VF_CFG_REQ_ENABLES_NUM_HW_RING_GRPS : 0;
	enables |= vnics ? FUNC_VF_CFG_REQ_ENABLES_NUM_VNICS : 0;

	req->num_tx_rings = cpu_to_le16(tx_rings);
	req->num_rx_rings = cpu_to_le16(rx_rings);
	req->num_hw_ring_grps = cpu_to_le16(ring_grps);
	req->num_cmpl_rings = cpu_to_le16(cp_rings);
	req->num_stat_ctxs = req->num_cmpl_rings;
	req->num_vnics = cpu_to_le16(vnics);

	req->enables = cpu_to_le32(enables);
}