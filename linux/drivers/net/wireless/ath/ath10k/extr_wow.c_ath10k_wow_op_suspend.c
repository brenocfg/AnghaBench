#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_hw {struct ath10k* priv; } ;
struct cfg80211_wowlan {int dummy; } ;
struct ath10k {int /*<<< orphan*/  conf_mutex; TYPE_2__* running_fw; } ;
struct TYPE_3__ {int /*<<< orphan*/  fw_features; } ;
struct TYPE_4__ {TYPE_1__ fw_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_FW_FEATURE_WOWLAN_SUPPORT ; 
 scalar_t__ WARN_ON (int) ; 
 int ath10k_hif_suspend (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_mac_wait_tx_complete (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 int ath10k_wow_cleanup (struct ath10k*) ; 
 int ath10k_wow_enable (struct ath10k*) ; 
 int ath10k_wow_set_wakeups (struct ath10k*,struct cfg80211_wowlan*) ; 
 int /*<<< orphan*/  ath10k_wow_wakeup (struct ath10k*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ath10k_wow_op_suspend(struct ieee80211_hw *hw,
			  struct cfg80211_wowlan *wowlan)
{
	struct ath10k *ar = hw->priv;
	int ret;

	mutex_lock(&ar->conf_mutex);

	if (WARN_ON(!test_bit(ATH10K_FW_FEATURE_WOWLAN_SUPPORT,
			      ar->running_fw->fw_file.fw_features))) {
		ret = 1;
		goto exit;
	}

	ret =  ath10k_wow_cleanup(ar);
	if (ret) {
		ath10k_warn(ar, "failed to clear wow wakeup events: %d\n",
			    ret);
		goto exit;
	}

	ret = ath10k_wow_set_wakeups(ar, wowlan);
	if (ret) {
		ath10k_warn(ar, "failed to set wow wakeup events: %d\n",
			    ret);
		goto cleanup;
	}

	ath10k_mac_wait_tx_complete(ar);

	ret = ath10k_wow_enable(ar);
	if (ret) {
		ath10k_warn(ar, "failed to start wow: %d\n", ret);
		goto cleanup;
	}

	ret = ath10k_hif_suspend(ar);
	if (ret) {
		ath10k_warn(ar, "failed to suspend hif: %d\n", ret);
		goto wakeup;
	}

	goto exit;

wakeup:
	ath10k_wow_wakeup(ar);

cleanup:
	ath10k_wow_cleanup(ar);

exit:
	mutex_unlock(&ar->conf_mutex);
	return ret ? 1 : 0;
}