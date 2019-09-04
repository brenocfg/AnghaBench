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
typedef  size_t u16 ;
struct hwrm_vnic_plcmodes_cfg_input {void* vnic_id; void* hds_threshold; void* jumbo_thresh; void* enables; void* flags; int /*<<< orphan*/  member_0; } ;
struct bnxt_vnic_info {int fw_vnic_id; } ;
struct bnxt {int /*<<< orphan*/  rx_copy_thresh; struct bnxt_vnic_info* vnic_info; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  HWRM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  HWRM_VNIC_PLCMODES_CFG ; 
 int VNIC_PLCMODES_CFG_REQ_ENABLES_HDS_THRESHOLD_VALID ; 
 int VNIC_PLCMODES_CFG_REQ_ENABLES_JUMBO_THRESH_VALID ; 
 int VNIC_PLCMODES_CFG_REQ_FLAGS_HDS_IPV4 ; 
 int VNIC_PLCMODES_CFG_REQ_FLAGS_HDS_IPV6 ; 
 int VNIC_PLCMODES_CFG_REQ_FLAGS_JUMBO_PLACEMENT ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt*,struct hwrm_vnic_plcmodes_cfg_input*,int /*<<< orphan*/ ,int,int) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int) ; 
 int hwrm_send_message (struct bnxt*,struct hwrm_vnic_plcmodes_cfg_input*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnxt_hwrm_vnic_set_hds(struct bnxt *bp, u16 vnic_id)
{
	struct bnxt_vnic_info *vnic = &bp->vnic_info[vnic_id];
	struct hwrm_vnic_plcmodes_cfg_input req = {0};

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_VNIC_PLCMODES_CFG, -1, -1);
	req.flags = cpu_to_le32(VNIC_PLCMODES_CFG_REQ_FLAGS_JUMBO_PLACEMENT |
				VNIC_PLCMODES_CFG_REQ_FLAGS_HDS_IPV4 |
				VNIC_PLCMODES_CFG_REQ_FLAGS_HDS_IPV6);
	req.enables =
		cpu_to_le32(VNIC_PLCMODES_CFG_REQ_ENABLES_JUMBO_THRESH_VALID |
			    VNIC_PLCMODES_CFG_REQ_ENABLES_HDS_THRESHOLD_VALID);
	/* thresholds not implemented in firmware yet */
	req.jumbo_thresh = cpu_to_le16(bp->rx_copy_thresh);
	req.hds_threshold = cpu_to_le16(bp->rx_copy_thresh);
	req.vnic_id = cpu_to_le32(vnic->fw_vnic_id);
	return hwrm_send_message(bp, &req, sizeof(req), HWRM_CMD_TIMEOUT);
}