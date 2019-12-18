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
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct ath10k* priv; } ;
struct TYPE_2__ {int roc_notify; int /*<<< orphan*/  timeout; } ;
struct ath10k {TYPE_1__ scan; int /*<<< orphan*/  conf_mutex; int /*<<< orphan*/  data_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath10k_scan_abort (struct ath10k*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath10k_cancel_remain_on_channel(struct ieee80211_hw *hw,
					   struct ieee80211_vif *vif)
{
	struct ath10k *ar = hw->priv;

	mutex_lock(&ar->conf_mutex);

	spin_lock_bh(&ar->data_lock);
	ar->scan.roc_notify = false;
	spin_unlock_bh(&ar->data_lock);

	ath10k_scan_abort(ar);

	mutex_unlock(&ar->conf_mutex);

	cancel_delayed_work_sync(&ar->scan.timeout);

	return 0;
}