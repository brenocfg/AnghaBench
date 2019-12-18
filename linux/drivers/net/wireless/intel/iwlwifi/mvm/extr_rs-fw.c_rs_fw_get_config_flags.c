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
typedef  int /*<<< orphan*/  u16 ;
struct iwl_mvm {TYPE_2__* cfg; } ;
struct ieee80211_supported_band {TYPE_5__* iftype_data; } ;
struct ieee80211_sta_vht_cap {int vht_supported; int cap; } ;
struct ieee80211_sta_ht_cap {int cap; } ;
struct TYPE_12__ {int* phy_cap_info; } ;
struct ieee80211_sta_he_cap {TYPE_6__ he_cap_elem; scalar_t__ has_he; } ;
struct ieee80211_sta {struct ieee80211_sta_he_cap he_cap; struct ieee80211_sta_vht_cap vht_cap; struct ieee80211_sta_ht_cap ht_cap; } ;
struct TYPE_9__ {int* phy_cap_info; } ;
struct TYPE_10__ {TYPE_3__ he_cap_elem; scalar_t__ has_he; } ;
struct TYPE_11__ {TYPE_4__ he_cap; } ;
struct TYPE_8__ {TYPE_1__* ht_params; } ;
struct TYPE_7__ {scalar_t__ ldpc; scalar_t__ stbc; } ;

/* Variables and functions */
 int IEEE80211_HE_PHY_CAP1_LDPC_CODING_IN_PAYLOAD ; 
 int IEEE80211_HE_PHY_CAP2_STBC_RX_UNDER_80MHZ ; 
 int IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_RX_MASK ; 
 int IEEE80211_HE_PHY_CAP7_STBC_RX_ABOVE_80MHZ ; 
 int IEEE80211_HT_CAP_LDPC_CODING ; 
 int IEEE80211_HT_CAP_RX_STBC ; 
 int IEEE80211_VHT_CAP_RXLDPC ; 
 int IEEE80211_VHT_CAP_RXSTBC_MASK ; 
 int /*<<< orphan*/  IWL_TLC_MNG_CFG_FLAGS_HE_DCM_NSS_1_MSK ; 
 int /*<<< orphan*/  IWL_TLC_MNG_CFG_FLAGS_HE_STBC_160MHZ_MSK ; 
 int /*<<< orphan*/  IWL_TLC_MNG_CFG_FLAGS_LDPC_MSK ; 
 int /*<<< orphan*/  IWL_TLC_MNG_CFG_FLAGS_STBC_MSK ; 
 int /*<<< orphan*/  iwl_mvm_get_valid_tx_ant (struct iwl_mvm*) ; 
 int num_of_ant (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 rs_fw_get_config_flags(struct iwl_mvm *mvm,
				  struct ieee80211_sta *sta,
				  struct ieee80211_supported_band *sband)
{
	struct ieee80211_sta_ht_cap *ht_cap = &sta->ht_cap;
	struct ieee80211_sta_vht_cap *vht_cap = &sta->vht_cap;
	struct ieee80211_sta_he_cap *he_cap = &sta->he_cap;
	bool vht_ena = vht_cap->vht_supported;
	u16 flags = 0;

	if (mvm->cfg->ht_params->stbc &&
	    (num_of_ant(iwl_mvm_get_valid_tx_ant(mvm)) > 1)) {
		if (he_cap->has_he) {
			if (he_cap->he_cap_elem.phy_cap_info[2] &
			    IEEE80211_HE_PHY_CAP2_STBC_RX_UNDER_80MHZ)
				flags |= IWL_TLC_MNG_CFG_FLAGS_STBC_MSK;

			if (he_cap->he_cap_elem.phy_cap_info[7] &
			    IEEE80211_HE_PHY_CAP7_STBC_RX_ABOVE_80MHZ)
				flags |= IWL_TLC_MNG_CFG_FLAGS_HE_STBC_160MHZ_MSK;
		} else if ((ht_cap->cap & IEEE80211_HT_CAP_RX_STBC) ||
			   (vht_ena &&
			    (vht_cap->cap & IEEE80211_VHT_CAP_RXSTBC_MASK)))
			flags |= IWL_TLC_MNG_CFG_FLAGS_STBC_MSK;
	}

	if (mvm->cfg->ht_params->ldpc &&
	    ((ht_cap->cap & IEEE80211_HT_CAP_LDPC_CODING) ||
	     (vht_ena && (vht_cap->cap & IEEE80211_VHT_CAP_RXLDPC))))
		flags |= IWL_TLC_MNG_CFG_FLAGS_LDPC_MSK;

	/* consider our LDPC support in case of HE */
	if (sband->iftype_data && sband->iftype_data->he_cap.has_he &&
	    !(sband->iftype_data->he_cap.he_cap_elem.phy_cap_info[1] &
	     IEEE80211_HE_PHY_CAP1_LDPC_CODING_IN_PAYLOAD))
		flags &= ~IWL_TLC_MNG_CFG_FLAGS_LDPC_MSK;

	if (he_cap->has_he &&
	    (he_cap->he_cap_elem.phy_cap_info[3] &
	     IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_RX_MASK))
		flags |= IWL_TLC_MNG_CFG_FLAGS_HE_DCM_NSS_1_MSK;

	return flags;
}