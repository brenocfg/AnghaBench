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
typedef  int u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct napi_struct {int dummy; } ;
struct iwl_rx_packet {scalar_t__ data; } ;
struct iwl_rx_no_data {int /*<<< orphan*/ * rx_vec; int /*<<< orphan*/ * phy_info; int /*<<< orphan*/  info; int /*<<< orphan*/  rssi; int /*<<< orphan*/  on_air_rise_time; int /*<<< orphan*/  rate; } ;
struct iwl_rx_cmd_buffer {int dummy; } ;
struct iwl_mvm_rx_phy_data {void* info_type; int /*<<< orphan*/  d0; } ;
struct iwl_mvm {int /*<<< orphan*/  hw; int /*<<< orphan*/  status; } ;
struct ieee80211_sta {int dummy; } ;
struct ieee80211_rx_status {int device_timestamp; int enc_flags; int rate_idx; int /*<<< orphan*/  band; void* nss; int /*<<< orphan*/  encoding; int /*<<< orphan*/  freq; int /*<<< orphan*/  bw; int /*<<< orphan*/  zero_length_psdu_type; int /*<<< orphan*/  flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IEEE80211_RADIOTAP_ZERO_LEN_PSDU_NOT_CAPTURED ; 
 int /*<<< orphan*/  IEEE80211_RADIOTAP_ZERO_LEN_PSDU_SOUNDING ; 
 int /*<<< orphan*/  IEEE80211_RADIOTAP_ZERO_LEN_PSDU_VENDOR ; 
 struct ieee80211_rx_status* IEEE80211_SKB_RXCB (struct sk_buff*) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*) ; 
 int /*<<< orphan*/  IWL_MVM_STATUS_IN_HW_RESTART ; 
 int /*<<< orphan*/  IWL_RX_MPDU_PHY_TSF_OVERLOAD ; 
 int /*<<< orphan*/  IWL_RX_PHY_DATA1_INFO_TYPE_MASK ; 
 void* IWL_RX_PHY_INFO_TYPE_NONE ; 
 int /*<<< orphan*/  NL80211_BAND_2GHZ ; 
 int /*<<< orphan*/  NL80211_BAND_5GHZ ; 
 int RATE_HT_MCS_GF_MSK ; 
 int RATE_HT_MCS_INDEX_MSK ; 
 int /*<<< orphan*/  RATE_INFO_BW_160 ; 
 int /*<<< orphan*/  RATE_INFO_BW_40 ; 
 int /*<<< orphan*/  RATE_INFO_BW_80 ; 
 int RATE_MCS_BF_MSK ; 
 int RATE_MCS_CCK_MSK ; 
#define  RATE_MCS_CHAN_WIDTH_160 134 
#define  RATE_MCS_CHAN_WIDTH_20 133 
#define  RATE_MCS_CHAN_WIDTH_40 132 
#define  RATE_MCS_CHAN_WIDTH_80 131 
 int RATE_MCS_CHAN_WIDTH_MSK ; 
 int RATE_MCS_HE_MSK ; 
 int RATE_MCS_HT_MSK ; 
 int RATE_MCS_LDPC_MSK ; 
 int RATE_MCS_SGI_MSK ; 
 int RATE_MCS_STBC_MSK ; 
 int RATE_MCS_STBC_POS ; 
 int RATE_MCS_VHT_MSK ; 
 int RATE_VHT_MCS_RATE_CODE_MSK ; 
 int RX_ENC_FLAG_BF ; 
 int RX_ENC_FLAG_HT_GF ; 
 int RX_ENC_FLAG_LDPC ; 
 int RX_ENC_FLAG_SHORT_GI ; 
 int RX_ENC_FLAG_STBC_SHIFT ; 
 int /*<<< orphan*/  RX_ENC_HT ; 
 int /*<<< orphan*/  RX_ENC_VHT ; 
 int /*<<< orphan*/  RX_FLAG_NO_PSDU ; 
 int RX_NO_DATA_CHAIN_A_MSK ; 
 int RX_NO_DATA_CHAIN_A_POS ; 
 int RX_NO_DATA_CHAIN_B_MSK ; 
 int RX_NO_DATA_CHAIN_B_POS ; 
 int RX_NO_DATA_CHANNEL_MSK ; 
 int RX_NO_DATA_CHANNEL_POS ; 
#define  RX_NO_DATA_INFO_TYPE_HE_TB_UNMATCHED 130 
 int RX_NO_DATA_INFO_TYPE_MSK ; 
#define  RX_NO_DATA_INFO_TYPE_MU_UNMATCHED 129 
#define  RX_NO_DATA_INFO_TYPE_NDP 128 
 int /*<<< orphan*/  RX_NO_DATA_RX_VEC0_HE_NSTS_MSK ; 
 int /*<<< orphan*/  RX_NO_DATA_RX_VEC0_VHT_NSTS_MSK ; 
 scalar_t__ WARN (int,char*,int,int /*<<< orphan*/ ) ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_channel_to_frequency (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_rx_napi (int /*<<< orphan*/ ,struct ieee80211_sta*,struct sk_buff*,struct napi_struct*) ; 
 int /*<<< orphan*/  iwl_mvm_decode_lsig (struct sk_buff*,struct iwl_mvm_rx_phy_data*) ; 
 int /*<<< orphan*/  iwl_mvm_get_signal_strength (struct iwl_mvm*,struct ieee80211_rx_status*,int,int,int) ; 
 int iwl_mvm_legacy_rate_to_mac80211_idx (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_rx_he (struct iwl_mvm*,struct sk_buff*,struct iwl_mvm_rx_phy_data*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 void* le32_get_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct iwl_rx_packet* rxb_addr (struct iwl_rx_cmd_buffer*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void iwl_mvm_rx_monitor_no_data(struct iwl_mvm *mvm, struct napi_struct *napi,
				struct iwl_rx_cmd_buffer *rxb, int queue)
{
	struct ieee80211_rx_status *rx_status;
	struct iwl_rx_packet *pkt = rxb_addr(rxb);
	struct iwl_rx_no_data *desc = (void *)pkt->data;
	u32 rate_n_flags = le32_to_cpu(desc->rate);
	u32 gp2_on_air_rise = le32_to_cpu(desc->on_air_rise_time);
	u32 rssi = le32_to_cpu(desc->rssi);
	u32 info_type = le32_to_cpu(desc->info) & RX_NO_DATA_INFO_TYPE_MSK;
	u16 phy_info = IWL_RX_MPDU_PHY_TSF_OVERLOAD;
	struct ieee80211_sta *sta = NULL;
	struct sk_buff *skb;
	u8 channel, energy_a, energy_b;
	struct iwl_mvm_rx_phy_data phy_data = {
		.d0 = desc->phy_info[0],
		.info_type = IWL_RX_PHY_INFO_TYPE_NONE,
	};

	if (unlikely(test_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status)))
		return;

	energy_a = (rssi & RX_NO_DATA_CHAIN_A_MSK) >> RX_NO_DATA_CHAIN_A_POS;
	energy_b = (rssi & RX_NO_DATA_CHAIN_B_MSK) >> RX_NO_DATA_CHAIN_B_POS;
	channel = (rssi & RX_NO_DATA_CHANNEL_MSK) >> RX_NO_DATA_CHANNEL_POS;

	phy_data.info_type =
		le32_get_bits(desc->phy_info[1],
			      IWL_RX_PHY_DATA1_INFO_TYPE_MASK);

	/* Dont use dev_alloc_skb(), we'll have enough headroom once
	 * ieee80211_hdr pulled.
	 */
	skb = alloc_skb(128, GFP_ATOMIC);
	if (!skb) {
		IWL_ERR(mvm, "alloc_skb failed\n");
		return;
	}

	rx_status = IEEE80211_SKB_RXCB(skb);

	/* 0-length PSDU */
	rx_status->flag |= RX_FLAG_NO_PSDU;

	switch (info_type) {
	case RX_NO_DATA_INFO_TYPE_NDP:
		rx_status->zero_length_psdu_type =
			IEEE80211_RADIOTAP_ZERO_LEN_PSDU_SOUNDING;
		break;
	case RX_NO_DATA_INFO_TYPE_MU_UNMATCHED:
	case RX_NO_DATA_INFO_TYPE_HE_TB_UNMATCHED:
		rx_status->zero_length_psdu_type =
			IEEE80211_RADIOTAP_ZERO_LEN_PSDU_NOT_CAPTURED;
		break;
	default:
		rx_status->zero_length_psdu_type =
			IEEE80211_RADIOTAP_ZERO_LEN_PSDU_VENDOR;
		break;
	}

	/* This may be overridden by iwl_mvm_rx_he() to HE_RU */
	switch (rate_n_flags & RATE_MCS_CHAN_WIDTH_MSK) {
	case RATE_MCS_CHAN_WIDTH_20:
		break;
	case RATE_MCS_CHAN_WIDTH_40:
		rx_status->bw = RATE_INFO_BW_40;
		break;
	case RATE_MCS_CHAN_WIDTH_80:
		rx_status->bw = RATE_INFO_BW_80;
		break;
	case RATE_MCS_CHAN_WIDTH_160:
		rx_status->bw = RATE_INFO_BW_160;
		break;
	}

	if (rate_n_flags & RATE_MCS_HE_MSK)
		iwl_mvm_rx_he(mvm, skb, &phy_data, rate_n_flags,
			      phy_info, queue);

	iwl_mvm_decode_lsig(skb, &phy_data);

	rx_status->device_timestamp = gp2_on_air_rise;
	rx_status->band = channel > 14 ? NL80211_BAND_5GHZ :
		NL80211_BAND_2GHZ;
	rx_status->freq = ieee80211_channel_to_frequency(channel,
							 rx_status->band);
	iwl_mvm_get_signal_strength(mvm, rx_status, rate_n_flags, energy_a,
				    energy_b);

	rcu_read_lock();

	if (!(rate_n_flags & RATE_MCS_CCK_MSK) &&
	    rate_n_flags & RATE_MCS_SGI_MSK)
		rx_status->enc_flags |= RX_ENC_FLAG_SHORT_GI;
	if (rate_n_flags & RATE_HT_MCS_GF_MSK)
		rx_status->enc_flags |= RX_ENC_FLAG_HT_GF;
	if (rate_n_flags & RATE_MCS_LDPC_MSK)
		rx_status->enc_flags |= RX_ENC_FLAG_LDPC;
	if (rate_n_flags & RATE_MCS_HT_MSK) {
		u8 stbc = (rate_n_flags & RATE_MCS_STBC_MSK) >>
				RATE_MCS_STBC_POS;
		rx_status->encoding = RX_ENC_HT;
		rx_status->rate_idx = rate_n_flags & RATE_HT_MCS_INDEX_MSK;
		rx_status->enc_flags |= stbc << RX_ENC_FLAG_STBC_SHIFT;
	} else if (rate_n_flags & RATE_MCS_VHT_MSK) {
		u8 stbc = (rate_n_flags & RATE_MCS_STBC_MSK) >>
				RATE_MCS_STBC_POS;
		rx_status->rate_idx = rate_n_flags & RATE_VHT_MCS_RATE_CODE_MSK;
		rx_status->encoding = RX_ENC_VHT;
		rx_status->enc_flags |= stbc << RX_ENC_FLAG_STBC_SHIFT;
		if (rate_n_flags & RATE_MCS_BF_MSK)
			rx_status->enc_flags |= RX_ENC_FLAG_BF;
		/*
		 * take the nss from the rx_vec since the rate_n_flags has
		 * only 2 bits for the nss which gives a max of 4 ss but
		 * there may be up to 8 spatial streams
		 */
		rx_status->nss =
			le32_get_bits(desc->rx_vec[0],
				      RX_NO_DATA_RX_VEC0_VHT_NSTS_MSK) + 1;
	} else if (rate_n_flags & RATE_MCS_HE_MSK) {
		rx_status->nss =
			le32_get_bits(desc->rx_vec[0],
				      RX_NO_DATA_RX_VEC0_HE_NSTS_MSK) + 1;
	} else {
		int rate = iwl_mvm_legacy_rate_to_mac80211_idx(rate_n_flags,
							       rx_status->band);

		if (WARN(rate < 0 || rate > 0xFF,
			 "Invalid rate flags 0x%x, band %d,\n",
			 rate_n_flags, rx_status->band)) {
			kfree_skb(skb);
			goto out;
		}
		rx_status->rate_idx = rate;
	}

	ieee80211_rx_napi(mvm->hw, sta, skb, napi);
out:
	rcu_read_unlock();
}