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
struct hwrm_func_cfg_input {int /*<<< orphan*/  flags; int /*<<< orphan*/  member_0; } ;
struct bnxt {int flags; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int BNXT_FLAG_CHIP_P5 ; 
 scalar_t__ BNXT_NEW_RM (struct bnxt*) ; 
 int FUNC_CFG_REQ_FLAGS_CMPL_ASSETS_TEST ; 
 int FUNC_CFG_REQ_FLAGS_NQ_ASSETS_TEST ; 
 int FUNC_CFG_REQ_FLAGS_RING_GRP_ASSETS_TEST ; 
 int FUNC_CFG_REQ_FLAGS_RSSCOS_CTX_ASSETS_TEST ; 
 int FUNC_CFG_REQ_FLAGS_RX_ASSETS_TEST ; 
 int FUNC_CFG_REQ_FLAGS_STAT_CTX_ASSETS_TEST ; 
 int FUNC_CFG_REQ_FLAGS_TX_ASSETS_TEST ; 
 int FUNC_CFG_REQ_FLAGS_VNIC_ASSETS_TEST ; 
 int /*<<< orphan*/  HWRM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  __bnxt_hwrm_reserve_pf_rings (struct bnxt*,struct hwrm_func_cfg_input*,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int hwrm_send_message_silent (struct bnxt*,struct hwrm_func_cfg_input*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnxt_hwrm_check_pf_rings(struct bnxt *bp, int tx_rings, int rx_rings,
				    int ring_grps, int cp_rings, int stats,
				    int vnics)
{
	struct hwrm_func_cfg_input req = {0};
	u32 flags;
	int rc;

	__bnxt_hwrm_reserve_pf_rings(bp, &req, tx_rings, rx_rings, ring_grps,
				     cp_rings, stats, vnics);
	flags = FUNC_CFG_REQ_FLAGS_TX_ASSETS_TEST;
	if (BNXT_NEW_RM(bp)) {
		flags |= FUNC_CFG_REQ_FLAGS_RX_ASSETS_TEST |
			 FUNC_CFG_REQ_FLAGS_CMPL_ASSETS_TEST |
			 FUNC_CFG_REQ_FLAGS_STAT_CTX_ASSETS_TEST |
			 FUNC_CFG_REQ_FLAGS_VNIC_ASSETS_TEST;
		if (bp->flags & BNXT_FLAG_CHIP_P5)
			flags |= FUNC_CFG_REQ_FLAGS_RSSCOS_CTX_ASSETS_TEST |
				 FUNC_CFG_REQ_FLAGS_NQ_ASSETS_TEST;
		else
			flags |= FUNC_CFG_REQ_FLAGS_RING_GRP_ASSETS_TEST;
	}

	req.flags = cpu_to_le32(flags);
	rc = hwrm_send_message_silent(bp, &req, sizeof(req), HWRM_CMD_TIMEOUT);
	return rc;
}