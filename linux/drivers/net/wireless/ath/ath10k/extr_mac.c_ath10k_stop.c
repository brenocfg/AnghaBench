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
struct ieee80211_hw {struct ath10k* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  timeout; } ;
struct ath10k {scalar_t__ state; int /*<<< orphan*/  restart_work; TYPE_1__ scan; int /*<<< orphan*/  set_coverage_class_work; int /*<<< orphan*/  conf_mutex; } ;

/* Variables and functions */
 scalar_t__ ATH10K_STATE_OFF ; 
 int /*<<< orphan*/  ath10k_drain_tx (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_halt (struct ath10k*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath10k_stop(struct ieee80211_hw *hw)
{
	struct ath10k *ar = hw->priv;

	ath10k_drain_tx(ar);

	mutex_lock(&ar->conf_mutex);
	if (ar->state != ATH10K_STATE_OFF) {
		ath10k_halt(ar);
		ar->state = ATH10K_STATE_OFF;
	}
	mutex_unlock(&ar->conf_mutex);

	cancel_work_sync(&ar->set_coverage_class_work);
	cancel_delayed_work_sync(&ar->scan.timeout);
	cancel_work_sync(&ar->restart_work);
}