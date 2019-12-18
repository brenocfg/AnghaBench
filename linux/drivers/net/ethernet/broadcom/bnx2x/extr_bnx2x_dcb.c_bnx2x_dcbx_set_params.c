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
struct bnx2x {int /*<<< orphan*/  dev; int /*<<< orphan*/  dcbx_error; int /*<<< orphan*/  dcbx_local_feat; } ;

/* Variables and functions */
#define  BNX2X_DCBX_STATE_NEG_RECEIVED 130 
#define  BNX2X_DCBX_STATE_TX_PAUSED 129 
#define  BNX2X_DCBX_STATE_TX_RELEASED 128 
 int /*<<< orphan*/  BNX2X_ERR (char*) ; 
 int /*<<< orphan*/  BNX2X_MSG_DCB ; 
 int /*<<< orphan*/  BNX2X_SP_RTNL_TX_STOP ; 
 int /*<<< orphan*/  DCB_CMD_CEE_GET ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int DRV_FLAGS_DCB_CONFIGURED ; 
 int /*<<< orphan*/  DRV_MSG_CODE_DCBX_PMF_DRV_OK ; 
 int /*<<< orphan*/  IS_MF (struct bnx2x*) ; 
 int /*<<< orphan*/  RTM_GETDCB ; 
 int /*<<< orphan*/  bnx2x_dcbnl_update_applist (struct bnx2x*,int) ; 
 int /*<<< orphan*/  bnx2x_dcbx_read_shmem_neg_results (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_dcbx_read_shmem_remote_mib (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_dcbx_update_ets_params (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_dcbx_update_tc_mapping (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_dump_dcbx_drv_param (struct bnx2x*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_fw_command (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_get_dcbx_drv_param (struct bnx2x*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_link_sync_notify (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_pfc_set_pfc (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_schedule_sp_rtnl (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_set_local_cmng (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_update_drv_flags (struct bnx2x*,int,int) ; 
 int /*<<< orphan*/  dcbnl_cee_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bnx2x_dcbx_set_params(struct bnx2x *bp, u32 state)
{
	switch (state) {
	case BNX2X_DCBX_STATE_NEG_RECEIVED:
		{
			DP(BNX2X_MSG_DCB, "BNX2X_DCBX_STATE_NEG_RECEIVED\n");
#ifdef BCM_DCBNL
			/**
			 * Delete app tlvs from dcbnl before reading new
			 * negotiation results
			 */
			bnx2x_dcbnl_update_applist(bp, true);

			/* Read remote mib if dcbx is in the FW */
			if (bnx2x_dcbx_read_shmem_remote_mib(bp))
				return;
#endif
			/* Read neg results if dcbx is in the FW */
			if (bnx2x_dcbx_read_shmem_neg_results(bp))
				return;

			bnx2x_dump_dcbx_drv_param(bp, &bp->dcbx_local_feat,
						  bp->dcbx_error);

			bnx2x_get_dcbx_drv_param(bp, &bp->dcbx_local_feat,
						 bp->dcbx_error);

			/* mark DCBX result for PMF migration */
			bnx2x_update_drv_flags(bp,
					       1 << DRV_FLAGS_DCB_CONFIGURED,
					       1);
#ifdef BCM_DCBNL
			/*
			 * Add new app tlvs to dcbnl
			 */
			bnx2x_dcbnl_update_applist(bp, false);
#endif
			/*
			 * reconfigure the netdevice with the results of the new
			 * dcbx negotiation.
			 */
			bnx2x_dcbx_update_tc_mapping(bp);

			/*
			 * allow other functions to update their netdevices
			 * accordingly
			 */
			if (IS_MF(bp))
				bnx2x_link_sync_notify(bp);

			bnx2x_schedule_sp_rtnl(bp, BNX2X_SP_RTNL_TX_STOP, 0);
			return;
		}
	case BNX2X_DCBX_STATE_TX_PAUSED:
		DP(BNX2X_MSG_DCB, "BNX2X_DCBX_STATE_TX_PAUSED\n");
		bnx2x_pfc_set_pfc(bp);

		bnx2x_dcbx_update_ets_params(bp);

		/* ets may affect cmng configuration: reinit it in hw */
		bnx2x_set_local_cmng(bp);
		return;
	case BNX2X_DCBX_STATE_TX_RELEASED:
		DP(BNX2X_MSG_DCB, "BNX2X_DCBX_STATE_TX_RELEASED\n");
		bnx2x_fw_command(bp, DRV_MSG_CODE_DCBX_PMF_DRV_OK, 0);
#ifdef BCM_DCBNL
		/*
		 * Send a notification for the new negotiated parameters
		 */
		dcbnl_cee_notify(bp->dev, RTM_GETDCB, DCB_CMD_CEE_GET, 0, 0);
#endif
		return;
	default:
		BNX2X_ERR("Unknown DCBX_STATE\n");
	}
}