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
struct hwrm_cfa_l2_set_rx_mask_input {void* mask; int /*<<< orphan*/  mc_tbl_addr; void* num_mc_entries; void* vnic_id; int /*<<< orphan*/  member_0; } ;
struct bnxt_vnic_info {int /*<<< orphan*/  rx_mask; int /*<<< orphan*/  mc_list_mapping; int /*<<< orphan*/  mc_list_count; int /*<<< orphan*/  fw_vnic_id; } ;
struct bnxt {struct bnxt_vnic_info* vnic_info; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  HWRM_CFA_L2_SET_RX_MASK ; 
 int /*<<< orphan*/  HWRM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt*,struct hwrm_cfa_l2_set_rx_mask_input*,int /*<<< orphan*/ ,int,int) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int hwrm_send_message (struct bnxt*,struct hwrm_cfa_l2_set_rx_mask_input*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnxt_hwrm_cfa_l2_set_rx_mask(struct bnxt *bp, u16 vnic_id)
{
	struct hwrm_cfa_l2_set_rx_mask_input req = {0};
	struct bnxt_vnic_info *vnic = &bp->vnic_info[vnic_id];

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_CFA_L2_SET_RX_MASK, -1, -1);
	req.vnic_id = cpu_to_le32(vnic->fw_vnic_id);

	req.num_mc_entries = cpu_to_le32(vnic->mc_list_count);
	req.mc_tbl_addr = cpu_to_le64(vnic->mc_list_mapping);
	req.mask = cpu_to_le32(vnic->rx_mask);
	return hwrm_send_message(bp, &req, sizeof(req), HWRM_CMD_TIMEOUT);
}