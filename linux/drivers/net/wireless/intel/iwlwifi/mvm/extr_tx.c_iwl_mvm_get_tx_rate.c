#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct iwl_mvm {TYPE_3__* nvm_data; } ;
struct TYPE_5__ {TYPE_1__* rates; } ;
struct ieee80211_tx_info {size_t band; TYPE_2__ control; } ;
struct ieee80211_sta {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/ * bands; } ;
struct TYPE_4__ {int flags; int idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int IEEE80211_TX_RC_MCS ; 
 int IWL_FIRST_CCK_RATE ; 
 scalar_t__ IWL_FIRST_OFDM_RATE ; 
 int IWL_LAST_CCK_RATE ; 
 int IWL_RATE_COUNT_LEGACY ; 
 size_t NL80211_BAND_5GHZ ; 
 int RATE_MCS_CCK_MSK ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int,int) ; 
 scalar_t__ iwl_mvm_mac80211_idx_to_hwrate (int) ; 
 int rate_lowest_index (int /*<<< orphan*/ *,struct ieee80211_sta*) ; 

__attribute__((used)) static u32 iwl_mvm_get_tx_rate(struct iwl_mvm *mvm,
			       struct ieee80211_tx_info *info,
			       struct ieee80211_sta *sta)
{
	int rate_idx;
	u8 rate_plcp;
	u32 rate_flags = 0;

	/* HT rate doesn't make sense for a non data frame */
	WARN_ONCE(info->control.rates[0].flags & IEEE80211_TX_RC_MCS,
		  "Got an HT rate (flags:0x%x/mcs:%d) for a non data frame\n",
		  info->control.rates[0].flags,
		  info->control.rates[0].idx);

	rate_idx = info->control.rates[0].idx;
	/* if the rate isn't a well known legacy rate, take the lowest one */
	if (rate_idx < 0 || rate_idx >= IWL_RATE_COUNT_LEGACY)
		rate_idx = rate_lowest_index(
				&mvm->nvm_data->bands[info->band], sta);

	/* For 5 GHZ band, remap mac80211 rate indices into driver indices */
	if (info->band == NL80211_BAND_5GHZ)
		rate_idx += IWL_FIRST_OFDM_RATE;

	/* For 2.4 GHZ band, check that there is no need to remap */
	BUILD_BUG_ON(IWL_FIRST_CCK_RATE != 0);

	/* Get PLCP rate for tx_cmd->rate_n_flags */
	rate_plcp = iwl_mvm_mac80211_idx_to_hwrate(rate_idx);

	/* Set CCK flag as needed */
	if ((rate_idx >= IWL_FIRST_CCK_RATE) && (rate_idx <= IWL_LAST_CCK_RATE))
		rate_flags |= RATE_MCS_CCK_MSK;

	return (u32)rate_plcp | rate_flags;
}