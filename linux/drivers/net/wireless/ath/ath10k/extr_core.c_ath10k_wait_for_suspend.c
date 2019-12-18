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
typedef  int /*<<< orphan*/  u32 ;
struct ath10k {int /*<<< orphan*/  target_suspend; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int HZ ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,...) ; 
 int ath10k_wmi_pdev_suspend_target (struct ath10k*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 

int ath10k_wait_for_suspend(struct ath10k *ar, u32 suspend_opt)
{
	int ret;
	unsigned long time_left;

	reinit_completion(&ar->target_suspend);

	ret = ath10k_wmi_pdev_suspend_target(ar, suspend_opt);
	if (ret) {
		ath10k_warn(ar, "could not suspend target (%d)\n", ret);
		return ret;
	}

	time_left = wait_for_completion_timeout(&ar->target_suspend, 1 * HZ);

	if (!time_left) {
		ath10k_warn(ar, "suspend timed out - target pause event never came\n");
		return -ETIMEDOUT;
	}

	return 0;
}