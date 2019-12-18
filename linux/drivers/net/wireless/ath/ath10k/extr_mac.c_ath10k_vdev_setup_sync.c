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
struct ath10k {int last_wmi_vdev_start_status; int /*<<< orphan*/  vdev_setup_done; int /*<<< orphan*/  dev_flags; int /*<<< orphan*/  conf_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_FLAG_CRASH_FLUSH ; 
 int /*<<< orphan*/  ATH10K_VDEV_SETUP_TIMEOUT_HZ ; 
 int ESHUTDOWN ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ath10k_vdev_setup_sync(struct ath10k *ar)
{
	unsigned long time_left;

	lockdep_assert_held(&ar->conf_mutex);

	if (test_bit(ATH10K_FLAG_CRASH_FLUSH, &ar->dev_flags))
		return -ESHUTDOWN;

	time_left = wait_for_completion_timeout(&ar->vdev_setup_done,
						ATH10K_VDEV_SETUP_TIMEOUT_HZ);
	if (time_left == 0)
		return -ETIMEDOUT;

	return ar->last_wmi_vdev_start_status;
}