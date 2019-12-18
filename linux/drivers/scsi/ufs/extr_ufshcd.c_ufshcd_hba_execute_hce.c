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
struct ufs_hba {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  POST_CHANGE ; 
 int /*<<< orphan*/  PRE_CHANGE ; 
 int /*<<< orphan*/  UFSHCD_UIC_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ufshcd_enable_intr (struct ufs_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ufshcd_hba_start (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_hba_stop (struct ufs_hba*,int) ; 
 scalar_t__ ufshcd_is_hba_active (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_set_link_off (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_vops_hce_enable_notify (struct ufs_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int ufshcd_hba_execute_hce(struct ufs_hba *hba)
{
	int retry;

	if (!ufshcd_is_hba_active(hba))
		/* change controller state to "reset state" */
		ufshcd_hba_stop(hba, true);

	/* UniPro link is disabled at this point */
	ufshcd_set_link_off(hba);

	ufshcd_vops_hce_enable_notify(hba, PRE_CHANGE);

	/* start controller initialization sequence */
	ufshcd_hba_start(hba);

	/*
	 * To initialize a UFS host controller HCE bit must be set to 1.
	 * During initialization the HCE bit value changes from 1->0->1.
	 * When the host controller completes initialization sequence
	 * it sets the value of HCE bit to 1. The same HCE bit is read back
	 * to check if the controller has completed initialization sequence.
	 * So without this delay the value HCE = 1, set in the previous
	 * instruction might be read back.
	 * This delay can be changed based on the controller.
	 */
	usleep_range(1000, 1100);

	/* wait for the host controller to complete initialization */
	retry = 10;
	while (ufshcd_is_hba_active(hba)) {
		if (retry) {
			retry--;
		} else {
			dev_err(hba->dev,
				"Controller enable failed\n");
			return -EIO;
		}
		usleep_range(5000, 5100);
	}

	/* enable UIC related interrupts */
	ufshcd_enable_intr(hba, UFSHCD_UIC_MASK);

	ufshcd_vops_hce_enable_notify(hba, POST_CHANGE);

	return 0;
}