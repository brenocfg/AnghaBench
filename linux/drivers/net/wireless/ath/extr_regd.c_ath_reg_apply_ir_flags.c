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
struct ieee80211_supported_band {int dummy; } ;
struct ath_regulatory {int dummy; } ;
typedef  enum nl80211_reg_initiator { ____Placeholder_nl80211_reg_initiator } nl80211_reg_initiator ;

/* Variables and functions */
 size_t NL80211_BAND_2GHZ ; 
#define  NL80211_REGDOM_SET_BY_COUNTRY_IE 129 
#define  NL80211_REGDOM_SET_BY_USER 128 
 int /*<<< orphan*/  ath_force_clear_no_ir_freq (struct wiphy*,int) ; 
 int /*<<< orphan*/  ath_force_no_ir_freq (struct wiphy*,int) ; 
 int /*<<< orphan*/  ath_reg_dyn_country_user_allow (struct ath_regulatory*) ; 

__attribute__((used)) static void
ath_reg_apply_ir_flags(struct wiphy *wiphy,
		       struct ath_regulatory *reg,
		       enum nl80211_reg_initiator initiator)
{
	struct ieee80211_supported_band *sband;

	sband = wiphy->bands[NL80211_BAND_2GHZ];
	if (!sband)
		return;

	switch(initiator) {
	case NL80211_REGDOM_SET_BY_COUNTRY_IE:
		ath_force_clear_no_ir_freq(wiphy, 2467);
		ath_force_clear_no_ir_freq(wiphy, 2472);
		break;
	case NL80211_REGDOM_SET_BY_USER:
		if (!ath_reg_dyn_country_user_allow(reg))
			break;
		ath_force_clear_no_ir_freq(wiphy, 2467);
		ath_force_clear_no_ir_freq(wiphy, 2472);
		break;
	default:
		ath_force_no_ir_freq(wiphy, 2467);
		ath_force_no_ir_freq(wiphy, 2472);
	}
}