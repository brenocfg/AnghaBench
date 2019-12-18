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
struct ath10k {int state; int /*<<< orphan*/  conf_mutex; TYPE_2__* running_fw; } ;
struct TYPE_3__ {int /*<<< orphan*/  fw_features; } ;
struct TYPE_4__ {TYPE_1__ fw_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_FW_FEATURE_WOWLAN_SUPPORT ; 
#define  ATH10K_STATE_OFF 133 
#define  ATH10K_STATE_ON 132 
#define  ATH10K_STATE_RESTARTED 131 
#define  ATH10K_STATE_RESTARTING 130 
#define  ATH10K_STATE_UTF 129 
#define  ATH10K_STATE_WEDGED 128 
 int EIO ; 
 scalar_t__ WARN_ON (int) ; 
 int ath10k_hif_resume (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 int ath10k_wow_nlo_cleanup (struct ath10k*) ; 
 int ath10k_wow_wakeup (struct ath10k*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ath10k_wow_op_resume(struct ieee80211_hw *hw)
{
	struct ath10k *ar = hw->priv;
	int ret;

	mutex_lock(&ar->conf_mutex);

	if (WARN_ON(!test_bit(ATH10K_FW_FEATURE_WOWLAN_SUPPORT,
			      ar->running_fw->fw_file.fw_features))) {
		ret = 1;
		goto exit;
	}

	ret = ath10k_hif_resume(ar);
	if (ret) {
		ath10k_warn(ar, "failed to resume hif: %d\n", ret);
		goto exit;
	}

	ret = ath10k_wow_wakeup(ar);
	if (ret)
		ath10k_warn(ar, "failed to wakeup from wow: %d\n", ret);

	ret = ath10k_wow_nlo_cleanup(ar);
	if (ret)
		ath10k_warn(ar, "failed to cleanup nlo: %d\n", ret);

exit:
	if (ret) {
		switch (ar->state) {
		case ATH10K_STATE_ON:
			ar->state = ATH10K_STATE_RESTARTING;
			ret = 1;
			break;
		case ATH10K_STATE_OFF:
		case ATH10K_STATE_RESTARTING:
		case ATH10K_STATE_RESTARTED:
		case ATH10K_STATE_UTF:
		case ATH10K_STATE_WEDGED:
			ath10k_warn(ar, "encountered unexpected device state %d on resume, cannot recover\n",
				    ar->state);
			ret = -EIO;
			break;
		}
	}

	mutex_unlock(&ar->conf_mutex);
	return ret;
}