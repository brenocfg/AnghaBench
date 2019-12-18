#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wiphy {int max_scan_ssids; int max_remain_on_channel_duration; int max_num_csa_counters; int flags; int probe_resp_offload; int regulatory_flags; int /*<<< orphan*/  hw_version; int /*<<< orphan*/  fw_version; scalar_t__ extended_capabilities_len; int /*<<< orphan*/  extended_capabilities_mask; int /*<<< orphan*/  extended_capabilities; int /*<<< orphan*/  reg_notifier; scalar_t__ wowlan; int /*<<< orphan*/  features; int /*<<< orphan*/  perm_addr; int /*<<< orphan*/ * vht_capa_mod_mask; int /*<<< orphan*/ * ht_capa_mod_mask; int /*<<< orphan*/  max_ap_assoc_sta; int /*<<< orphan*/  available_antennas_rx; int /*<<< orphan*/  available_antennas_tx; int /*<<< orphan*/  signal_type; int /*<<< orphan*/  n_cipher_suites; int /*<<< orphan*/  cipher_suites; int /*<<< orphan*/  max_acl_mac_addrs; int /*<<< orphan*/  mgmt_stypes; int /*<<< orphan*/  max_scan_ie_len; int /*<<< orphan*/  coverage_class; int /*<<< orphan*/  retry_long; int /*<<< orphan*/  retry_short; int /*<<< orphan*/  rts_threshold; int /*<<< orphan*/  frag_threshold; } ;
struct qtnf_mac_info {scalar_t__ extended_capabilities_len; int /*<<< orphan*/  extended_capabilities_mask; int /*<<< orphan*/  extended_capabilities; scalar_t__ wowlan; int /*<<< orphan*/  vht_cap_mod_mask; int /*<<< orphan*/  ht_cap_mod_mask; int /*<<< orphan*/  max_ap_assoc_sta; int /*<<< orphan*/  num_rx_chain; int /*<<< orphan*/  num_tx_chain; int /*<<< orphan*/  max_acl_mac_addrs; int /*<<< orphan*/  coverage_class; int /*<<< orphan*/  lretry_limit; int /*<<< orphan*/  sretry_limit; int /*<<< orphan*/  rts_thr; int /*<<< orphan*/  frag_thr; } ;
struct qtnf_wmac {TYPE_1__* rd; struct qtnf_mac_info macinfo; int /*<<< orphan*/  macaddr; } ;
struct qtnf_hw_info {int max_scan_ssids; int hw_capab; int /*<<< orphan*/  hw_version; int /*<<< orphan*/  fw_version; } ;
struct TYPE_3__ {char* alpha2; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFG80211_SIGNAL_TYPE_MBM ; 
 int EFAULT ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_DFS_OFFLOAD ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_SET_SCAN_DWELL ; 
 int /*<<< orphan*/  NL80211_FEATURE_INACTIVITY_TIMER ; 
 int /*<<< orphan*/  NL80211_FEATURE_NEED_OBSS_SCAN ; 
 int /*<<< orphan*/  NL80211_FEATURE_SAE ; 
 int /*<<< orphan*/  NL80211_FEATURE_SCAN_RANDOM_MAC_ADDR ; 
 int NL80211_PROBE_RESP_OFFLOAD_SUPPORT_WPS ; 
 int NL80211_PROBE_RESP_OFFLOAD_SUPPORT_WPS2 ; 
 int QLINK_HW_CAPAB_DFS_OFFLOAD ; 
 int QLINK_HW_CAPAB_OBSS_SCAN ; 
 int QLINK_HW_CAPAB_REG_UPDATE ; 
 int QLINK_HW_CAPAB_SAE ; 
 int QLINK_HW_CAPAB_SCAN_DWELL ; 
 int QLINK_HW_CAPAB_SCAN_RANDOM_MAC_ADDR ; 
 int QLINK_HW_CAPAB_STA_INACT_TIMEOUT ; 
 int /*<<< orphan*/  QTNF_MAX_VSIE_LEN ; 
 int REGULATORY_CUSTOM_REG ; 
 int REGULATORY_STRICT_REG ; 
 int REGULATORY_WIPHY_SELF_MANAGED ; 
 int WIPHY_FLAG_4ADDR_STATION ; 
 int WIPHY_FLAG_AP_PROBE_RESP_OFFLOAD ; 
 int WIPHY_FLAG_AP_UAPSD ; 
 int WIPHY_FLAG_HAS_CHANNEL_SWITCH ; 
 int WIPHY_FLAG_HAVE_AP_SME ; 
 int WIPHY_FLAG_NETNS_OK ; 
 int WIPHY_FLAG_PS_ON_BY_DEFAULT ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ isalpha (char) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 struct wiphy* priv_to_wiphy (struct qtnf_wmac*) ; 
 int /*<<< orphan*/  qtnf_cfg80211_reg_notifier ; 
 int /*<<< orphan*/  qtnf_cipher_suites ; 
 int /*<<< orphan*/  qtnf_mgmt_stypes ; 
 int qtnf_wiphy_setup_if_comb (struct wiphy*,struct qtnf_mac_info*) ; 
 int regulatory_hint (struct wiphy*,char*) ; 
 int regulatory_set_wiphy_regd (struct wiphy*,TYPE_1__*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wiphy_apply_custom_regulatory (struct wiphy*,TYPE_1__*) ; 
 int /*<<< orphan*/  wiphy_ext_feature_set (struct wiphy*,int /*<<< orphan*/ ) ; 
 int wiphy_register (struct wiphy*) ; 

int qtnf_wiphy_register(struct qtnf_hw_info *hw_info, struct qtnf_wmac *mac)
{
	struct wiphy *wiphy = priv_to_wiphy(mac);
	struct qtnf_mac_info *macinfo = &mac->macinfo;
	int ret;
	bool regdomain_is_known;

	if (!wiphy) {
		pr_err("invalid wiphy pointer\n");
		return -EFAULT;
	}

	wiphy->frag_threshold = macinfo->frag_thr;
	wiphy->rts_threshold = macinfo->rts_thr;
	wiphy->retry_short = macinfo->sretry_limit;
	wiphy->retry_long = macinfo->lretry_limit;
	wiphy->coverage_class = macinfo->coverage_class;

	wiphy->max_scan_ssids =
		(hw_info->max_scan_ssids) ? hw_info->max_scan_ssids : 1;
	wiphy->max_scan_ie_len = QTNF_MAX_VSIE_LEN;
	wiphy->mgmt_stypes = qtnf_mgmt_stypes;
	wiphy->max_remain_on_channel_duration = 5000;
	wiphy->max_acl_mac_addrs = macinfo->max_acl_mac_addrs;
	wiphy->max_num_csa_counters = 2;

	ret = qtnf_wiphy_setup_if_comb(wiphy, macinfo);
	if (ret)
		goto out;

	/* Initialize cipher suits */
	wiphy->cipher_suites = qtnf_cipher_suites;
	wiphy->n_cipher_suites = ARRAY_SIZE(qtnf_cipher_suites);
	wiphy->signal_type = CFG80211_SIGNAL_TYPE_MBM;
	wiphy->flags |= WIPHY_FLAG_HAVE_AP_SME |
			WIPHY_FLAG_AP_PROBE_RESP_OFFLOAD |
			WIPHY_FLAG_AP_UAPSD |
			WIPHY_FLAG_HAS_CHANNEL_SWITCH |
			WIPHY_FLAG_4ADDR_STATION |
			WIPHY_FLAG_NETNS_OK;
	wiphy->flags &= ~WIPHY_FLAG_PS_ON_BY_DEFAULT;

	if (hw_info->hw_capab & QLINK_HW_CAPAB_DFS_OFFLOAD)
		wiphy_ext_feature_set(wiphy, NL80211_EXT_FEATURE_DFS_OFFLOAD);

	if (hw_info->hw_capab & QLINK_HW_CAPAB_SCAN_DWELL)
		wiphy_ext_feature_set(wiphy,
				      NL80211_EXT_FEATURE_SET_SCAN_DWELL);

	wiphy->probe_resp_offload = NL80211_PROBE_RESP_OFFLOAD_SUPPORT_WPS |
				    NL80211_PROBE_RESP_OFFLOAD_SUPPORT_WPS2;

	wiphy->available_antennas_tx = macinfo->num_tx_chain;
	wiphy->available_antennas_rx = macinfo->num_rx_chain;

	wiphy->max_ap_assoc_sta = macinfo->max_ap_assoc_sta;
	wiphy->ht_capa_mod_mask = &macinfo->ht_cap_mod_mask;
	wiphy->vht_capa_mod_mask = &macinfo->vht_cap_mod_mask;

	ether_addr_copy(wiphy->perm_addr, mac->macaddr);

	if (hw_info->hw_capab & QLINK_HW_CAPAB_STA_INACT_TIMEOUT)
		wiphy->features |= NL80211_FEATURE_INACTIVITY_TIMER;

	if (hw_info->hw_capab & QLINK_HW_CAPAB_SCAN_RANDOM_MAC_ADDR)
		wiphy->features |= NL80211_FEATURE_SCAN_RANDOM_MAC_ADDR;

	if (!(hw_info->hw_capab & QLINK_HW_CAPAB_OBSS_SCAN))
		wiphy->features |= NL80211_FEATURE_NEED_OBSS_SCAN;

	if (hw_info->hw_capab & QLINK_HW_CAPAB_SAE)
		wiphy->features |= NL80211_FEATURE_SAE;

#ifdef CONFIG_PM
	if (macinfo->wowlan)
		wiphy->wowlan = macinfo->wowlan;
#endif

	regdomain_is_known = isalpha(mac->rd->alpha2[0]) &&
				isalpha(mac->rd->alpha2[1]);

	if (hw_info->hw_capab & QLINK_HW_CAPAB_REG_UPDATE) {
		wiphy->reg_notifier = qtnf_cfg80211_reg_notifier;

		if (mac->rd->alpha2[0] == '9' && mac->rd->alpha2[1] == '9') {
			wiphy->regulatory_flags |= REGULATORY_CUSTOM_REG |
				REGULATORY_STRICT_REG;
			wiphy_apply_custom_regulatory(wiphy, mac->rd);
		} else if (regdomain_is_known) {
			wiphy->regulatory_flags |= REGULATORY_STRICT_REG;
		}
	} else {
		wiphy->regulatory_flags |= REGULATORY_WIPHY_SELF_MANAGED;
	}

	if (mac->macinfo.extended_capabilities_len) {
		wiphy->extended_capabilities =
			mac->macinfo.extended_capabilities;
		wiphy->extended_capabilities_mask =
			mac->macinfo.extended_capabilities_mask;
		wiphy->extended_capabilities_len =
			mac->macinfo.extended_capabilities_len;
	}

	strlcpy(wiphy->fw_version, hw_info->fw_version,
		sizeof(wiphy->fw_version));
	wiphy->hw_version = hw_info->hw_version;

	ret = wiphy_register(wiphy);
	if (ret < 0)
		goto out;

	if (wiphy->regulatory_flags & REGULATORY_WIPHY_SELF_MANAGED)
		ret = regulatory_set_wiphy_regd(wiphy, mac->rd);
	else if (regdomain_is_known)
		ret = regulatory_hint(wiphy, mac->rd->alpha2);

out:
	return ret;
}