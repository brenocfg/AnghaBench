#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ieee80211_supported_band {int n_bitrates; TYPE_6__* bitrates; } ;
struct ieee80211_sta {int* supp_rates; } ;
struct ieee80211_bss_conf {int /*<<< orphan*/  bssid; } ;
struct ar5523 {TYPE_5__* hw; int /*<<< orphan*/  vif; } ;
struct TYPE_12__ {int bitrate; } ;
struct TYPE_9__ {TYPE_2__* chan; } ;
struct TYPE_10__ {TYPE_3__ chandef; } ;
struct TYPE_11__ {TYPE_4__ conf; TYPE_1__* wiphy; } ;
struct TYPE_8__ {size_t band; } ;
struct TYPE_7__ {struct ieee80211_supported_band** bands; } ;

/* Variables and functions */
 int WLAN_MODE_11b ; 
 int WLAN_MODE_11g ; 
 int /*<<< orphan*/  ar5523_info (struct ar5523*,char*) ; 
 struct ieee80211_sta* ieee80211_find_sta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ar5523_get_wlan_mode(struct ar5523 *ar,
				struct ieee80211_bss_conf *bss_conf)
{
	struct ieee80211_supported_band *band;
	int bit;
	struct ieee80211_sta *sta;
	u32 sta_rate_set;

	band = ar->hw->wiphy->bands[ar->hw->conf.chandef.chan->band];
	sta = ieee80211_find_sta(ar->vif, bss_conf->bssid);
	if (!sta) {
		ar5523_info(ar, "STA not found!\n");
		return WLAN_MODE_11b;
	}
	sta_rate_set = sta->supp_rates[ar->hw->conf.chandef.chan->band];

	for (bit = 0; bit < band->n_bitrates; bit++) {
		if (sta_rate_set & 1) {
			int rate = band->bitrates[bit].bitrate;
			switch (rate) {
			case 60:
			case 90:
			case 120:
			case 180:
			case 240:
			case 360:
			case 480:
			case 540:
				return WLAN_MODE_11g;
			}
		}
		sta_rate_set >>= 1;
	}
	return WLAN_MODE_11b;
}