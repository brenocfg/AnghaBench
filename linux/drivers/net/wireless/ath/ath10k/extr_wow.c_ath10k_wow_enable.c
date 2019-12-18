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
struct ath10k {int /*<<< orphan*/  target_suspend; int /*<<< orphan*/  conf_mutex; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int HZ ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,...) ; 
 int ath10k_wmi_wow_enable (struct ath10k*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ath10k_wow_enable(struct ath10k *ar)
{
	int ret;

	lockdep_assert_held(&ar->conf_mutex);

	reinit_completion(&ar->target_suspend);

	ret = ath10k_wmi_wow_enable(ar);
	if (ret) {
		ath10k_warn(ar, "failed to issue wow enable: %d\n", ret);
		return ret;
	}

	ret = wait_for_completion_timeout(&ar->target_suspend, 3 * HZ);
	if (ret == 0) {
		ath10k_warn(ar, "timed out while waiting for suspend completion\n");
		return -ETIMEDOUT;
	}

	return 0;
}