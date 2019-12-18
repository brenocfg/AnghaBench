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
struct ieee80211_supported_band {unsigned int n_channels; struct ieee80211_channel* channels; } ;
struct ieee80211_reg_rule {int flags; } ;
struct ieee80211_channel {int /*<<< orphan*/  flags; int /*<<< orphan*/  center_freq; } ;
typedef  enum nl80211_reg_initiator { ____Placeholder_nl80211_reg_initiator } nl80211_reg_initiator ;
typedef  enum nl80211_band { ____Placeholder_nl80211_band } nl80211_band ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_CHAN_DISABLED ; 
 int /*<<< orphan*/  IEEE80211_CHAN_NO_IR ; 
 scalar_t__ IS_ERR (struct ieee80211_reg_rule const*) ; 
 int /*<<< orphan*/  MHZ_TO_KHZ (int /*<<< orphan*/ ) ; 
 int NL80211_RRF_NO_IR ; 
 int NUM_NL80211_BANDS ; 
 struct ieee80211_reg_rule* freq_reg_info (struct wiphy*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtw_regd_apply_beaconing_flags(struct wiphy *wiphy,
					   enum nl80211_reg_initiator initiator)
{
	enum nl80211_band band;
	struct ieee80211_supported_band *sband;
	const struct ieee80211_reg_rule *reg_rule;
	struct ieee80211_channel *ch;
	unsigned int i;

	for (band = 0; band < NUM_NL80211_BANDS; band++) {
		if (!wiphy->bands[band])
			continue;

		sband = wiphy->bands[band];
		for (i = 0; i < sband->n_channels; i++) {
			ch = &sband->channels[i];

			reg_rule = freq_reg_info(wiphy,
						 MHZ_TO_KHZ(ch->center_freq));
			if (IS_ERR(reg_rule))
				continue;

			ch->flags &= ~IEEE80211_CHAN_DISABLED;

			if (!(reg_rule->flags & NL80211_RRF_NO_IR))
				ch->flags &= ~IEEE80211_CHAN_NO_IR;
		}
	}
}