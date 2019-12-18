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
struct ieee80211_sta {scalar_t__ drv_priv; } ;
struct ath10k_vif {struct ath10k* ar; } ;
struct ath10k_sta {int /*<<< orphan*/  update_wk; int /*<<< orphan*/  changed; struct ath10k_vif* arvif; } ;
struct ath10k {int /*<<< orphan*/  hw; int /*<<< orphan*/  data_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_RC_SUPP_RATES_CHANGED ; 
 scalar_t__ ath10k_mac_set_vht_bitrate_mask_fixup (struct ath10k*,struct ath10k_vif*,struct ieee80211_sta*) ; 
 int /*<<< orphan*/  ieee80211_queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath10k_mac_set_bitrate_mask_iter(void *data,
					     struct ieee80211_sta *sta)
{
	struct ath10k_vif *arvif = data;
	struct ath10k_sta *arsta = (struct ath10k_sta *)sta->drv_priv;
	struct ath10k *ar = arvif->ar;

	if (arsta->arvif != arvif)
		return;

	if (ath10k_mac_set_vht_bitrate_mask_fixup(ar, arvif, sta))
		return;

	spin_lock_bh(&ar->data_lock);
	arsta->changed |= IEEE80211_RC_SUPP_RATES_CHANGED;
	spin_unlock_bh(&ar->data_lock);

	ieee80211_queue_work(ar->hw, &arsta->update_wk);
}