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
struct rtw_dev {int dummy; } ;
struct rtw_chip_info {int band; scalar_t__ vht_supported; scalar_t__ ht_supported; } ;
struct ieee80211_supported_band {int /*<<< orphan*/  vht_cap; int /*<<< orphan*/  ht_cap; } ;
struct ieee80211_hw {TYPE_1__* wiphy; struct rtw_dev* priv; } ;
struct TYPE_2__ {struct ieee80211_supported_band** bands; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t NL80211_BAND_2GHZ ; 
 size_t NL80211_BAND_5GHZ ; 
 int RTW_BAND_2G ; 
 int RTW_BAND_5G ; 
 int /*<<< orphan*/  kfree (struct ieee80211_supported_band*) ; 
 struct ieee80211_supported_band* kmemdup (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_band_2ghz ; 
 int /*<<< orphan*/  rtw_band_5ghz ; 
 int /*<<< orphan*/  rtw_err (struct rtw_dev*,char*) ; 
 int /*<<< orphan*/  rtw_init_ht_cap (struct rtw_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_init_vht_cap (struct rtw_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rtw_set_supported_band(struct ieee80211_hw *hw,
				   struct rtw_chip_info *chip)
{
	struct rtw_dev *rtwdev = hw->priv;
	struct ieee80211_supported_band *sband;

	if (chip->band & RTW_BAND_2G) {
		sband = kmemdup(&rtw_band_2ghz, sizeof(*sband), GFP_KERNEL);
		if (!sband)
			goto err_out;
		if (chip->ht_supported)
			rtw_init_ht_cap(rtwdev, &sband->ht_cap);
		hw->wiphy->bands[NL80211_BAND_2GHZ] = sband;
	}

	if (chip->band & RTW_BAND_5G) {
		sband = kmemdup(&rtw_band_5ghz, sizeof(*sband), GFP_KERNEL);
		if (!sband)
			goto err_out;
		if (chip->ht_supported)
			rtw_init_ht_cap(rtwdev, &sband->ht_cap);
		if (chip->vht_supported)
			rtw_init_vht_cap(rtwdev, &sband->vht_cap);
		hw->wiphy->bands[NL80211_BAND_5GHZ] = sband;
	}

	return;

err_out:
	rtw_err(rtwdev, "failed to set supported band\n");
	kfree(sband);
}