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
struct ufs_hba {int auto_bkops_enabled; int /*<<< orphan*/  ee_ctrl_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  MASK_EE_URGENT_BKOPS ; 
 int /*<<< orphan*/  ufshcd_disable_auto_bkops (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_enable_auto_bkops (struct ufs_hba*) ; 
 scalar_t__ ufshcd_keep_autobkops_enabled_except_suspend (struct ufs_hba*) ; 

__attribute__((used)) static void ufshcd_force_reset_auto_bkops(struct ufs_hba *hba)
{
	if (ufshcd_keep_autobkops_enabled_except_suspend(hba)) {
		hba->auto_bkops_enabled = false;
		hba->ee_ctrl_mask |= MASK_EE_URGENT_BKOPS;
		ufshcd_enable_auto_bkops(hba);
	} else {
		hba->auto_bkops_enabled = true;
		hba->ee_ctrl_mask &= ~MASK_EE_URGENT_BKOPS;
		ufshcd_disable_auto_bkops(hba);
	}
}