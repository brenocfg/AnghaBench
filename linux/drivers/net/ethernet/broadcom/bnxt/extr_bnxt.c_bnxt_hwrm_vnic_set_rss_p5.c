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
typedef  size_t u32 ;
typedef  size_t u16 ;
struct hwrm_vnic_rss_cfg_input {size_t ring_table_pair_index; void* rss_ctx_idx; void* hash_key_tbl_addr; void* ring_grp_tbl_addr; int /*<<< orphan*/  hash_mode_flags; int /*<<< orphan*/  hash_type; void* vnic_id; int /*<<< orphan*/  member_0; } ;
struct bnxt_vnic_info {size_t fw_vnic_id; size_t* fw_rss_cos_lb_ctx; int /*<<< orphan*/ * rss_table; int /*<<< orphan*/  rss_hash_key_dma_addr; int /*<<< orphan*/  rss_table_dma_addr; } ;
struct TYPE_2__ {size_t fw_ring_id; } ;
struct bnxt_rx_ring_info {TYPE_1__ rx_ring_struct; } ;
struct bnxt {size_t rx_nr_rings; struct bnxt_rx_ring_info* rx_ring; int /*<<< orphan*/  rss_hash_cfg; struct bnxt_vnic_info* vnic_info; } ;
typedef  int /*<<< orphan*/  req ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 size_t DIV_ROUND_UP (size_t,int) ; 
 int /*<<< orphan*/  HWRM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  HWRM_VNIC_RSS_CFG ; 
 int /*<<< orphan*/  VNIC_RSS_CFG_REQ_HASH_MODE_FLAGS_DEFAULT ; 
 size_t bnxt_cp_ring_for_rx (struct bnxt*,struct bnxt_rx_ring_info*) ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt*,struct hwrm_vnic_rss_cfg_input*,int /*<<< orphan*/ ,int,int) ; 
 void* cpu_to_le16 (size_t) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int hwrm_send_message (struct bnxt*,struct hwrm_vnic_rss_cfg_input*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnxt_hwrm_vnic_set_rss_p5(struct bnxt *bp, u16 vnic_id, bool set_rss)
{
	struct bnxt_vnic_info *vnic = &bp->vnic_info[vnic_id];
	u32 i, j, k, nr_ctxs, max_rings = bp->rx_nr_rings;
	struct bnxt_rx_ring_info *rxr = &bp->rx_ring[0];
	struct hwrm_vnic_rss_cfg_input req = {0};

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_VNIC_RSS_CFG, -1, -1);
	req.vnic_id = cpu_to_le16(vnic->fw_vnic_id);
	if (!set_rss) {
		hwrm_send_message(bp, &req, sizeof(req), HWRM_CMD_TIMEOUT);
		return 0;
	}
	req.hash_type = cpu_to_le32(bp->rss_hash_cfg);
	req.hash_mode_flags = VNIC_RSS_CFG_REQ_HASH_MODE_FLAGS_DEFAULT;
	req.ring_grp_tbl_addr = cpu_to_le64(vnic->rss_table_dma_addr);
	req.hash_key_tbl_addr = cpu_to_le64(vnic->rss_hash_key_dma_addr);
	nr_ctxs = DIV_ROUND_UP(bp->rx_nr_rings, 64);
	for (i = 0, k = 0; i < nr_ctxs; i++) {
		__le16 *ring_tbl = vnic->rss_table;
		int rc;

		req.ring_table_pair_index = i;
		req.rss_ctx_idx = cpu_to_le16(vnic->fw_rss_cos_lb_ctx[i]);
		for (j = 0; j < 64; j++) {
			u16 ring_id;

			ring_id = rxr->rx_ring_struct.fw_ring_id;
			*ring_tbl++ = cpu_to_le16(ring_id);
			ring_id = bnxt_cp_ring_for_rx(bp, rxr);
			*ring_tbl++ = cpu_to_le16(ring_id);
			rxr++;
			k++;
			if (k == max_rings) {
				k = 0;
				rxr = &bp->rx_ring[0];
			}
		}
		rc = hwrm_send_message(bp, &req, sizeof(req), HWRM_CMD_TIMEOUT);
		if (rc)
			return rc;
	}
	return 0;
}