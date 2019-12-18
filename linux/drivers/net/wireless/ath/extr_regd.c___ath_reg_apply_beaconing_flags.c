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
struct wiphy {int dummy; } ;
struct ieee80211_channel {int flags; int /*<<< orphan*/  beacon_found; int /*<<< orphan*/  center_freq; } ;
struct ath_regulatory {int dummy; } ;
typedef  enum nl80211_reg_initiator { ____Placeholder_nl80211_reg_initiator } nl80211_reg_initiator ;

/* Variables and functions */
 int IEEE80211_CHAN_NO_IR ; 
 int IEEE80211_CHAN_RADAR ; 
#define  NL80211_REGDOM_SET_BY_COUNTRY_IE 129 
#define  NL80211_REGDOM_SET_BY_USER 128 
 int /*<<< orphan*/  ath_force_clear_no_ir_chan (struct wiphy*,struct ieee80211_channel*) ; 
 scalar_t__ ath_is_radar_freq (int /*<<< orphan*/ ,struct ath_regulatory*) ; 
 int /*<<< orphan*/  ath_reg_dyn_country_user_allow (struct ath_regulatory*) ; 

__attribute__((used)) static void
__ath_reg_apply_beaconing_flags(struct wiphy *wiphy,
				struct ath_regulatory *reg,
				enum nl80211_reg_initiator initiator,
				struct ieee80211_channel *ch)
{
	if (ath_is_radar_freq(ch->center_freq, reg) ||
	    (ch->flags & IEEE80211_CHAN_RADAR))
		return;

	switch (initiator) {
	case NL80211_REGDOM_SET_BY_COUNTRY_IE:
		ath_force_clear_no_ir_chan(wiphy, ch);
		break;
	case NL80211_REGDOM_SET_BY_USER:
		if (ath_reg_dyn_country_user_allow(reg))
			ath_force_clear_no_ir_chan(wiphy, ch);
		break;
	default:
		if (ch->beacon_found)
			ch->flags &= ~IEEE80211_CHAN_NO_IR;
	}
}