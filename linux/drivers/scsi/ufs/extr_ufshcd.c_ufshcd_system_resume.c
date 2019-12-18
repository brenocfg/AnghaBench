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
struct ufs_hba {int is_sys_suspended; int /*<<< orphan*/  uic_link_state; int /*<<< orphan*/  curr_dev_pwr_mode; int /*<<< orphan*/  dev; int /*<<< orphan*/  is_powered; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  UFS_SYSTEM_PM ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_to_us (int /*<<< orphan*/ ) ; 
 scalar_t__ pm_runtime_suspended (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_ufshcd_system_resume (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ufshcd_resume (struct ufs_hba*,int /*<<< orphan*/ ) ; 

int ufshcd_system_resume(struct ufs_hba *hba)
{
	int ret = 0;
	ktime_t start = ktime_get();

	if (!hba)
		return -EINVAL;

	if (!hba->is_powered || pm_runtime_suspended(hba->dev))
		/*
		 * Let the runtime resume take care of resuming
		 * if runtime suspended.
		 */
		goto out;
	else
		ret = ufshcd_resume(hba, UFS_SYSTEM_PM);
out:
	trace_ufshcd_system_resume(dev_name(hba->dev), ret,
		ktime_to_us(ktime_sub(ktime_get(), start)),
		hba->curr_dev_pwr_mode, hba->uic_link_state);
	if (!ret)
		hba->is_sys_suspended = false;
	return ret;
}