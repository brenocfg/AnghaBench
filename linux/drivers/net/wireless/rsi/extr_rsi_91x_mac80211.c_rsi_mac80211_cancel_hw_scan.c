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
struct rsi_hw {int /*<<< orphan*/  hw; struct rsi_common* priv; } ;
struct rsi_common {int bgscan_en; int /*<<< orphan*/  mutex; int /*<<< orphan*/ * hwscan; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct rsi_hw* priv; } ;
struct cfg80211_scan_info {int aborted; } ;

/* Variables and functions */
 int /*<<< orphan*/  INFO_ZONE ; 
 int /*<<< orphan*/  RSI_STOP_BGSCAN ; 
 int /*<<< orphan*/  ieee80211_scan_completed (int /*<<< orphan*/ ,struct cfg80211_scan_info*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rsi_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rsi_send_bgscan_params (struct rsi_common*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rsi_mac80211_cancel_hw_scan(struct ieee80211_hw *hw,
					struct ieee80211_vif *vif)
{
	struct rsi_hw *adapter = hw->priv;
	struct rsi_common *common = adapter->priv;
	struct cfg80211_scan_info info;

	rsi_dbg(INFO_ZONE, "***** Hardware scan stop *****\n");
	mutex_lock(&common->mutex);

	if (common->bgscan_en) {
		if (!rsi_send_bgscan_params(common, RSI_STOP_BGSCAN))
			common->bgscan_en = false;
		info.aborted = false;
		ieee80211_scan_completed(adapter->hw, &info);
		rsi_dbg(INFO_ZONE, "Back ground scan cancelled\n");
	}
	common->hwscan = NULL;
	mutex_unlock(&common->mutex);
}