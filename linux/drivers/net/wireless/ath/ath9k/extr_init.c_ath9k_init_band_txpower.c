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
struct ieee80211_supported_band {int n_channels; struct ieee80211_channel* channels; } ;
struct ieee80211_channel {size_t hw_value; } ;
struct cfg80211_chan_def {int dummy; } ;
struct ath_softc {int /*<<< orphan*/  hw; struct ath_hw* sc_ah; } ;
struct ath_hw {int /*<<< orphan*/ * channels; int /*<<< orphan*/ * curchan; } ;
struct ath_common {struct ieee80211_supported_band* sbands; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_COMBINED_POWER ; 
 int /*<<< orphan*/  NL80211_CHAN_HT20 ; 
 int /*<<< orphan*/  ath9k_cmn_get_channel (int /*<<< orphan*/ ,struct ath_hw*,struct cfg80211_chan_def*) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_set_txpowerlimit (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cfg80211_chandef_create (struct cfg80211_chan_def*,struct ieee80211_channel*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath9k_init_band_txpower(struct ath_softc *sc, int band)
{
	struct ieee80211_supported_band *sband;
	struct ieee80211_channel *chan;
	struct ath_hw *ah = sc->sc_ah;
	struct ath_common *common = ath9k_hw_common(ah);
	struct cfg80211_chan_def chandef;
	int i;

	sband = &common->sbands[band];
	for (i = 0; i < sband->n_channels; i++) {
		chan = &sband->channels[i];
		ah->curchan = &ah->channels[chan->hw_value];
		cfg80211_chandef_create(&chandef, chan, NL80211_CHAN_HT20);
		ath9k_cmn_get_channel(sc->hw, ah, &chandef);
		ath9k_hw_set_txpowerlimit(ah, MAX_COMBINED_POWER, true);
	}
}