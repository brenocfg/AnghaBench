#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wiphy {struct ieee80211_supported_band** bands; } ;
struct TYPE_2__ {int bw; } ;
struct rtw_efuse {TYPE_1__ hw_cap; } ;
struct rtw_dev {struct rtw_efuse efuse; } ;
struct ieee80211_supported_band {int n_channels; struct ieee80211_channel* channels; } ;
struct ieee80211_hw {struct rtw_dev* priv; } ;
struct ieee80211_channel {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEEE80211_CHAN_NO_80MHZ ; 
 size_t NL80211_BAND_2GHZ ; 
 size_t NL80211_BAND_5GHZ ; 
 int /*<<< orphan*/  RTW_CHANNEL_WIDTH_80 ; 
 struct ieee80211_hw* wiphy_to_ieee80211_hw (struct wiphy*) ; 

__attribute__((used)) static void rtw_regd_apply_hw_cap_flags(struct wiphy *wiphy)
{
	struct ieee80211_hw *hw = wiphy_to_ieee80211_hw(wiphy);
	struct ieee80211_supported_band *sband;
	struct ieee80211_channel *ch;
	struct rtw_dev *rtwdev = hw->priv;
	struct rtw_efuse *efuse = &rtwdev->efuse;
	int i;

	if (efuse->hw_cap.bw & BIT(RTW_CHANNEL_WIDTH_80))
		return;

	sband = wiphy->bands[NL80211_BAND_2GHZ];
	if (!sband)
		goto out_5g;

	for (i = 0; i < sband->n_channels; i++) {
		ch = &sband->channels[i];
		ch->flags |= IEEE80211_CHAN_NO_80MHZ;
	}

out_5g:
	sband = wiphy->bands[NL80211_BAND_5GHZ];
	if (!sband)
		return;

	for (i = 0; i < sband->n_channels; i++) {
		ch = &sband->channels[i];
		ch->flags |= IEEE80211_CHAN_NO_80MHZ;
	}
}