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
struct TYPE_2__ {int state; } ;
struct ath10k {int /*<<< orphan*/  data_lock; TYPE_1__ scan; int /*<<< orphan*/  conf_mutex; } ;

/* Variables and functions */
#define  ATH10K_SCAN_ABORTING 131 
#define  ATH10K_SCAN_IDLE 130 
#define  ATH10K_SCAN_RUNNING 129 
#define  ATH10K_SCAN_STARTING 128 
 int /*<<< orphan*/  ath10k_scan_state_str (int) ; 
 int ath10k_scan_stop (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int,...) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath10k_scan_abort(struct ath10k *ar)
{
	int ret;

	lockdep_assert_held(&ar->conf_mutex);

	spin_lock_bh(&ar->data_lock);

	switch (ar->scan.state) {
	case ATH10K_SCAN_IDLE:
		/* This can happen if timeout worker kicked in and called
		 * abortion while scan completion was being processed.
		 */
		break;
	case ATH10K_SCAN_STARTING:
	case ATH10K_SCAN_ABORTING:
		ath10k_warn(ar, "refusing scan abortion due to invalid scan state: %s (%d)\n",
			    ath10k_scan_state_str(ar->scan.state),
			    ar->scan.state);
		break;
	case ATH10K_SCAN_RUNNING:
		ar->scan.state = ATH10K_SCAN_ABORTING;
		spin_unlock_bh(&ar->data_lock);

		ret = ath10k_scan_stop(ar);
		if (ret)
			ath10k_warn(ar, "failed to abort scan: %d\n", ret);

		spin_lock_bh(&ar->data_lock);
		break;
	}

	spin_unlock_bh(&ar->data_lock);
}