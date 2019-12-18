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
typedef  size_t u16 ;
struct hwrm_vnic_tpa_cfg_input {void* vnic_id; void* min_agg_len; void* max_aggs; void* max_agg_segs; void* enables; void* flags; int /*<<< orphan*/  member_0; } ;
struct bnxt_vnic_info {scalar_t__ fw_vnic_id; } ;
struct bnxt {int flags; size_t max_tpa; TYPE_1__* dev; struct bnxt_vnic_info* vnic_info; } ;
typedef  int /*<<< orphan*/  req ;
struct TYPE_2__ {size_t mtu; } ;

/* Variables and functions */
 int BNXT_FLAG_CHIP_P5 ; 
 int BNXT_FLAG_GRO ; 
 size_t BNXT_RX_PAGE_SIZE ; 
 int /*<<< orphan*/  HWRM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  HWRM_VNIC_TPA_CFG ; 
 scalar_t__ INVALID_HW_RING_ID ; 
 int MAX_SKB_FRAGS ; 
 int MAX_TPA_SEGS_P5 ; 
 int VNIC_TPA_CFG_REQ_ENABLES_MAX_AGGS ; 
 int VNIC_TPA_CFG_REQ_ENABLES_MAX_AGG_SEGS ; 
 int VNIC_TPA_CFG_REQ_ENABLES_MIN_AGG_LEN ; 
 int VNIC_TPA_CFG_REQ_FLAGS_AGG_WITH_ECN ; 
 int VNIC_TPA_CFG_REQ_FLAGS_AGG_WITH_SAME_GRE_SEQ ; 
 int VNIC_TPA_CFG_REQ_FLAGS_ENCAP_TPA ; 
 int VNIC_TPA_CFG_REQ_FLAGS_GRO ; 
 int VNIC_TPA_CFG_REQ_FLAGS_RSC_WND_UPDATE ; 
 int VNIC_TPA_CFG_REQ_FLAGS_TPA ; 
 size_t VNIC_TPA_CFG_REQ_MAX_AGGS_MAX ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt*,struct hwrm_vnic_tpa_cfg_input*,int /*<<< orphan*/ ,int,int) ; 
 void* cpu_to_le16 (size_t) ; 
 void* cpu_to_le32 (int) ; 
 int hwrm_send_message (struct bnxt*,struct hwrm_vnic_tpa_cfg_input*,int,int /*<<< orphan*/ ) ; 
 int ilog2 (int) ; 

__attribute__((used)) static int bnxt_hwrm_vnic_set_tpa(struct bnxt *bp, u16 vnic_id, u32 tpa_flags)
{
	struct bnxt_vnic_info *vnic = &bp->vnic_info[vnic_id];
	u16 max_aggs = VNIC_TPA_CFG_REQ_MAX_AGGS_MAX;
	struct hwrm_vnic_tpa_cfg_input req = {0};

	if (vnic->fw_vnic_id == INVALID_HW_RING_ID)
		return 0;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_VNIC_TPA_CFG, -1, -1);

	if (tpa_flags) {
		u16 mss = bp->dev->mtu - 40;
		u32 nsegs, n, segs = 0, flags;

		flags = VNIC_TPA_CFG_REQ_FLAGS_TPA |
			VNIC_TPA_CFG_REQ_FLAGS_ENCAP_TPA |
			VNIC_TPA_CFG_REQ_FLAGS_RSC_WND_UPDATE |
			VNIC_TPA_CFG_REQ_FLAGS_AGG_WITH_ECN |
			VNIC_TPA_CFG_REQ_FLAGS_AGG_WITH_SAME_GRE_SEQ;
		if (tpa_flags & BNXT_FLAG_GRO)
			flags |= VNIC_TPA_CFG_REQ_FLAGS_GRO;

		req.flags = cpu_to_le32(flags);

		req.enables =
			cpu_to_le32(VNIC_TPA_CFG_REQ_ENABLES_MAX_AGG_SEGS |
				    VNIC_TPA_CFG_REQ_ENABLES_MAX_AGGS |
				    VNIC_TPA_CFG_REQ_ENABLES_MIN_AGG_LEN);

		/* Number of segs are log2 units, and first packet is not
		 * included as part of this units.
		 */
		if (mss <= BNXT_RX_PAGE_SIZE) {
			n = BNXT_RX_PAGE_SIZE / mss;
			nsegs = (MAX_SKB_FRAGS - 1) * n;
		} else {
			n = mss / BNXT_RX_PAGE_SIZE;
			if (mss & (BNXT_RX_PAGE_SIZE - 1))
				n++;
			nsegs = (MAX_SKB_FRAGS - n) / n;
		}

		if (bp->flags & BNXT_FLAG_CHIP_P5) {
			segs = MAX_TPA_SEGS_P5;
			max_aggs = bp->max_tpa;
		} else {
			segs = ilog2(nsegs);
		}
		req.max_agg_segs = cpu_to_le16(segs);
		req.max_aggs = cpu_to_le16(max_aggs);

		req.min_agg_len = cpu_to_le32(512);
	}
	req.vnic_id = cpu_to_le16(vnic->fw_vnic_id);

	return hwrm_send_message(bp, &req, sizeof(req), HWRM_CMD_TIMEOUT);
}