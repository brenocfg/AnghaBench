#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_7__ {int /*<<< orphan*/  basic_rates; int /*<<< orphan*/  use_short_preamble; } ;
struct ieee80211_vif {TYPE_1__ bss_conf; } ;
struct TYPE_9__ {TYPE_2__* chan; } ;
struct TYPE_10__ {TYPE_3__ chandef; } ;
struct ieee80211_hw {TYPE_4__ conf; } ;
struct ieee80211_bss_conf {int /*<<< orphan*/  enable_beacon; } ;
struct TYPE_12__ {int hw_value; } ;
struct TYPE_11__ {int hw_value; } ;
struct TYPE_8__ {scalar_t__ band; } ;

/* Variables and functions */
 int BSS_CHANGED_BASIC_RATES ; 
 int BSS_CHANGED_BEACON ; 
 int BSS_CHANGED_BEACON_ENABLED ; 
 int BSS_CHANGED_BEACON_INT ; 
 int BSS_CHANGED_ERP_PREAMBLE ; 
 scalar_t__ NL80211_BAND_2GHZ ; 
 int ffs (int /*<<< orphan*/ ) ; 
 struct sk_buff* ieee80211_beacon_get (struct ieee80211_hw*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  mwl8k_cmd_bss_start (struct ieee80211_hw*,struct ieee80211_vif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwl8k_cmd_set_beacon (struct ieee80211_hw*,struct ieee80211_vif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwl8k_cmd_use_fixed_rate_ap (struct ieee80211_hw*,int,int) ; 
 scalar_t__ mwl8k_fw_lock (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  mwl8k_fw_unlock (struct ieee80211_hw*) ; 
 TYPE_6__* mwl8k_rates_24 ; 
 TYPE_5__* mwl8k_rates_50 ; 
 int mwl8k_set_radio_preamble (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mwl8k_bss_info_changed_ap(struct ieee80211_hw *hw, struct ieee80211_vif *vif,
			  struct ieee80211_bss_conf *info, u32 changed)
{
	int rc;

	if (mwl8k_fw_lock(hw))
		return;

	if (changed & BSS_CHANGED_ERP_PREAMBLE) {
		rc = mwl8k_set_radio_preamble(hw,
				vif->bss_conf.use_short_preamble);
		if (rc)
			goto out;
	}

	if (changed & BSS_CHANGED_BASIC_RATES) {
		int idx;
		int rate;

		/*
		 * Use lowest supported basic rate for multicasts
		 * and management frames (such as probe responses --
		 * beacons will always go out at 1 Mb/s).
		 */
		idx = ffs(vif->bss_conf.basic_rates);
		if (idx)
			idx--;

		if (hw->conf.chandef.chan->band == NL80211_BAND_2GHZ)
			rate = mwl8k_rates_24[idx].hw_value;
		else
			rate = mwl8k_rates_50[idx].hw_value;

		mwl8k_cmd_use_fixed_rate_ap(hw, rate, rate);
	}

	if (changed & (BSS_CHANGED_BEACON_INT | BSS_CHANGED_BEACON)) {
		struct sk_buff *skb;

		skb = ieee80211_beacon_get(hw, vif);
		if (skb != NULL) {
			mwl8k_cmd_set_beacon(hw, vif, skb->data, skb->len);
			kfree_skb(skb);
		}
	}

	if (changed & BSS_CHANGED_BEACON_ENABLED)
		mwl8k_cmd_bss_start(hw, vif, info->enable_beacon);

out:
	mwl8k_fw_unlock(hw);
}