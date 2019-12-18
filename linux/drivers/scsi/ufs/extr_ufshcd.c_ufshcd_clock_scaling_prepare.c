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
struct ufs_hba {int /*<<< orphan*/  clk_scaling_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOORBELL_CLR_TOUT_US ; 
 int EBUSY ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ufshcd_scsi_block_requests (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_scsi_unblock_requests (struct ufs_hba*) ; 
 scalar_t__ ufshcd_wait_for_doorbell_clr (struct ufs_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ufshcd_clock_scaling_prepare(struct ufs_hba *hba)
{
	#define DOORBELL_CLR_TOUT_US		(1000 * 1000) /* 1 sec */
	int ret = 0;
	/*
	 * make sure that there are no outstanding requests when
	 * clock scaling is in progress
	 */
	ufshcd_scsi_block_requests(hba);
	down_write(&hba->clk_scaling_lock);
	if (ufshcd_wait_for_doorbell_clr(hba, DOORBELL_CLR_TOUT_US)) {
		ret = -EBUSY;
		up_write(&hba->clk_scaling_lock);
		ufshcd_scsi_unblock_requests(hba);
	}

	return ret;
}