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
struct rs_rate {scalar_t__ bw; int /*<<< orphan*/  sgi; int /*<<< orphan*/  type; } ;
struct iwl_mvm {int dummy; } ;
struct iwl_lq_sta {scalar_t__ max_mimo2_rate_idx; scalar_t__ max_siso_rate_idx; scalar_t__ band; void* optimal_nentries; void* optimal_rates; int /*<<< orphan*/  active_legacy_rate; int /*<<< orphan*/  optimal_rate_mask; int /*<<< orphan*/  active_siso_rate; int /*<<< orphan*/  active_mimo2_rate; scalar_t__ is_vht; struct rs_rate optimal_rate; } ;
struct ieee80211_sta {int dummy; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 scalar_t__ IWL_RATE_INVALID ; 
 int /*<<< orphan*/  LQ_HT_MIMO2 ; 
 int /*<<< orphan*/  LQ_HT_SISO ; 
 int /*<<< orphan*/  LQ_LEGACY_A ; 
 int /*<<< orphan*/  LQ_LEGACY_G ; 
 int /*<<< orphan*/  LQ_VHT_MIMO2 ; 
 int /*<<< orphan*/  LQ_VHT_SISO ; 
 scalar_t__ NL80211_BAND_5GHZ ; 
 scalar_t__ RATE_MCS_CHAN_WIDTH_20 ; 
 scalar_t__ is_ht (struct rs_rate*) ; 
 scalar_t__ is_mimo (struct rs_rate*) ; 
 scalar_t__ is_siso (struct rs_rate*) ; 
 scalar_t__ is_vht (struct rs_rate*) ; 
 scalar_t__ rs_bw_from_sta_bw (struct ieee80211_sta*) ; 
 void* rs_optimal_rates_24ghz_legacy ; 
 void* rs_optimal_rates_5ghz_legacy ; 
 void* rs_optimal_rates_ht ; 
 void* rs_optimal_rates_vht ; 
 void* rs_optimal_rates_vht_20mhz ; 
 int /*<<< orphan*/  rs_sgi_allow (struct iwl_mvm*,struct ieee80211_sta*,struct rs_rate*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rs_init_optimal_rate(struct iwl_mvm *mvm,
				 struct ieee80211_sta *sta,
				 struct iwl_lq_sta *lq_sta)
{
	struct rs_rate *rate = &lq_sta->optimal_rate;

	if (lq_sta->max_mimo2_rate_idx != IWL_RATE_INVALID)
		rate->type = lq_sta->is_vht ? LQ_VHT_MIMO2 : LQ_HT_MIMO2;
	else if (lq_sta->max_siso_rate_idx != IWL_RATE_INVALID)
		rate->type = lq_sta->is_vht ? LQ_VHT_SISO : LQ_HT_SISO;
	else if (lq_sta->band == NL80211_BAND_5GHZ)
		rate->type = LQ_LEGACY_A;
	else
		rate->type = LQ_LEGACY_G;

	rate->bw = rs_bw_from_sta_bw(sta);
	rate->sgi = rs_sgi_allow(mvm, sta, rate, NULL);

	/* ANT/LDPC/STBC aren't relevant for the rate reported to userspace */

	if (is_mimo(rate)) {
		lq_sta->optimal_rate_mask = lq_sta->active_mimo2_rate;
	} else if (is_siso(rate)) {
		lq_sta->optimal_rate_mask = lq_sta->active_siso_rate;
	} else {
		lq_sta->optimal_rate_mask = lq_sta->active_legacy_rate;

		if (lq_sta->band == NL80211_BAND_5GHZ) {
			lq_sta->optimal_rates = rs_optimal_rates_5ghz_legacy;
			lq_sta->optimal_nentries =
				ARRAY_SIZE(rs_optimal_rates_5ghz_legacy);
		} else {
			lq_sta->optimal_rates = rs_optimal_rates_24ghz_legacy;
			lq_sta->optimal_nentries =
				ARRAY_SIZE(rs_optimal_rates_24ghz_legacy);
		}
	}

	if (is_vht(rate)) {
		if (rate->bw == RATE_MCS_CHAN_WIDTH_20) {
			lq_sta->optimal_rates = rs_optimal_rates_vht_20mhz;
			lq_sta->optimal_nentries =
				ARRAY_SIZE(rs_optimal_rates_vht_20mhz);
		} else {
			lq_sta->optimal_rates = rs_optimal_rates_vht;
			lq_sta->optimal_nentries =
				ARRAY_SIZE(rs_optimal_rates_vht);
		}
	} else if (is_ht(rate)) {
		lq_sta->optimal_rates = rs_optimal_rates_ht;
		lq_sta->optimal_nentries = ARRAY_SIZE(rs_optimal_rates_ht);
	}
}