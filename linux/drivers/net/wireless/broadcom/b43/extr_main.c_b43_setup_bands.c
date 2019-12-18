#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_hw {TYPE_2__* wiphy; } ;
struct b43_phy {int radio_ver; int radio_rev; scalar_t__ type; int supports_2ghz; int supports_5ghz; } ;
struct b43_wldev {struct b43_phy phy; TYPE_1__* wl; } ;
struct TYPE_4__ {int /*<<< orphan*/ ** bands; } ;
struct TYPE_3__ {struct ieee80211_hw* hw; } ;

/* Variables and functions */
 scalar_t__ B43_PHYTYPE_N ; 
 size_t NL80211_BAND_2GHZ ; 
 size_t NL80211_BAND_5GHZ ; 
 int /*<<< orphan*/  b43_band_2GHz ; 
 int /*<<< orphan*/  b43_band_2ghz_limited ; 
 int /*<<< orphan*/  b43_band_5GHz_aphy ; 
 int /*<<< orphan*/  b43_band_5GHz_nphy ; 
 int /*<<< orphan*/  b43_band_5GHz_nphy_limited ; 

__attribute__((used)) static int b43_setup_bands(struct b43_wldev *dev,
			   bool have_2ghz_phy, bool have_5ghz_phy)
{
	struct ieee80211_hw *hw = dev->wl->hw;
	struct b43_phy *phy = &dev->phy;
	bool limited_2g;
	bool limited_5g;

	/* We don't support all 2 GHz channels on some devices */
	limited_2g = phy->radio_ver == 0x2057 &&
		     (phy->radio_rev == 9 || phy->radio_rev == 14);
	limited_5g = phy->radio_ver == 0x2057 &&
		     phy->radio_rev == 9;

	if (have_2ghz_phy)
		hw->wiphy->bands[NL80211_BAND_2GHZ] = limited_2g ?
			&b43_band_2ghz_limited : &b43_band_2GHz;
	if (dev->phy.type == B43_PHYTYPE_N) {
		if (have_5ghz_phy)
			hw->wiphy->bands[NL80211_BAND_5GHZ] = limited_5g ?
				&b43_band_5GHz_nphy_limited :
				&b43_band_5GHz_nphy;
	} else {
		if (have_5ghz_phy)
			hw->wiphy->bands[NL80211_BAND_5GHZ] = &b43_band_5GHz_aphy;
	}

	dev->phy.supports_2ghz = have_2ghz_phy;
	dev->phy.supports_5ghz = have_5ghz_phy;

	return 0;
}