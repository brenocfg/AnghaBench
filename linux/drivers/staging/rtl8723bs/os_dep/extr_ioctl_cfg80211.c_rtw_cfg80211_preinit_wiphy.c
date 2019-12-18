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
struct wiphy {int interface_modes; int software_iftypes; int flags; int max_sched_scan_reqs; int /*<<< orphan*/ * wowlan; int /*<<< orphan*/  max_sched_scan_ssids; int /*<<< orphan*/ * bands; int /*<<< orphan*/  n_cipher_suites; int /*<<< orphan*/  cipher_suites; int /*<<< orphan*/  mgmt_stypes; int /*<<< orphan*/  max_remain_on_channel_duration; int /*<<< orphan*/  max_num_pmkids; int /*<<< orphan*/  max_scan_ie_len; int /*<<< orphan*/  max_scan_ssids; int /*<<< orphan*/  signal_type; } ;
struct TYPE_2__ {scalar_t__ power_mgnt; } ;
struct adapter {TYPE_1__ registrypriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFG80211_SIGNAL_TYPE_MBM ; 
 int /*<<< orphan*/  MAX_PNO_LIST_COUNT ; 
 size_t NL80211_BAND_2GHZ ; 
 int /*<<< orphan*/  NL80211_IFTYPE_ADHOC ; 
 int /*<<< orphan*/  NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  NL80211_IFTYPE_MONITOR ; 
 int /*<<< orphan*/  NL80211_IFTYPE_STATION ; 
 scalar_t__ PS_MODE_ACTIVE ; 
 int /*<<< orphan*/  RTW_MAX_NUM_PMKIDS ; 
 int /*<<< orphan*/  RTW_MAX_REMAIN_ON_CHANNEL_DURATION ; 
 int /*<<< orphan*/  RTW_SCAN_IE_LEN_MAX ; 
 int /*<<< orphan*/  RTW_SSID_SCAN_AMOUNT ; 
 int WIPHY_FLAG_HAS_REMAIN_ON_CHANNEL ; 
 int WIPHY_FLAG_HAVE_AP_SME ; 
 int WIPHY_FLAG_OFFCHAN_TX ; 
 int WIPHY_FLAG_PS_ON_BY_DEFAULT ; 
 int /*<<< orphan*/  rtw_cfg80211_default_mgmt_stypes ; 
 int /*<<< orphan*/  rtw_cipher_suites ; 
 int /*<<< orphan*/  rtw_spt_band_alloc (size_t) ; 
 int /*<<< orphan*/  wowlan_stub ; 

__attribute__((used)) static void rtw_cfg80211_preinit_wiphy(struct adapter *padapter, struct wiphy *wiphy)
{

	wiphy->signal_type = CFG80211_SIGNAL_TYPE_MBM;

	wiphy->max_scan_ssids = RTW_SSID_SCAN_AMOUNT;
	wiphy->max_scan_ie_len = RTW_SCAN_IE_LEN_MAX;
	wiphy->max_num_pmkids = RTW_MAX_NUM_PMKIDS;

	wiphy->max_remain_on_channel_duration = RTW_MAX_REMAIN_ON_CHANNEL_DURATION;

	wiphy->interface_modes =	BIT(NL80211_IFTYPE_STATION)
								| BIT(NL80211_IFTYPE_ADHOC)
								| BIT(NL80211_IFTYPE_AP)
								| BIT(NL80211_IFTYPE_MONITOR)
								;

	wiphy->mgmt_stypes = rtw_cfg80211_default_mgmt_stypes;

	wiphy->software_iftypes |= BIT(NL80211_IFTYPE_MONITOR);

	wiphy->cipher_suites = rtw_cipher_suites;
	wiphy->n_cipher_suites = ARRAY_SIZE(rtw_cipher_suites);

	/* if (padapter->registrypriv.wireless_mode & WIRELESS_11G) */
	wiphy->bands[NL80211_BAND_2GHZ] = rtw_spt_band_alloc(NL80211_BAND_2GHZ);

	wiphy->flags |= WIPHY_FLAG_HAS_REMAIN_ON_CHANNEL;
	wiphy->flags |= WIPHY_FLAG_OFFCHAN_TX | WIPHY_FLAG_HAVE_AP_SME;

#if defined(CONFIG_PM)
	wiphy->max_sched_scan_reqs = 1;
#ifdef CONFIG_PNO_SUPPORT
	wiphy->max_sched_scan_ssids = MAX_PNO_LIST_COUNT;
#endif
#endif

#if defined(CONFIG_PM)
	wiphy->wowlan = &wowlan_stub;
#endif

	if (padapter->registrypriv.power_mgnt != PS_MODE_ACTIVE)
		wiphy->flags |= WIPHY_FLAG_PS_ON_BY_DEFAULT;
	else
		wiphy->flags &= ~WIPHY_FLAG_PS_ON_BY_DEFAULT;
}