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
struct ufs_hba {TYPE_1__* host; } ;
struct TYPE_2__ {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int MAX_HOST_RESET_RETRIES ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int ufshcd_host_reset_and_restore (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_tmc_handler (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_transfer_req_compl (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_vops_device_reset (struct ufs_hba*) ; 

__attribute__((used)) static int ufshcd_reset_and_restore(struct ufs_hba *hba)
{
	int err = 0;
	unsigned long flags;
	int retries = MAX_HOST_RESET_RETRIES;

	do {
		/* Reset the attached device */
		ufshcd_vops_device_reset(hba);

		err = ufshcd_host_reset_and_restore(hba);
	} while (err && --retries);

	/*
	 * After reset the door-bell might be cleared, complete
	 * outstanding requests in s/w here.
	 */
	spin_lock_irqsave(hba->host->host_lock, flags);
	ufshcd_transfer_req_compl(hba);
	ufshcd_tmc_handler(hba);
	spin_unlock_irqrestore(hba->host->host_lock, flags);

	return err;
}