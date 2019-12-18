#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sk_buff {int dummy; } ;
struct iwl_mvm_rx_phy_data {int info_type; int /*<<< orphan*/  d1; } ;
struct ieee80211_rx_status {int /*<<< orphan*/  flag; } ;
struct ieee80211_radiotap_lsig {int /*<<< orphan*/  data2; int /*<<< orphan*/  data1; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_RADIOTAP_LSIG_DATA1_LENGTH_KNOWN ; 
 int /*<<< orphan*/  IEEE80211_RADIOTAP_LSIG_DATA2_LENGTH ; 
 struct ieee80211_rx_status* IEEE80211_SKB_RXCB (struct sk_buff*) ; 
 int /*<<< orphan*/  IWL_RX_PHY_DATA1_LSIG_LEN_MASK ; 
#define  IWL_RX_PHY_INFO_TYPE_HE_MU 135 
#define  IWL_RX_PHY_INFO_TYPE_HE_MU_EXT 134 
#define  IWL_RX_PHY_INFO_TYPE_HE_SU 133 
#define  IWL_RX_PHY_INFO_TYPE_HE_TB 132 
#define  IWL_RX_PHY_INFO_TYPE_HE_TB_EXT 131 
#define  IWL_RX_PHY_INFO_TYPE_HT 130 
#define  IWL_RX_PHY_INFO_TYPE_VHT_MU 129 
#define  IWL_RX_PHY_INFO_TYPE_VHT_SU 128 
 int /*<<< orphan*/  RX_FLAG_RADIOTAP_LSIG ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_encode_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_get_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ieee80211_radiotap_lsig* skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static void iwl_mvm_decode_lsig(struct sk_buff *skb,
				struct iwl_mvm_rx_phy_data *phy_data)
{
	struct ieee80211_rx_status *rx_status = IEEE80211_SKB_RXCB(skb);
	struct ieee80211_radiotap_lsig *lsig;

	switch (phy_data->info_type) {
	case IWL_RX_PHY_INFO_TYPE_HT:
	case IWL_RX_PHY_INFO_TYPE_VHT_SU:
	case IWL_RX_PHY_INFO_TYPE_VHT_MU:
	case IWL_RX_PHY_INFO_TYPE_HE_TB_EXT:
	case IWL_RX_PHY_INFO_TYPE_HE_SU:
	case IWL_RX_PHY_INFO_TYPE_HE_MU:
	case IWL_RX_PHY_INFO_TYPE_HE_MU_EXT:
	case IWL_RX_PHY_INFO_TYPE_HE_TB:
		lsig = skb_put(skb, sizeof(*lsig));
		lsig->data1 = cpu_to_le16(IEEE80211_RADIOTAP_LSIG_DATA1_LENGTH_KNOWN);
		lsig->data2 = le16_encode_bits(le32_get_bits(phy_data->d1,
							     IWL_RX_PHY_DATA1_LSIG_LEN_MASK),
					       IEEE80211_RADIOTAP_LSIG_DATA2_LENGTH);
		rx_status->flag |= RX_FLAG_RADIOTAP_LSIG;
		break;
	default:
		break;
	}
}