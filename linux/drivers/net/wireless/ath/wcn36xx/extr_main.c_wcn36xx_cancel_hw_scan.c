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
struct wcn36xx {int scan_aborted; int /*<<< orphan*/  hw; int /*<<< orphan*/  scan_work; int /*<<< orphan*/  fw_feat_caps; int /*<<< orphan*/  scan_lock; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct wcn36xx* priv; } ;
struct cfg80211_scan_info {int aborted; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCAN_OFFLOAD ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 scalar_t__ get_feat_caps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_scan_completed (int /*<<< orphan*/ ,struct cfg80211_scan_info*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcn36xx_smd_stop_hw_scan (struct wcn36xx*) ; 

__attribute__((used)) static void wcn36xx_cancel_hw_scan(struct ieee80211_hw *hw,
				   struct ieee80211_vif *vif)
{
	struct wcn36xx *wcn = hw->priv;

	mutex_lock(&wcn->scan_lock);
	wcn->scan_aborted = true;
	mutex_unlock(&wcn->scan_lock);

	if (get_feat_caps(wcn->fw_feat_caps, SCAN_OFFLOAD)) {
		/* ieee80211_scan_completed will be called on FW scan
		 * indication */
		wcn36xx_smd_stop_hw_scan(wcn);
	} else {
		struct cfg80211_scan_info scan_info = {
			.aborted = true,
		};

		cancel_work_sync(&wcn->scan_work);
		ieee80211_scan_completed(wcn->hw, &scan_info);
	}
}