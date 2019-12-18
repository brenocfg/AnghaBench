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
struct wmi_start_scan_arg {int dummy; } ;
struct TYPE_2__ {scalar_t__ state; int /*<<< orphan*/  started; } ;
struct ath10k {int /*<<< orphan*/  data_lock; TYPE_1__ scan; int /*<<< orphan*/  conf_mutex; } ;

/* Variables and functions */
 scalar_t__ ATH10K_SCAN_IDLE ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
 int HZ ; 
 int ath10k_scan_stop (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 int ath10k_wmi_start_scan (struct ath10k*,struct wmi_start_scan_arg const*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ath10k_start_scan(struct ath10k *ar,
			     const struct wmi_start_scan_arg *arg)
{
	int ret;

	lockdep_assert_held(&ar->conf_mutex);

	ret = ath10k_wmi_start_scan(ar, arg);
	if (ret)
		return ret;

	ret = wait_for_completion_timeout(&ar->scan.started, 1 * HZ);
	if (ret == 0) {
		ret = ath10k_scan_stop(ar);
		if (ret)
			ath10k_warn(ar, "failed to stop scan: %d\n", ret);

		return -ETIMEDOUT;
	}

	/* If we failed to start the scan, return error code at
	 * this point.  This is probably due to some issue in the
	 * firmware, but no need to wedge the driver due to that...
	 */
	spin_lock_bh(&ar->data_lock);
	if (ar->scan.state == ATH10K_SCAN_IDLE) {
		spin_unlock_bh(&ar->data_lock);
		return -EINVAL;
	}
	spin_unlock_bh(&ar->data_lock);

	return 0;
}