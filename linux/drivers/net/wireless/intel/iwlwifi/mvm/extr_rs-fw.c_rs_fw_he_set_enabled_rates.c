#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct iwl_tlc_config_cmd {void*** ht_rates; } ;
struct ieee80211_supported_band {TYPE_4__* iftype_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  rx_mcs_80; int /*<<< orphan*/  rx_mcs_160; } ;
struct ieee80211_sta_he_cap {TYPE_1__ he_mcs_nss_supp; } ;
struct ieee80211_sta {int rx_nss; struct ieee80211_sta_he_cap he_cap; } ;
struct TYPE_6__ {int /*<<< orphan*/  tx_mcs_160; int /*<<< orphan*/  tx_mcs_80; } ;
struct TYPE_7__ {TYPE_2__ he_mcs_nss_supp; } ;
struct TYPE_8__ {TYPE_3__ he_cap; } ;

/* Variables and functions */
 int IEEE80211_HE_MCS_NOT_SUPPORTED ; 
 size_t IWL_TLC_HT_BW_160 ; 
 size_t IWL_TLC_HT_BW_NONE_160 ; 
 int IWL_TLC_NSS_MAX ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rs_fw_he_ieee80211_mcs_to_rs_mcs (int) ; 

__attribute__((used)) static void
rs_fw_he_set_enabled_rates(const struct ieee80211_sta *sta,
			   struct ieee80211_supported_band *sband,
			   struct iwl_tlc_config_cmd *cmd)
{
	const struct ieee80211_sta_he_cap *he_cap = &sta->he_cap;
	u16 mcs_160 = le16_to_cpu(he_cap->he_mcs_nss_supp.rx_mcs_160);
	u16 mcs_80 = le16_to_cpu(he_cap->he_mcs_nss_supp.rx_mcs_80);
	u16 tx_mcs_80 =
		le16_to_cpu(sband->iftype_data->he_cap.he_mcs_nss_supp.tx_mcs_80);
	u16 tx_mcs_160 =
		le16_to_cpu(sband->iftype_data->he_cap.he_mcs_nss_supp.tx_mcs_160);
	int i;

	for (i = 0; i < sta->rx_nss && i < IWL_TLC_NSS_MAX; i++) {
		u16 _mcs_160 = (mcs_160 >> (2 * i)) & 0x3;
		u16 _mcs_80 = (mcs_80 >> (2 * i)) & 0x3;
		u16 _tx_mcs_160 = (tx_mcs_160 >> (2 * i)) & 0x3;
		u16 _tx_mcs_80 = (tx_mcs_80 >> (2 * i)) & 0x3;

		/* If one side doesn't support - mark both as not supporting */
		if (_mcs_80 == IEEE80211_HE_MCS_NOT_SUPPORTED ||
		    _tx_mcs_80 == IEEE80211_HE_MCS_NOT_SUPPORTED) {
			_mcs_80 = IEEE80211_HE_MCS_NOT_SUPPORTED;
			_tx_mcs_80 = IEEE80211_HE_MCS_NOT_SUPPORTED;
		}
		if (_mcs_80 > _tx_mcs_80)
			_mcs_80 = _tx_mcs_80;
		cmd->ht_rates[i][IWL_TLC_HT_BW_NONE_160] =
			cpu_to_le16(rs_fw_he_ieee80211_mcs_to_rs_mcs(_mcs_80));

		/* If one side doesn't support - mark both as not supporting */
		if (_mcs_160 == IEEE80211_HE_MCS_NOT_SUPPORTED ||
		    _tx_mcs_160 == IEEE80211_HE_MCS_NOT_SUPPORTED) {
			_mcs_160 = IEEE80211_HE_MCS_NOT_SUPPORTED;
			_tx_mcs_160 = IEEE80211_HE_MCS_NOT_SUPPORTED;
		}
		if (_mcs_160 > _tx_mcs_160)
			_mcs_160 = _tx_mcs_160;
		cmd->ht_rates[i][IWL_TLC_HT_BW_160] =
			cpu_to_le16(rs_fw_he_ieee80211_mcs_to_rs_mcs(_mcs_160));
	}
}