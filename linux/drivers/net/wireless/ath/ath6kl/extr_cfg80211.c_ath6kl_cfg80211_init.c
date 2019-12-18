#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct wiphy {int max_remain_on_channel_duration; int interface_modes; int max_scan_ie_len; int available_antennas_tx; int available_antennas_rx; int flags; int max_sched_scan_reqs; int probe_resp_offload; int /*<<< orphan*/  features; void* max_sched_scan_ssids; int /*<<< orphan*/ * wowlan; int /*<<< orphan*/  n_cipher_suites; int /*<<< orphan*/  cipher_suites; int /*<<< orphan*/  signal_type; TYPE_4__** bands; void* max_match_sets; void* max_scan_ssids; int /*<<< orphan*/  reg_notifier; int /*<<< orphan*/  mgmt_stypes; } ;
struct TYPE_8__ {int cap; int tx_ant; int rx_ant; } ;
struct ath6kl {int wiphy_registered; struct wiphy* wiphy; int /*<<< orphan*/  fw_capabilities; TYPE_3__ hw; scalar_t__ p2p; int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int* rx_mask; } ;
struct TYPE_7__ {int ht_supported; TYPE_1__ mcs; scalar_t__ cap; } ;
struct TYPE_9__ {TYPE_2__ ht_cap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATH6KL_FW_CAPABILITY_64BIT_RATES ; 
 int /*<<< orphan*/  ATH6KL_FW_CAPABILITY_INACTIVITY_TIMEOUT ; 
 int /*<<< orphan*/  ATH6KL_FW_CAPABILITY_REGDOMAIN ; 
 int /*<<< orphan*/  ATH6KL_FW_CAPABILITY_RSN_CAP_OVERRIDE ; 
 int /*<<< orphan*/  ATH6KL_FW_CAPABILITY_SCHED_SCAN_MATCH_LIST ; 
 int /*<<< orphan*/  ATH6KL_FW_CAPABILITY_SCHED_SCAN_V2 ; 
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFG80211_SIGNAL_TYPE_MBM ; 
 int /*<<< orphan*/  CONFIG_ATH6KL_REGDOMAIN ; 
 int EINVAL ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 void* MAX_PROBED_SSIDS ; 
 size_t NL80211_BAND_2GHZ ; 
 size_t NL80211_BAND_5GHZ ; 
 int /*<<< orphan*/  NL80211_FEATURE_CELL_BASE_REG_HINTS ; 
 int /*<<< orphan*/  NL80211_FEATURE_INACTIVITY_TIMER ; 
 int /*<<< orphan*/  NL80211_IFTYPE_ADHOC ; 
 int /*<<< orphan*/  NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  NL80211_IFTYPE_P2P_CLIENT ; 
 int /*<<< orphan*/  NL80211_IFTYPE_P2P_GO ; 
 int /*<<< orphan*/  NL80211_IFTYPE_STATION ; 
 int NL80211_PROBE_RESP_OFFLOAD_SUPPORT_P2P ; 
 int NL80211_PROBE_RESP_OFFLOAD_SUPPORT_WPS ; 
 int NL80211_PROBE_RESP_OFFLOAD_SUPPORT_WPS2 ; 
 int WIPHY_FLAG_AP_PROBE_RESP_OFFLOAD ; 
 int WIPHY_FLAG_HAS_REMAIN_ON_CHANNEL ; 
 int WIPHY_FLAG_HAVE_AP_SME ; 
 int WIPHY_FLAG_SUPPORTS_FW_ROAM ; 
#define  WMI_11AGN_CAP 133 
#define  WMI_11AG_CAP 132 
#define  WMI_11AN_CAP 131 
#define  WMI_11A_CAP 130 
#define  WMI_11GN_CAP 129 
#define  WMI_11G_CAP 128 
 TYPE_4__ ath6kl_band_2ghz ; 
 TYPE_4__ ath6kl_band_5ghz ; 
 int /*<<< orphan*/  ath6kl_cfg80211_reg_notify ; 
 int /*<<< orphan*/  ath6kl_err (char*) ; 
 int /*<<< orphan*/  ath6kl_mgmt_stypes ; 
 int /*<<< orphan*/  ath6kl_wowlan_support ; 
 int /*<<< orphan*/  cipher_suites ; 
 int /*<<< orphan*/  set_wiphy_dev (struct wiphy*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wiphy_register (struct wiphy*) ; 

int ath6kl_cfg80211_init(struct ath6kl *ar)
{
	struct wiphy *wiphy = ar->wiphy;
	bool band_2gig = false, band_5gig = false, ht = false;
	int ret;

	wiphy->mgmt_stypes = ath6kl_mgmt_stypes;

	wiphy->max_remain_on_channel_duration = 5000;

	/* set device pointer for wiphy */
	set_wiphy_dev(wiphy, ar->dev);

	wiphy->interface_modes = BIT(NL80211_IFTYPE_STATION) |
				 BIT(NL80211_IFTYPE_ADHOC) |
				 BIT(NL80211_IFTYPE_AP);
	if (ar->p2p) {
		wiphy->interface_modes |= BIT(NL80211_IFTYPE_P2P_GO) |
					  BIT(NL80211_IFTYPE_P2P_CLIENT);
	}

	if (IS_ENABLED(CONFIG_ATH6KL_REGDOMAIN) &&
	    test_bit(ATH6KL_FW_CAPABILITY_REGDOMAIN, ar->fw_capabilities)) {
		wiphy->reg_notifier = ath6kl_cfg80211_reg_notify;
		ar->wiphy->features |= NL80211_FEATURE_CELL_BASE_REG_HINTS;
	}

	/* max num of ssids that can be probed during scanning */
	wiphy->max_scan_ssids = MAX_PROBED_SSIDS;

	/* max num of ssids that can be matched after scan */
	if (test_bit(ATH6KL_FW_CAPABILITY_SCHED_SCAN_MATCH_LIST,
		     ar->fw_capabilities))
		wiphy->max_match_sets = MAX_PROBED_SSIDS;

	wiphy->max_scan_ie_len = 1000; /* FIX: what is correct limit? */
	switch (ar->hw.cap) {
	case WMI_11AN_CAP:
		ht = true;
		/* fall through */
	case WMI_11A_CAP:
		band_5gig = true;
		break;
	case WMI_11GN_CAP:
		ht = true;
		/* fall through */
	case WMI_11G_CAP:
		band_2gig = true;
		break;
	case WMI_11AGN_CAP:
		ht = true;
		/* fall through */
	case WMI_11AG_CAP:
		band_2gig = true;
		band_5gig = true;
		break;
	default:
		ath6kl_err("invalid phy capability!\n");
		return -EINVAL;
	}

	/*
	 * Even if the fw has HT support, advertise HT cap only when
	 * the firmware has support to override RSN capability, otherwise
	 * 4-way handshake would fail.
	 */
	if (!(ht &&
	      test_bit(ATH6KL_FW_CAPABILITY_RSN_CAP_OVERRIDE,
		       ar->fw_capabilities))) {
		ath6kl_band_2ghz.ht_cap.cap = 0;
		ath6kl_band_2ghz.ht_cap.ht_supported = false;
		ath6kl_band_5ghz.ht_cap.cap = 0;
		ath6kl_band_5ghz.ht_cap.ht_supported = false;

		if (ht)
			ath6kl_err("Firmware lacks RSN-CAP-OVERRIDE, so HT (802.11n) is disabled.");
	}

	if (test_bit(ATH6KL_FW_CAPABILITY_64BIT_RATES,
		     ar->fw_capabilities)) {
		ath6kl_band_2ghz.ht_cap.mcs.rx_mask[0] = 0xff;
		ath6kl_band_5ghz.ht_cap.mcs.rx_mask[0] = 0xff;
		ath6kl_band_2ghz.ht_cap.mcs.rx_mask[1] = 0xff;
		ath6kl_band_5ghz.ht_cap.mcs.rx_mask[1] = 0xff;
		ar->hw.tx_ant = 0x3; /* mask, 2 antenna */
		ar->hw.rx_ant = 0x3;
	} else {
		ath6kl_band_2ghz.ht_cap.mcs.rx_mask[0] = 0xff;
		ath6kl_band_5ghz.ht_cap.mcs.rx_mask[0] = 0xff;
		ar->hw.tx_ant = 1;
		ar->hw.rx_ant = 1;
	}

	wiphy->available_antennas_tx = ar->hw.tx_ant;
	wiphy->available_antennas_rx = ar->hw.rx_ant;

	if (band_2gig)
		wiphy->bands[NL80211_BAND_2GHZ] = &ath6kl_band_2ghz;
	if (band_5gig)
		wiphy->bands[NL80211_BAND_5GHZ] = &ath6kl_band_5ghz;

	wiphy->signal_type = CFG80211_SIGNAL_TYPE_MBM;

	wiphy->cipher_suites = cipher_suites;
	wiphy->n_cipher_suites = ARRAY_SIZE(cipher_suites);

#ifdef CONFIG_PM
	wiphy->wowlan = &ath6kl_wowlan_support;
#endif

	wiphy->max_sched_scan_ssids = MAX_PROBED_SSIDS;

	ar->wiphy->flags |= WIPHY_FLAG_SUPPORTS_FW_ROAM |
			    WIPHY_FLAG_HAVE_AP_SME |
			    WIPHY_FLAG_HAS_REMAIN_ON_CHANNEL |
			    WIPHY_FLAG_AP_PROBE_RESP_OFFLOAD;

	if (test_bit(ATH6KL_FW_CAPABILITY_SCHED_SCAN_V2, ar->fw_capabilities))
		ar->wiphy->max_sched_scan_reqs = 1;

	if (test_bit(ATH6KL_FW_CAPABILITY_INACTIVITY_TIMEOUT,
		     ar->fw_capabilities))
		ar->wiphy->features |= NL80211_FEATURE_INACTIVITY_TIMER;

	ar->wiphy->probe_resp_offload =
		NL80211_PROBE_RESP_OFFLOAD_SUPPORT_WPS |
		NL80211_PROBE_RESP_OFFLOAD_SUPPORT_WPS2 |
		NL80211_PROBE_RESP_OFFLOAD_SUPPORT_P2P;

	ret = wiphy_register(wiphy);
	if (ret < 0) {
		ath6kl_err("couldn't register wiphy device\n");
		return ret;
	}

	ar->wiphy_registered = true;

	return 0;
}