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
typedef  int u32 ;
struct ieee80211_vif {scalar_t__ drv_priv; } ;
struct ieee80211_hw {struct ath5k_hw* priv; } ;
struct ieee80211_bss_conf {int /*<<< orphan*/  enable_beacon; scalar_t__ aid; scalar_t__ assoc; int /*<<< orphan*/  use_short_slot; int /*<<< orphan*/  beacon_int; int /*<<< orphan*/  bssid; } ;
struct ath_common {scalar_t__ curaid; int /*<<< orphan*/  curbssid; } ;
struct ath5k_vif {scalar_t__ assoc; } ;
struct ath5k_hw {int ah_coverage_class; scalar_t__ opmode; int /*<<< orphan*/  lock; int /*<<< orphan*/  enable_beacon; int /*<<< orphan*/  block; scalar_t__ assoc; int /*<<< orphan*/  ah_short_slot; int /*<<< orphan*/  bintval; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR5K_LED_ASSOC ; 
 int /*<<< orphan*/  AR5K_LED_INIT ; 
 int /*<<< orphan*/  ATH5K_DBG (struct ath5k_hw*,int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATH5K_DEBUG_ANY ; 
 int BSS_CHANGED_ASSOC ; 
 int BSS_CHANGED_BEACON ; 
 int BSS_CHANGED_BEACON_ENABLED ; 
 int BSS_CHANGED_BEACON_INT ; 
 int BSS_CHANGED_BSSID ; 
 int BSS_CHANGED_ERP_SLOT ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 scalar_t__ ath5k_any_vif_assoc (struct ath5k_hw*) ; 
 int /*<<< orphan*/  ath5k_beacon_config (struct ath5k_hw*) ; 
 int /*<<< orphan*/  ath5k_beacon_update (struct ieee80211_hw*,struct ieee80211_vif*) ; 
 struct ath_common* ath5k_hw_common (struct ath5k_hw*) ; 
 int ath5k_hw_get_default_slottime (struct ath5k_hw*) ; 
 int /*<<< orphan*/  ath5k_hw_set_bssid (struct ath5k_hw*) ; 
 int /*<<< orphan*/  ath5k_hw_set_ifs_intervals (struct ath5k_hw*,int) ; 
 int /*<<< orphan*/  ath5k_hw_set_ledstate (struct ath5k_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath5k_set_beacon_filter (struct ieee80211_hw*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ath5k_bss_info_changed(struct ieee80211_hw *hw, struct ieee80211_vif *vif,
		       struct ieee80211_bss_conf *bss_conf, u32 changes)
{
	struct ath5k_vif *avf = (void *)vif->drv_priv;
	struct ath5k_hw *ah = hw->priv;
	struct ath_common *common = ath5k_hw_common(ah);

	mutex_lock(&ah->lock);

	if (changes & BSS_CHANGED_BSSID) {
		/* Cache for later use during resets */
		memcpy(common->curbssid, bss_conf->bssid, ETH_ALEN);
		common->curaid = 0;
		ath5k_hw_set_bssid(ah);
	}

	if (changes & BSS_CHANGED_BEACON_INT)
		ah->bintval = bss_conf->beacon_int;

	if (changes & BSS_CHANGED_ERP_SLOT) {
		int slot_time;

		ah->ah_short_slot = bss_conf->use_short_slot;
		slot_time = ath5k_hw_get_default_slottime(ah) +
			    3 * ah->ah_coverage_class;
		ath5k_hw_set_ifs_intervals(ah, slot_time);
	}

	if (changes & BSS_CHANGED_ASSOC) {
		avf->assoc = bss_conf->assoc;
		if (bss_conf->assoc)
			ah->assoc = bss_conf->assoc;
		else
			ah->assoc = ath5k_any_vif_assoc(ah);

		if (ah->opmode == NL80211_IFTYPE_STATION)
			ath5k_set_beacon_filter(hw, ah->assoc);
		ath5k_hw_set_ledstate(ah, ah->assoc ?
			AR5K_LED_ASSOC : AR5K_LED_INIT);
		if (bss_conf->assoc) {
			ATH5K_DBG(ah, ATH5K_DEBUG_ANY,
				  "Bss Info ASSOC %d, bssid: %pM\n",
				  bss_conf->aid, common->curbssid);
			common->curaid = bss_conf->aid;
			ath5k_hw_set_bssid(ah);
			/* Once ANI is available you would start it here */
		}
	}

	if (changes & BSS_CHANGED_BEACON) {
		spin_lock_bh(&ah->block);
		ath5k_beacon_update(hw, vif);
		spin_unlock_bh(&ah->block);
	}

	if (changes & BSS_CHANGED_BEACON_ENABLED)
		ah->enable_beacon = bss_conf->enable_beacon;

	if (changes & (BSS_CHANGED_BEACON | BSS_CHANGED_BEACON_ENABLED |
		       BSS_CHANGED_BEACON_INT))
		ath5k_beacon_config(ah);

	mutex_unlock(&ah->lock);
}