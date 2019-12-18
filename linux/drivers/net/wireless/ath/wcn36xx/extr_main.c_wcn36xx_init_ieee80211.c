#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct wcn36xx_vif {int dummy; } ;
struct wcn36xx_sta {int dummy; } ;
struct wcn36xx {scalar_t__ rf_id; TYPE_2__* hw; int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int max_listen_interval; int queues; int sta_data_size; int vif_data_size; TYPE_1__* wiphy; } ;
struct TYPE_4__ {int interface_modes; int /*<<< orphan*/ * wowlan; int /*<<< orphan*/  n_cipher_suites; int /*<<< orphan*/  const* cipher_suites; int /*<<< orphan*/  max_scan_ie_len; int /*<<< orphan*/  max_scan_ssids; int /*<<< orphan*/ ** bands; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMPDU_AGGREGATION ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/  const*) ; 
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONNECTION_MONITOR ; 
 int /*<<< orphan*/  HAS_RATE_CONTROL ; 
 size_t NL80211_BAND_2GHZ ; 
 size_t NL80211_BAND_5GHZ ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_CQM_RSSI_LIST ; 
 int /*<<< orphan*/  NL80211_IFTYPE_ADHOC ; 
 int /*<<< orphan*/  NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  NL80211_IFTYPE_MESH_POINT ; 
 int /*<<< orphan*/  NL80211_IFTYPE_STATION ; 
 scalar_t__ RF_IRIS_WCN3620 ; 
 int /*<<< orphan*/  SET_IEEE80211_DEV (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGNAL_DBM ; 
 int /*<<< orphan*/  SINGLE_SCAN_ON_ALL_BANDS ; 
 int /*<<< orphan*/  SUPPORTS_PS ; 
 int /*<<< orphan*/  TIMING_BEACON_ONLY ; 
 int /*<<< orphan*/  WCN36XX_MAX_SCAN_IE_LEN ; 
 int /*<<< orphan*/  WCN36XX_MAX_SCAN_SSIDS ; 
#define  WLAN_CIPHER_SUITE_CCMP 131 
#define  WLAN_CIPHER_SUITE_TKIP 130 
#define  WLAN_CIPHER_SUITE_WEP104 129 
#define  WLAN_CIPHER_SUITE_WEP40 128 
 int /*<<< orphan*/  ieee80211_hw_set (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcn_band_2ghz ; 
 int /*<<< orphan*/  wcn_band_5ghz ; 
 int /*<<< orphan*/  wiphy_ext_feature_set (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wowlan_support ; 

__attribute__((used)) static int wcn36xx_init_ieee80211(struct wcn36xx *wcn)
{
	static const u32 cipher_suites[] = {
		WLAN_CIPHER_SUITE_WEP40,
		WLAN_CIPHER_SUITE_WEP104,
		WLAN_CIPHER_SUITE_TKIP,
		WLAN_CIPHER_SUITE_CCMP,
	};

	ieee80211_hw_set(wcn->hw, TIMING_BEACON_ONLY);
	ieee80211_hw_set(wcn->hw, AMPDU_AGGREGATION);
	ieee80211_hw_set(wcn->hw, CONNECTION_MONITOR);
	ieee80211_hw_set(wcn->hw, SUPPORTS_PS);
	ieee80211_hw_set(wcn->hw, SIGNAL_DBM);
	ieee80211_hw_set(wcn->hw, HAS_RATE_CONTROL);
	ieee80211_hw_set(wcn->hw, SINGLE_SCAN_ON_ALL_BANDS);

	wcn->hw->wiphy->interface_modes = BIT(NL80211_IFTYPE_STATION) |
		BIT(NL80211_IFTYPE_AP) |
		BIT(NL80211_IFTYPE_ADHOC) |
		BIT(NL80211_IFTYPE_MESH_POINT);

	wcn->hw->wiphy->bands[NL80211_BAND_2GHZ] = &wcn_band_2ghz;
	if (wcn->rf_id != RF_IRIS_WCN3620)
		wcn->hw->wiphy->bands[NL80211_BAND_5GHZ] = &wcn_band_5ghz;

	wcn->hw->wiphy->max_scan_ssids = WCN36XX_MAX_SCAN_SSIDS;
	wcn->hw->wiphy->max_scan_ie_len = WCN36XX_MAX_SCAN_IE_LEN;

	wcn->hw->wiphy->cipher_suites = cipher_suites;
	wcn->hw->wiphy->n_cipher_suites = ARRAY_SIZE(cipher_suites);

#ifdef CONFIG_PM
	wcn->hw->wiphy->wowlan = &wowlan_support;
#endif

	wcn->hw->max_listen_interval = 200;

	wcn->hw->queues = 4;

	SET_IEEE80211_DEV(wcn->hw, wcn->dev);

	wcn->hw->sta_data_size = sizeof(struct wcn36xx_sta);
	wcn->hw->vif_data_size = sizeof(struct wcn36xx_vif);

	wiphy_ext_feature_set(wcn->hw->wiphy,
			      NL80211_EXT_FEATURE_CQM_RSSI_LIST);

	return 0;
}