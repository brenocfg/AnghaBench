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
struct rsi_hw {int /*<<< orphan*/  dfsentry; struct ieee80211_supported_band* sbands; struct ieee80211_hw* hw; } ;
struct ieee80211_supported_band {int /*<<< orphan*/  channels; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;

/* Variables and functions */
 int NUM_NL80211_BANDS ; 
 int /*<<< orphan*/  ieee80211_free_hw (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  ieee80211_stop_queues (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  ieee80211_unregister_hw (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsi_remove_dbgfs (struct rsi_hw*) ; 

void rsi_mac80211_detach(struct rsi_hw *adapter)
{
	struct ieee80211_hw *hw = adapter->hw;
	enum nl80211_band band;

	if (hw) {
		ieee80211_stop_queues(hw);
		ieee80211_unregister_hw(hw);
		ieee80211_free_hw(hw);
		adapter->hw = NULL;
	}

	for (band = 0; band < NUM_NL80211_BANDS; band++) {
		struct ieee80211_supported_band *sband =
					&adapter->sbands[band];

		kfree(sband->channels);
	}

#ifdef CONFIG_RSI_DEBUGFS
	rsi_remove_dbgfs(adapter);
	kfree(adapter->dfsentry);
#endif
}