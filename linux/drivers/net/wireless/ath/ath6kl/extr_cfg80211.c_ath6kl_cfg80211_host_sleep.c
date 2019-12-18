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
struct ath6kl_vif {int /*<<< orphan*/  fw_vif_idx; int /*<<< orphan*/  flags; } ;
struct ath6kl {size_t ctrl_ep; int /*<<< orphan*/  event_wq; scalar_t__* tx_pending; int /*<<< orphan*/  wmi; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_HOST_MODE_ASLEEP ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  HOST_SLEEP_MODE_CMD_PROCESSED ; 
 int /*<<< orphan*/  WMI_TIMEOUT ; 
 int /*<<< orphan*/  ath6kl_warn (char*,...) ; 
 int ath6kl_wmi_set_host_sleep_mode_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_ctrl_ep_empty (struct ath6kl*) ; 
 int /*<<< orphan*/  is_hsleep_mode_procsed (struct ath6kl_vif*) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath6kl_cfg80211_host_sleep(struct ath6kl *ar, struct ath6kl_vif *vif)
{
	int ret, left;

	clear_bit(HOST_SLEEP_MODE_CMD_PROCESSED, &vif->flags);

	ret = ath6kl_wmi_set_host_sleep_mode_cmd(ar->wmi, vif->fw_vif_idx,
						 ATH6KL_HOST_MODE_ASLEEP);
	if (ret)
		return ret;

	left = wait_event_interruptible_timeout(ar->event_wq,
						is_hsleep_mode_procsed(vif),
						WMI_TIMEOUT);
	if (left == 0) {
		ath6kl_warn("timeout, didn't get host sleep cmd processed event\n");
		ret = -ETIMEDOUT;
	} else if (left < 0) {
		ath6kl_warn("error while waiting for host sleep cmd processed event %d\n",
			    left);
		ret = left;
	}

	if (ar->tx_pending[ar->ctrl_ep]) {
		left = wait_event_interruptible_timeout(ar->event_wq,
							is_ctrl_ep_empty(ar),
							WMI_TIMEOUT);
		if (left == 0) {
			ath6kl_warn("clear wmi ctrl data timeout\n");
			ret = -ETIMEDOUT;
		} else if (left < 0) {
			ath6kl_warn("clear wmi ctrl data failed: %d\n", left);
			ret = left;
		}
	}

	return ret;
}