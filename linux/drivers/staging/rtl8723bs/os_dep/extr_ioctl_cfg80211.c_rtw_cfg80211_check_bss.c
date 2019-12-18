#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_9__ {int /*<<< orphan*/  SsidLength; int /*<<< orphan*/  Ssid; } ;
struct TYPE_8__ {int /*<<< orphan*/  DSConfig; } ;
struct wlan_bssid_ex {TYPE_4__ Ssid; int /*<<< orphan*/  MacAddress; TYPE_3__ Configuration; } ;
struct ieee80211_channel {int dummy; } ;
struct cfg80211_bss {int dummy; } ;
struct TYPE_6__ {struct wlan_bssid_ex network; } ;
struct TYPE_7__ {TYPE_1__ mlmext_info; } ;
struct adapter {TYPE_5__* rtw_wdev; TYPE_2__ mlmeextpriv; } ;
struct TYPE_10__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NL80211_BAND_2GHZ ; 
 int /*<<< orphan*/  WLAN_CAPABILITY_ESS ; 
 struct cfg80211_bss* cfg80211_get_bss (int /*<<< orphan*/ ,struct ieee80211_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cfg80211_put_bss (int /*<<< orphan*/ ,struct cfg80211_bss*) ; 
 struct ieee80211_channel* ieee80211_get_channel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_ieee80211_channel_to_frequency (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rtw_cfg80211_check_bss(struct adapter *padapter)
{
	struct wlan_bssid_ex  *pnetwork = &(padapter->mlmeextpriv.mlmext_info.network);
	struct cfg80211_bss *bss = NULL;
	struct ieee80211_channel *notify_channel = NULL;
	u32 freq;

	if (!(pnetwork) || !(padapter->rtw_wdev))
		return false;

	freq = rtw_ieee80211_channel_to_frequency(pnetwork->Configuration.DSConfig, NL80211_BAND_2GHZ);

	notify_channel = ieee80211_get_channel(padapter->rtw_wdev->wiphy, freq);
	bss = cfg80211_get_bss(padapter->rtw_wdev->wiphy, notify_channel,
			pnetwork->MacAddress, pnetwork->Ssid.Ssid,
			pnetwork->Ssid.SsidLength,
			WLAN_CAPABILITY_ESS, WLAN_CAPABILITY_ESS);

	cfg80211_put_bss(padapter->rtw_wdev->wiphy, bss);

	return	(bss!= NULL);
}