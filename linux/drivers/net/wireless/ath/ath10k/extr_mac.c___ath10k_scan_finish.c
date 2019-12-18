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
struct cfg80211_scan_info {int aborted; } ;
struct TYPE_2__ {int state; int /*<<< orphan*/  completed; int /*<<< orphan*/  timeout; int /*<<< orphan*/  roc_freq; int /*<<< orphan*/  roc_notify; int /*<<< orphan*/  is_roc; } ;
struct ath10k {TYPE_1__ scan; int /*<<< orphan*/ * scan_channel; int /*<<< orphan*/  hw; int /*<<< orphan*/  data_lock; } ;

/* Variables and functions */
#define  ATH10K_SCAN_ABORTING 131 
#define  ATH10K_SCAN_IDLE 130 
#define  ATH10K_SCAN_RUNNING 129 
#define  ATH10K_SCAN_STARTING 128 
 int /*<<< orphan*/  ath10k_offchan_tx_purge (struct ath10k*) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_remain_on_channel_expired (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_scan_completed (int /*<<< orphan*/ ,struct cfg80211_scan_info*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

void __ath10k_scan_finish(struct ath10k *ar)
{
	lockdep_assert_held(&ar->data_lock);

	switch (ar->scan.state) {
	case ATH10K_SCAN_IDLE:
		break;
	case ATH10K_SCAN_RUNNING:
	case ATH10K_SCAN_ABORTING:
		if (!ar->scan.is_roc) {
			struct cfg80211_scan_info info = {
				.aborted = (ar->scan.state ==
					    ATH10K_SCAN_ABORTING),
			};

			ieee80211_scan_completed(ar->hw, &info);
		} else if (ar->scan.roc_notify) {
			ieee80211_remain_on_channel_expired(ar->hw);
		}
		/* fall through */
	case ATH10K_SCAN_STARTING:
		ar->scan.state = ATH10K_SCAN_IDLE;
		ar->scan_channel = NULL;
		ar->scan.roc_freq = 0;
		ath10k_offchan_tx_purge(ar);
		cancel_delayed_work(&ar->scan.timeout);
		complete(&ar->scan.completed);
		break;
	}
}