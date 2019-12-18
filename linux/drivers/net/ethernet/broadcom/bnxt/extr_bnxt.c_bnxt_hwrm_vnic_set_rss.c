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
typedef  size_t u32 ;
typedef  size_t u16 ;
struct hwrm_vnic_rss_cfg_input {void* rss_ctx_idx; void* hash_key_tbl_addr; void* ring_grp_tbl_addr; int /*<<< orphan*/  hash_mode_flags; int /*<<< orphan*/  hash_type; int /*<<< orphan*/  member_0; } ;
struct bnxt_vnic_info {scalar_t__* fw_rss_cos_lb_ctx; int flags; scalar_t__* fw_grp_ids; int /*<<< orphan*/  rss_hash_key_dma_addr; int /*<<< orphan*/  rss_table_dma_addr; void** rss_table; } ;
struct bnxt {int flags; size_t rx_nr_rings; int /*<<< orphan*/  rss_hash_cfg; struct bnxt_vnic_info* vnic_info; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 scalar_t__ BNXT_CHIP_TYPE_NITRO_A0 (struct bnxt*) ; 
 int BNXT_FLAG_CHIP_P5 ; 
 int BNXT_VNIC_RSS_FLAG ; 
 int /*<<< orphan*/  HWRM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  HWRM_VNIC_RSS_CFG ; 
 size_t HW_HASH_INDEX_SIZE ; 
 scalar_t__ INVALID_HW_RING_ID ; 
 int /*<<< orphan*/  VNIC_RSS_CFG_REQ_HASH_MODE_FLAGS_DEFAULT ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt*,struct hwrm_vnic_rss_cfg_input*,int /*<<< orphan*/ ,int,int) ; 
 void* cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int hwrm_send_message (struct bnxt*,struct hwrm_vnic_rss_cfg_input*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnxt_hwrm_vnic_set_rss(struct bnxt *bp, u16 vnic_id, bool set_rss)
{
	u32 i, j, max_rings;
	struct bnxt_vnic_info *vnic = &bp->vnic_info[vnic_id];
	struct hwrm_vnic_rss_cfg_input req = {0};

	if ((bp->flags & BNXT_FLAG_CHIP_P5) ||
	    vnic->fw_rss_cos_lb_ctx[0] == INVALID_HW_RING_ID)
		return 0;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_VNIC_RSS_CFG, -1, -1);
	if (set_rss) {
		req.hash_type = cpu_to_le32(bp->rss_hash_cfg);
		req.hash_mode_flags = VNIC_RSS_CFG_REQ_HASH_MODE_FLAGS_DEFAULT;
		if (vnic->flags & BNXT_VNIC_RSS_FLAG) {
			if (BNXT_CHIP_TYPE_NITRO_A0(bp))
				max_rings = bp->rx_nr_rings - 1;
			else
				max_rings = bp->rx_nr_rings;
		} else {
			max_rings = 1;
		}

		/* Fill the RSS indirection table with ring group ids */
		for (i = 0, j = 0; i < HW_HASH_INDEX_SIZE; i++, j++) {
			if (j == max_rings)
				j = 0;
			vnic->rss_table[i] = cpu_to_le16(vnic->fw_grp_ids[j]);
		}

		req.ring_grp_tbl_addr = cpu_to_le64(vnic->rss_table_dma_addr);
		req.hash_key_tbl_addr =
			cpu_to_le64(vnic->rss_hash_key_dma_addr);
	}
	req.rss_ctx_idx = cpu_to_le16(vnic->fw_rss_cos_lb_ctx[0]);
	return hwrm_send_message(bp, &req, sizeof(req), HWRM_CMD_TIMEOUT);
}