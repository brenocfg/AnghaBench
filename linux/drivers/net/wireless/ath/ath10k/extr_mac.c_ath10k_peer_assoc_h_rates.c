#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct wmi_rate_set_arg {size_t num_rates; int /*<<< orphan*/ * rates; } ;
struct wmi_peer_assoc_complete_arg {struct wmi_rate_set_arg peer_legacy_rates; } ;
struct ieee80211_vif {scalar_t__ drv_priv; } ;
struct ieee80211_supported_band {struct ieee80211_rate* bitrates; } ;
struct ieee80211_sta {int* supp_rates; } ;
struct ieee80211_rate {int /*<<< orphan*/  bitrate; } ;
struct cfg80211_chan_def {TYPE_1__* chan; } ;
struct TYPE_10__ {TYPE_4__* control; } ;
struct ath10k_vif {TYPE_5__ bitrate_mask; } ;
struct ath10k {TYPE_3__* hw; int /*<<< orphan*/  conf_mutex; } ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;
struct TYPE_9__ {int legacy; } ;
struct TYPE_8__ {TYPE_2__* wiphy; } ;
struct TYPE_7__ {struct ieee80211_supported_band** bands; } ;
struct TYPE_6__ {int band; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_mac_bitrate_to_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_mac_vif_chan (struct ieee80211_vif*,struct cfg80211_chan_def*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath10k_peer_assoc_h_rates(struct ath10k *ar,
				      struct ieee80211_vif *vif,
				      struct ieee80211_sta *sta,
				      struct wmi_peer_assoc_complete_arg *arg)
{
	struct ath10k_vif *arvif = (void *)vif->drv_priv;
	struct wmi_rate_set_arg *rateset = &arg->peer_legacy_rates;
	struct cfg80211_chan_def def;
	const struct ieee80211_supported_band *sband;
	const struct ieee80211_rate *rates;
	enum nl80211_band band;
	u32 ratemask;
	u8 rate;
	int i;

	lockdep_assert_held(&ar->conf_mutex);

	if (WARN_ON(ath10k_mac_vif_chan(vif, &def)))
		return;

	band = def.chan->band;
	sband = ar->hw->wiphy->bands[band];
	ratemask = sta->supp_rates[band];
	ratemask &= arvif->bitrate_mask.control[band].legacy;
	rates = sband->bitrates;

	rateset->num_rates = 0;

	for (i = 0; i < 32; i++, ratemask >>= 1, rates++) {
		if (!(ratemask & 1))
			continue;

		rate = ath10k_mac_bitrate_to_rate(rates->bitrate);
		rateset->rates[rateset->num_rates] = rate;
		rateset->num_rates++;
	}
}