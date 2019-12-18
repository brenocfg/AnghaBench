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
struct bnx2x {int /*<<< orphan*/  dev; int /*<<< orphan*/  dcbx_error; int /*<<< orphan*/  dcbx_local_feat; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCB_CMD_CEE_GET ; 
 int DRV_FLAGS_DCB_CONFIGURED ; 
 scalar_t__ GET_FLAGS (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RTM_GETDCB ; 
 scalar_t__ SHMEM2_HAS (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHMEM2_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_dcbnl_update_applist (struct bnx2x*,int) ; 
 scalar_t__ bnx2x_dcbx_read_shmem_neg_results (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_dcbx_update_tc_mapping (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_dump_dcbx_drv_param (struct bnx2x*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_get_dcbx_drv_param (struct bnx2x*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dcbnl_cee_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drv_flags ; 

void bnx2x_dcbx_pmf_update(struct bnx2x *bp)
{
	/* if we need to synchronize DCBX result from prev PMF
	 * read it from shmem and update bp and netdev accordingly
	 */
	if (SHMEM2_HAS(bp, drv_flags) &&
	   GET_FLAGS(SHMEM2_RD(bp, drv_flags), 1 << DRV_FLAGS_DCB_CONFIGURED)) {
		/* Read neg results if dcbx is in the FW */
		if (bnx2x_dcbx_read_shmem_neg_results(bp))
			return;

		bnx2x_dump_dcbx_drv_param(bp, &bp->dcbx_local_feat,
					  bp->dcbx_error);
		bnx2x_get_dcbx_drv_param(bp, &bp->dcbx_local_feat,
					 bp->dcbx_error);
#ifdef BCM_DCBNL
		/*
		 * Add new app tlvs to dcbnl
		 */
		bnx2x_dcbnl_update_applist(bp, false);
		/*
		 * Send a notification for the new negotiated parameters
		 */
		dcbnl_cee_notify(bp->dev, RTM_GETDCB, DCB_CMD_CEE_GET, 0, 0);
#endif
		/*
		 * reconfigure the netdevice with the results of the new
		 * dcbx negotiation.
		 */
		bnx2x_dcbx_update_tc_mapping(bp);
	}
}