#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct rtl_sta_info {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  pattern_max_len; int /*<<< orphan*/  pattern_min_len; int /*<<< orphan*/  n_patterns; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int wo_wlan_mode; scalar_t__ fwctrl_lps; scalar_t__ swctrl_lps; } ;
struct rtl_priv {TYPE_3__ wowlan; TYPE_1__ psc; } ;
struct rtl_mac {struct ieee80211_supported_band* bands; } ;
struct rtl_hal {scalar_t__ macphymode; scalar_t__ bandset; scalar_t__ current_bandtype; } ;
struct rtl_efuse {int* dev_addr; } ;
struct ieee80211_supported_band {int /*<<< orphan*/  vht_cap; int /*<<< orphan*/  ht_cap; } ;
struct ieee80211_hw {int sta_data_size; TYPE_2__* wiphy; int /*<<< orphan*/  max_rate_tries; int /*<<< orphan*/  max_listen_interval; int /*<<< orphan*/  extra_tx_headroom; int /*<<< orphan*/  queues; } ;
struct TYPE_5__ {int interface_modes; int rts_threshold; TYPE_3__* wowlan; int /*<<< orphan*/  flags; struct ieee80211_supported_band** bands; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_MAX ; 
 int /*<<< orphan*/  AMPDU_AGGREGATION ; 
 scalar_t__ BAND_ON_2_4G ; 
 scalar_t__ BAND_ON_5G ; 
 scalar_t__ BAND_ON_BOTH ; 
 int BIT (int /*<<< orphan*/ ) ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  MAX_LISTEN_INTERVAL ; 
 int /*<<< orphan*/  MAX_RATE_TRIES ; 
 int /*<<< orphan*/  MAX_SUPPORT_WOL_PATTERN_NUM ; 
 int /*<<< orphan*/  MAX_WOL_PATTERN_SIZE ; 
 int /*<<< orphan*/  MFP_CAPABLE ; 
 int /*<<< orphan*/  MIN_WOL_PATTERN_SIZE ; 
 size_t NL80211_BAND_2GHZ ; 
 size_t NL80211_BAND_5GHZ ; 
 int /*<<< orphan*/  NL80211_IFTYPE_ADHOC ; 
 int /*<<< orphan*/  NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  NL80211_IFTYPE_MESH_POINT ; 
 int /*<<< orphan*/  NL80211_IFTYPE_P2P_CLIENT ; 
 int /*<<< orphan*/  NL80211_IFTYPE_P2P_GO ; 
 int /*<<< orphan*/  NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  PS_NULLFUNC_STACK ; 
 int /*<<< orphan*/  REPORTS_TX_ACK_STATUS ; 
 int /*<<< orphan*/  RTL_TX_HEADER_SIZE ; 
 int /*<<< orphan*/  RX_INCLUDES_FCS ; 
 int /*<<< orphan*/  SET_IEEE80211_PERM_ADDR (struct ieee80211_hw*,int*) ; 
 int /*<<< orphan*/  SIGNAL_DBM ; 
 scalar_t__ SINGLEMAC_SINGLEPHY ; 
 int /*<<< orphan*/  SUPPORTS_AMSDU_IN_AMPDU ; 
 int /*<<< orphan*/  SUPPORTS_DYNAMIC_PS ; 
 int /*<<< orphan*/  SUPPORTS_PS ; 
 int /*<<< orphan*/  SUPPORT_FAST_XMIT ; 
 int WAKE_ON_MAGIC_PACKET ; 
 int WAKE_ON_PATTERN_MATCH ; 
 int /*<<< orphan*/  WIPHY_FLAG_HAS_REMAIN_ON_CHANNEL ; 
 int /*<<< orphan*/  WIPHY_FLAG_IBSS_RSN ; 
 int /*<<< orphan*/  WIPHY_WOWLAN_MAGIC_PKT ; 
 int /*<<< orphan*/  _rtl_init_hw_ht_capab (struct ieee80211_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtl_init_hw_vht_capab (struct ieee80211_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_random_bytes (int*,int) ; 
 int /*<<< orphan*/  ieee80211_hw_set (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_valid_ether_addr (int*) ; 
 int /*<<< orphan*/  memcpy (struct ieee80211_supported_band*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__) ; 
 int /*<<< orphan*/  rtl_band_2ghz ; 
 int /*<<< orphan*/  rtl_band_5ghz ; 
 struct rtl_efuse* rtl_efuse (struct rtl_priv*) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void _rtl_init_mac80211(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtlpriv);
	struct rtl_mac *rtlmac = rtl_mac(rtl_priv(hw));
	struct rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	struct ieee80211_supported_band *sband;

	if (rtlhal->macphymode == SINGLEMAC_SINGLEPHY &&
	    rtlhal->bandset == BAND_ON_BOTH) {
		/* 1: 2.4 G bands */
		/* <1> use  mac->bands as mem for hw->wiphy->bands */
		sband = &(rtlmac->bands[NL80211_BAND_2GHZ]);

		/* <2> set hw->wiphy->bands[NL80211_BAND_2GHZ]
		 * to default value(1T1R) */
		memcpy(&(rtlmac->bands[NL80211_BAND_2GHZ]), &rtl_band_2ghz,
				sizeof(struct ieee80211_supported_band));

		/* <3> init ht cap base on ant_num */
		_rtl_init_hw_ht_capab(hw, &sband->ht_cap);

		/* <4> set mac->sband to wiphy->sband */
		hw->wiphy->bands[NL80211_BAND_2GHZ] = sband;

		/* 2: 5 G bands */
		/* <1> use  mac->bands as mem for hw->wiphy->bands */
		sband = &(rtlmac->bands[NL80211_BAND_5GHZ]);

		/* <2> set hw->wiphy->bands[NL80211_BAND_5GHZ]
		 * to default value(1T1R) */
		memcpy(&(rtlmac->bands[NL80211_BAND_5GHZ]), &rtl_band_5ghz,
				sizeof(struct ieee80211_supported_band));

		/* <3> init ht cap base on ant_num */
		_rtl_init_hw_ht_capab(hw, &sband->ht_cap);

		_rtl_init_hw_vht_capab(hw, &sband->vht_cap);
		/* <4> set mac->sband to wiphy->sband */
		hw->wiphy->bands[NL80211_BAND_5GHZ] = sband;
	} else {
		if (rtlhal->current_bandtype == BAND_ON_2_4G) {
			/* <1> use  mac->bands as mem for hw->wiphy->bands */
			sband = &(rtlmac->bands[NL80211_BAND_2GHZ]);

			/* <2> set hw->wiphy->bands[NL80211_BAND_2GHZ]
			 * to default value(1T1R) */
			memcpy(&(rtlmac->bands[NL80211_BAND_2GHZ]),
			       &rtl_band_2ghz,
			       sizeof(struct ieee80211_supported_band));

			/* <3> init ht cap base on ant_num */
			_rtl_init_hw_ht_capab(hw, &sband->ht_cap);

			/* <4> set mac->sband to wiphy->sband */
			hw->wiphy->bands[NL80211_BAND_2GHZ] = sband;
		} else if (rtlhal->current_bandtype == BAND_ON_5G) {
			/* <1> use  mac->bands as mem for hw->wiphy->bands */
			sband = &(rtlmac->bands[NL80211_BAND_5GHZ]);

			/* <2> set hw->wiphy->bands[NL80211_BAND_5GHZ]
			 * to default value(1T1R) */
			memcpy(&(rtlmac->bands[NL80211_BAND_5GHZ]),
			       &rtl_band_5ghz,
			       sizeof(struct ieee80211_supported_band));

			/* <3> init ht cap base on ant_num */
			_rtl_init_hw_ht_capab(hw, &sband->ht_cap);

			_rtl_init_hw_vht_capab(hw, &sband->vht_cap);
			/* <4> set mac->sband to wiphy->sband */
			hw->wiphy->bands[NL80211_BAND_5GHZ] = sband;
		} else {
			pr_err("Err BAND %d\n",
			       rtlhal->current_bandtype);
		}
	}
	/* <5> set hw caps */
	ieee80211_hw_set(hw, SIGNAL_DBM);
	ieee80211_hw_set(hw, RX_INCLUDES_FCS);
	ieee80211_hw_set(hw, AMPDU_AGGREGATION);
	ieee80211_hw_set(hw, MFP_CAPABLE);
	ieee80211_hw_set(hw, REPORTS_TX_ACK_STATUS);
	ieee80211_hw_set(hw, SUPPORTS_AMSDU_IN_AMPDU);
	ieee80211_hw_set(hw, SUPPORT_FAST_XMIT);

	/* swlps or hwlps has been set in diff chip in init_sw_vars */
	if (rtlpriv->psc.swctrl_lps) {
		ieee80211_hw_set(hw, SUPPORTS_PS);
		ieee80211_hw_set(hw, PS_NULLFUNC_STACK);
	}
	if (rtlpriv->psc.fwctrl_lps) {
		ieee80211_hw_set(hw, SUPPORTS_PS);
		ieee80211_hw_set(hw, SUPPORTS_DYNAMIC_PS);
	}
	hw->wiphy->interface_modes =
	    BIT(NL80211_IFTYPE_AP) |
	    BIT(NL80211_IFTYPE_STATION) |
	    BIT(NL80211_IFTYPE_ADHOC) |
	    BIT(NL80211_IFTYPE_MESH_POINT) |
	    BIT(NL80211_IFTYPE_P2P_CLIENT) |
	    BIT(NL80211_IFTYPE_P2P_GO);
	hw->wiphy->flags |= WIPHY_FLAG_IBSS_RSN;

	hw->wiphy->flags |= WIPHY_FLAG_HAS_REMAIN_ON_CHANNEL;

	hw->wiphy->rts_threshold = 2347;

	hw->queues = AC_MAX;
	hw->extra_tx_headroom = RTL_TX_HEADER_SIZE;

	/* TODO: Correct this value for our hw */
	hw->max_listen_interval = MAX_LISTEN_INTERVAL;
	hw->max_rate_tries = MAX_RATE_TRIES;
	/* hw->max_rates = 1; */
	hw->sta_data_size = sizeof(struct rtl_sta_info);

/* wowlan is not supported by kernel if CONFIG_PM is not defined */
#ifdef CONFIG_PM
	if (rtlpriv->psc.wo_wlan_mode) {
		if (rtlpriv->psc.wo_wlan_mode & WAKE_ON_MAGIC_PACKET)
			rtlpriv->wowlan.flags = WIPHY_WOWLAN_MAGIC_PKT;
		if (rtlpriv->psc.wo_wlan_mode & WAKE_ON_PATTERN_MATCH) {
			rtlpriv->wowlan.n_patterns =
				MAX_SUPPORT_WOL_PATTERN_NUM;
			rtlpriv->wowlan.pattern_min_len = MIN_WOL_PATTERN_SIZE;
			rtlpriv->wowlan.pattern_max_len = MAX_WOL_PATTERN_SIZE;
		}
		hw->wiphy->wowlan = &rtlpriv->wowlan;
	}
#endif

	/* <6> mac address */
	if (is_valid_ether_addr(rtlefuse->dev_addr)) {
		SET_IEEE80211_PERM_ADDR(hw, rtlefuse->dev_addr);
	} else {
		u8 rtlmac1[] = { 0x00, 0xe0, 0x4c, 0x81, 0x92, 0x00 };

		get_random_bytes((rtlmac1 + (ETH_ALEN - 1)), 1);
		SET_IEEE80211_PERM_ADDR(hw, rtlmac1);
	}
}