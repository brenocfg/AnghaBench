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
struct wiphy {struct ieee80211_supported_band** bands; } ;
struct ieee80211_supported_band {int n_channels; struct ieee80211_channel* channels; } ;
struct ieee80211_reg_rule {int flags; } ;
struct ieee80211_channel {int flags; scalar_t__ beacon_found; int /*<<< orphan*/  center_freq; } ;
typedef  enum nl80211_reg_initiator { ____Placeholder_nl80211_reg_initiator } nl80211_reg_initiator ;

/* Variables and functions */
 int IEEE80211_CHAN_DISABLED ; 
 int IEEE80211_CHAN_NO_IR ; 
 int IEEE80211_CHAN_RADAR ; 
 scalar_t__ IS_ERR (struct ieee80211_reg_rule const*) ; 
 int /*<<< orphan*/  MHZ_TO_KHZ (int /*<<< orphan*/ ) ; 
 int NL80211_REGDOM_SET_BY_COUNTRY_IE ; 
 int NL80211_RRF_NO_IR ; 
 int NUM_NL80211_BANDS ; 
 struct ieee80211_reg_rule* freq_reg_info (struct wiphy*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
brcms_reg_apply_beaconing_flags(struct wiphy *wiphy,
				enum nl80211_reg_initiator initiator)
{
	struct ieee80211_supported_band *sband;
	struct ieee80211_channel *ch;
	const struct ieee80211_reg_rule *rule;
	int band, i;

	for (band = 0; band < NUM_NL80211_BANDS; band++) {
		sband = wiphy->bands[band];
		if (!sband)
			continue;

		for (i = 0; i < sband->n_channels; i++) {
			ch = &sband->channels[i];

			if (ch->flags &
			    (IEEE80211_CHAN_DISABLED | IEEE80211_CHAN_RADAR))
				continue;

			if (initiator == NL80211_REGDOM_SET_BY_COUNTRY_IE) {
				rule = freq_reg_info(wiphy,
						     MHZ_TO_KHZ(ch->center_freq));
				if (IS_ERR(rule))
					continue;

				if (!(rule->flags & NL80211_RRF_NO_IR))
					ch->flags &= ~IEEE80211_CHAN_NO_IR;
			} else if (ch->beacon_found) {
				ch->flags &= ~IEEE80211_CHAN_NO_IR;
			}
		}
	}
}