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
typedef  size_t u16 ;
struct hwrm_vnic_cfg_input {int /*<<< orphan*/  flags; void* mru; void* lb_rule; void* dflt_ring_grp; void* vnic_id; void* cos_rule; int /*<<< orphan*/  enables; void* rss_rule; int /*<<< orphan*/  member_0; } ;
struct bnxt_vnic_info {int* fw_rss_cos_lb_ctx; int flags; int fw_vnic_id; } ;
struct bnxt {int rx_nr_rings; int flags; int /*<<< orphan*/  edev; TYPE_4__* dev; TYPE_3__* grp_info; TYPE_2__* rx_ring; struct bnxt_vnic_info* vnic_info; } ;
typedef  int /*<<< orphan*/  req ;
struct TYPE_8__ {int mtu; } ;
struct TYPE_7__ {int fw_grp_id; } ;
struct TYPE_6__ {TYPE_1__* bnapi; } ;
struct TYPE_5__ {unsigned int index; } ;

/* Variables and functions */
 scalar_t__ BNXT_CHIP_TYPE_NITRO_A0 (struct bnxt*) ; 
 int BNXT_FLAG_STRIP_VLAN ; 
 int /*<<< orphan*/  BNXT_ROCE_ULP ; 
 int BNXT_VNIC_RFS_FLAG ; 
 int BNXT_VNIC_RFS_NEW_RSS_FLAG ; 
 int BNXT_VNIC_RSS_FLAG ; 
 int ETH_FCS_LEN ; 
 int ETH_HLEN ; 
 int /*<<< orphan*/  HWRM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  HWRM_VNIC_CFG ; 
 int INVALID_HW_RING_ID ; 
 int VLAN_HLEN ; 
 int VNIC_CFG_REQ_ENABLES_COS_RULE ; 
 int VNIC_CFG_REQ_ENABLES_DFLT_RING_GRP ; 
 int VNIC_CFG_REQ_ENABLES_MRU ; 
 int VNIC_CFG_REQ_ENABLES_RSS_RULE ; 
 int VNIC_CFG_REQ_FLAGS_RSS_DFLT_CR_MODE ; 
 int VNIC_CFG_REQ_FLAGS_VLAN_STRIP_MODE ; 
 int bnxt_get_roce_vnic_mode (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt*,struct hwrm_vnic_cfg_input*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ bnxt_ulp_registered (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int hwrm_send_message (struct bnxt*,struct hwrm_vnic_cfg_input*,int,int /*<<< orphan*/ ) ; 

int bnxt_hwrm_vnic_cfg(struct bnxt *bp, u16 vnic_id)
{
	unsigned int ring = 0, grp_idx;
	struct bnxt_vnic_info *vnic = &bp->vnic_info[vnic_id];
	struct hwrm_vnic_cfg_input req = {0};
	u16 def_vlan = 0;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_VNIC_CFG, -1, -1);

	req.enables = cpu_to_le32(VNIC_CFG_REQ_ENABLES_DFLT_RING_GRP);
	/* Only RSS support for now TBD: COS & LB */
	if (vnic->fw_rss_cos_lb_ctx[0] != INVALID_HW_RING_ID) {
		req.rss_rule = cpu_to_le16(vnic->fw_rss_cos_lb_ctx[0]);
		req.enables |= cpu_to_le32(VNIC_CFG_REQ_ENABLES_RSS_RULE |
					   VNIC_CFG_REQ_ENABLES_MRU);
	} else if (vnic->flags & BNXT_VNIC_RFS_NEW_RSS_FLAG) {
		req.rss_rule =
			cpu_to_le16(bp->vnic_info[0].fw_rss_cos_lb_ctx[0]);
		req.enables |= cpu_to_le32(VNIC_CFG_REQ_ENABLES_RSS_RULE |
					   VNIC_CFG_REQ_ENABLES_MRU);
		req.flags |= cpu_to_le32(VNIC_CFG_REQ_FLAGS_RSS_DFLT_CR_MODE);
	} else {
		req.rss_rule = cpu_to_le16(0xffff);
	}

	if (BNXT_CHIP_TYPE_NITRO_A0(bp) &&
	    (vnic->fw_rss_cos_lb_ctx[0] != INVALID_HW_RING_ID)) {
		req.cos_rule = cpu_to_le16(vnic->fw_rss_cos_lb_ctx[1]);
		req.enables |= cpu_to_le32(VNIC_CFG_REQ_ENABLES_COS_RULE);
	} else {
		req.cos_rule = cpu_to_le16(0xffff);
	}

	if (vnic->flags & BNXT_VNIC_RSS_FLAG)
		ring = 0;
	else if (vnic->flags & BNXT_VNIC_RFS_FLAG)
		ring = vnic_id - 1;
	else if ((vnic_id == 1) && BNXT_CHIP_TYPE_NITRO_A0(bp))
		ring = bp->rx_nr_rings - 1;

	grp_idx = bp->rx_ring[ring].bnapi->index;
	req.vnic_id = cpu_to_le16(vnic->fw_vnic_id);
	req.dflt_ring_grp = cpu_to_le16(bp->grp_info[grp_idx].fw_grp_id);

	req.lb_rule = cpu_to_le16(0xffff);
	req.mru = cpu_to_le16(bp->dev->mtu + ETH_HLEN + ETH_FCS_LEN +
			      VLAN_HLEN);

#ifdef CONFIG_BNXT_SRIOV
	if (BNXT_VF(bp))
		def_vlan = bp->vf.vlan;
#endif
	if ((bp->flags & BNXT_FLAG_STRIP_VLAN) || def_vlan)
		req.flags |= cpu_to_le32(VNIC_CFG_REQ_FLAGS_VLAN_STRIP_MODE);
	if (!vnic_id && bnxt_ulp_registered(bp->edev, BNXT_ROCE_ULP))
		req.flags |= cpu_to_le32(bnxt_get_roce_vnic_mode(bp));

	return hwrm_send_message(bp, &req, sizeof(req), HWRM_CMD_TIMEOUT);
}