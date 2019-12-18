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
struct hwrm_func_cfg_input {int /*<<< orphan*/  enables; void* num_vnics; void* num_stat_ctxs; void* num_rsscos_ctxs; void* num_hw_ring_grps; void* num_cmpl_rings; void* num_msix; void* num_rx_rings; void* num_tx_rings; void* fid; } ;
struct bnxt {int flags; } ;

/* Variables and functions */
 int BNXT_FLAG_CHIP_P5 ; 
 int BNXT_FLAG_NEW_RSS_CAP ; 
 scalar_t__ BNXT_NEW_RM (struct bnxt*) ; 
 int DIV_ROUND_UP (int,int) ; 
 int FUNC_CFG_REQ_ENABLES_NUM_CMPL_RINGS ; 
 int FUNC_CFG_REQ_ENABLES_NUM_HW_RING_GRPS ; 
 int FUNC_CFG_REQ_ENABLES_NUM_MSIX ; 
 int FUNC_CFG_REQ_ENABLES_NUM_RSSCOS_CTXS ; 
 int FUNC_CFG_REQ_ENABLES_NUM_RX_RINGS ; 
 int FUNC_CFG_REQ_ENABLES_NUM_STAT_CTXS ; 
 int FUNC_CFG_REQ_ENABLES_NUM_TX_RINGS ; 
 int FUNC_CFG_REQ_ENABLES_NUM_VNICS ; 
 int /*<<< orphan*/  HWRM_FUNC_CFG ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt*,struct hwrm_func_cfg_input*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ bnxt_rfs_supported (struct bnxt*) ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 

__attribute__((used)) static void
__bnxt_hwrm_reserve_pf_rings(struct bnxt *bp, struct hwrm_func_cfg_input *req,
			     int tx_rings, int rx_rings, int ring_grps,
			     int cp_rings, int stats, int vnics)
{
	u32 enables = 0;

	bnxt_hwrm_cmd_hdr_init(bp, req, HWRM_FUNC_CFG, -1, -1);
	req->fid = cpu_to_le16(0xffff);
	enables |= tx_rings ? FUNC_CFG_REQ_ENABLES_NUM_TX_RINGS : 0;
	req->num_tx_rings = cpu_to_le16(tx_rings);
	if (BNXT_NEW_RM(bp)) {
		enables |= rx_rings ? FUNC_CFG_REQ_ENABLES_NUM_RX_RINGS : 0;
		enables |= stats ? FUNC_CFG_REQ_ENABLES_NUM_STAT_CTXS : 0;
		if (bp->flags & BNXT_FLAG_CHIP_P5) {
			enables |= cp_rings ? FUNC_CFG_REQ_ENABLES_NUM_MSIX : 0;
			enables |= tx_rings + ring_grps ?
				   FUNC_CFG_REQ_ENABLES_NUM_CMPL_RINGS : 0;
			enables |= rx_rings ?
				FUNC_CFG_REQ_ENABLES_NUM_RSSCOS_CTXS : 0;
		} else {
			enables |= cp_rings ?
				   FUNC_CFG_REQ_ENABLES_NUM_CMPL_RINGS : 0;
			enables |= ring_grps ?
				   FUNC_CFG_REQ_ENABLES_NUM_HW_RING_GRPS |
				   FUNC_CFG_REQ_ENABLES_NUM_RSSCOS_CTXS : 0;
		}
		enables |= vnics ? FUNC_CFG_REQ_ENABLES_NUM_VNICS : 0;

		req->num_rx_rings = cpu_to_le16(rx_rings);
		if (bp->flags & BNXT_FLAG_CHIP_P5) {
			req->num_cmpl_rings = cpu_to_le16(tx_rings + ring_grps);
			req->num_msix = cpu_to_le16(cp_rings);
			req->num_rsscos_ctxs =
				cpu_to_le16(DIV_ROUND_UP(ring_grps, 64));
		} else {
			req->num_cmpl_rings = cpu_to_le16(cp_rings);
			req->num_hw_ring_grps = cpu_to_le16(ring_grps);
			req->num_rsscos_ctxs = cpu_to_le16(1);
			if (!(bp->flags & BNXT_FLAG_NEW_RSS_CAP) &&
			    bnxt_rfs_supported(bp))
				req->num_rsscos_ctxs =
					cpu_to_le16(ring_grps + 1);
		}
		req->num_stat_ctxs = cpu_to_le16(stats);
		req->num_vnics = cpu_to_le16(vnics);
	}
	req->enables = cpu_to_le32(enables);
}