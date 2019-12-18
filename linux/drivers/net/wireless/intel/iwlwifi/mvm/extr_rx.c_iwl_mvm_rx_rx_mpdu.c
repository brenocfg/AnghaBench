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
typedef  int u8 ;
typedef  int u32 ;
struct sk_buff {int dummy; } ;
struct napi_struct {int dummy; } ;
struct iwl_rx_phy_info {int phy_flags; int /*<<< orphan*/  channel; int /*<<< orphan*/  system_timestamp; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  rate_n_flags; } ;
struct iwl_rx_packet {scalar_t__ data; } ;
struct iwl_rx_mpdu_res_start {int /*<<< orphan*/  byte_count; } ;
struct iwl_rx_cmd_buffer {int dummy; } ;
struct iwl_mvm_vif {scalar_t__ csa_target_freq; } ;
struct iwl_mvm_sta {struct ieee80211_vif* vif; } ;
struct TYPE_2__ {int /*<<< orphan*/  paused; } ;
struct iwl_mvm {scalar_t__ sched_scan_pass_all; int /*<<< orphan*/  ampdu_ref; TYPE_1__ tcm; int /*<<< orphan*/  fwrt; int /*<<< orphan*/  csa_tx_blocked_vif; int /*<<< orphan*/  hw; int /*<<< orphan*/ * fw_id_to_mac_id; struct iwl_rx_phy_info last_phy_info; } ;
struct iwl_fw_dbg_trigger_tlv {scalar_t__ data; } ;
struct iwl_fw_dbg_trigger_low_rssi {int /*<<< orphan*/  rssi; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {int dummy; } ;
struct ieee80211_rx_status {int flag; scalar_t__ freq; scalar_t__ signal; int enc_flags; int rate_idx; int nss; int /*<<< orphan*/  boottime_ns; int /*<<< orphan*/  band; int /*<<< orphan*/  encoding; int /*<<< orphan*/  bw; int /*<<< orphan*/  ampdu_reference; scalar_t__ mactime; void* device_timestamp; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; int /*<<< orphan*/  addr1; int /*<<< orphan*/  addr2; } ;
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FW_DBG_TRIGGER_RSSI ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct ieee80211_rx_status* IEEE80211_SKB_RXCB (struct sk_buff*) ; 
 scalar_t__ IS_ERR (struct ieee80211_sta*) ; 
 int /*<<< orphan*/  IWL_DEBUG_DROP (struct iwl_mvm*,char*,int) ; 
 int /*<<< orphan*/  IWL_DEBUG_RX (struct iwl_mvm*,char*,int) ; 
 int /*<<< orphan*/  IWL_DEBUG_STATS_LIMIT (struct iwl_mvm*,char*,scalar_t__,unsigned long long) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*) ; 
 int /*<<< orphan*/  NL80211_BAND_2GHZ ; 
 int /*<<< orphan*/  NL80211_BAND_5GHZ ; 
 int RATE_HT_MCS_GF_MSK ; 
 int RATE_HT_MCS_INDEX_MSK ; 
 int /*<<< orphan*/  RATE_INFO_BW_160 ; 
 int /*<<< orphan*/  RATE_INFO_BW_40 ; 
 int /*<<< orphan*/  RATE_INFO_BW_80 ; 
 int RATE_MCS_BF_MSK ; 
 int RATE_MCS_CCK_MSK ; 
#define  RATE_MCS_CHAN_WIDTH_160 131 
#define  RATE_MCS_CHAN_WIDTH_20 130 
#define  RATE_MCS_CHAN_WIDTH_40 129 
#define  RATE_MCS_CHAN_WIDTH_80 128 
 int RATE_MCS_CHAN_WIDTH_MSK ; 
 int RATE_MCS_HT_MSK ; 
 int RATE_MCS_LDPC_MSK ; 
 int RATE_MCS_SGI_MSK ; 
 int RATE_MCS_STBC_MSK ; 
 int RATE_MCS_STBC_POS ; 
 int RATE_MCS_VHT_MSK ; 
 int RATE_VHT_MCS_NSS_MSK ; 
 int RATE_VHT_MCS_NSS_POS ; 
 int RATE_VHT_MCS_RATE_CODE_MSK ; 
 int RX_ENC_FLAG_BF ; 
 int RX_ENC_FLAG_HT_GF ; 
 int RX_ENC_FLAG_LDPC ; 
 int RX_ENC_FLAG_SHORTPRE ; 
 int RX_ENC_FLAG_SHORT_GI ; 
 int RX_ENC_FLAG_STBC_SHIFT ; 
 int /*<<< orphan*/  RX_ENC_HT ; 
 int /*<<< orphan*/  RX_ENC_VHT ; 
 int RX_FLAG_AMPDU_DETAILS ; 
 int RX_FLAG_FAILED_FCS_CRC ; 
 int RX_FLAG_MACTIME_PLCP_START ; 
 int RX_MDPU_RES_STATUS_STA_ID_SHIFT ; 
 int RX_MPDU_RES_STATUS_CRC_OK ; 
 int RX_MPDU_RES_STATUS_OVERRUN_OK ; 
 int RX_MPDU_RES_STATUS_SRC_STA_FOUND ; 
 int RX_MPDU_RES_STATUS_STA_ID_MSK ; 
 int /*<<< orphan*/  RX_RES_PHY_FLAGS_AGG ; 
 int /*<<< orphan*/  RX_RES_PHY_FLAGS_BAND_24 ; 
 int /*<<< orphan*/  RX_RES_PHY_FLAGS_SHORT_PREAMBLE ; 
 scalar_t__ SCHED_SCAN_PASS_ALL_ENABLED ; 
 scalar_t__ SCHED_SCAN_PASS_ALL_FOUND ; 
 scalar_t__ WARN (int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int cpu_to_le16 (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_channel_to_frequency (int,int /*<<< orphan*/ ) ; 
 struct ieee80211_sta* ieee80211_find_sta_by_ifaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ieee80211_is_beacon (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_data (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_probe_resp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_vif_to_wdev (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_fw_dbg_collect_trig (int /*<<< orphan*/ *,struct iwl_fw_dbg_trigger_tlv*,int /*<<< orphan*/ *) ; 
 struct iwl_fw_dbg_trigger_tlv* iwl_fw_dbg_trigger_on (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_get_signal_strength (struct iwl_mvm*,struct iwl_rx_phy_info*,struct ieee80211_rx_status*) ; 
 int iwl_mvm_legacy_rate_to_mac80211_idx (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_pass_packet_to_mac80211 (struct iwl_mvm*,struct ieee80211_sta*,struct napi_struct*,struct sk_buff*,struct ieee80211_hdr*,int,int,struct iwl_rx_cmd_buffer*) ; 
 int /*<<< orphan*/  iwl_mvm_rx_csum (struct ieee80211_sta*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  iwl_mvm_rx_handle_tcm (struct iwl_mvm*,struct ieee80211_sta*,struct ieee80211_hdr*,int,struct iwl_rx_phy_info*,int) ; 
 scalar_t__ iwl_mvm_set_mac80211_rx_flag (struct iwl_mvm*,struct ieee80211_hdr*,struct ieee80211_rx_status*,int,int*) ; 
 struct iwl_mvm_sta* iwl_mvm_sta_from_mac80211 (struct ieee80211_sta*) ; 
 int /*<<< orphan*/  iwl_mvm_sta_modify_disable_tx_ap (struct iwl_mvm*,struct ieee80211_sta*,int) ; 
 int /*<<< orphan*/  iwl_mvm_update_frame_stats (struct iwl_mvm*,int,int) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  ktime_get_boottime_ns () ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpup (int /*<<< orphan*/ *) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 void* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  rs_update_last_rssi (struct iwl_mvm*,struct iwl_mvm_sta*,struct ieee80211_rx_status*) ; 
 struct iwl_rx_packet* rxb_addr (struct iwl_rx_cmd_buffer*) ; 
 scalar_t__ unlikely (int) ; 

void iwl_mvm_rx_rx_mpdu(struct iwl_mvm *mvm, struct napi_struct *napi,
			struct iwl_rx_cmd_buffer *rxb)
{
	struct ieee80211_hdr *hdr;
	struct ieee80211_rx_status *rx_status;
	struct iwl_rx_packet *pkt = rxb_addr(rxb);
	struct iwl_rx_phy_info *phy_info;
	struct iwl_rx_mpdu_res_start *rx_res;
	struct ieee80211_sta *sta = NULL;
	struct sk_buff *skb;
	u32 len;
	u32 rate_n_flags;
	u32 rx_pkt_status;
	u8 crypt_len = 0;

	phy_info = &mvm->last_phy_info;
	rx_res = (struct iwl_rx_mpdu_res_start *)pkt->data;
	hdr = (struct ieee80211_hdr *)(pkt->data + sizeof(*rx_res));
	len = le16_to_cpu(rx_res->byte_count);
	rx_pkt_status = le32_to_cpup((__le32 *)
		(pkt->data + sizeof(*rx_res) + len));

	/* Dont use dev_alloc_skb(), we'll have enough headroom once
	 * ieee80211_hdr pulled.
	 */
	skb = alloc_skb(128, GFP_ATOMIC);
	if (!skb) {
		IWL_ERR(mvm, "alloc_skb failed\n");
		return;
	}

	rx_status = IEEE80211_SKB_RXCB(skb);

	/*
	 * drop the packet if it has failed being decrypted by HW
	 */
	if (iwl_mvm_set_mac80211_rx_flag(mvm, hdr, rx_status, rx_pkt_status,
					 &crypt_len)) {
		IWL_DEBUG_DROP(mvm, "Bad decryption results 0x%08x\n",
			       rx_pkt_status);
		kfree_skb(skb);
		return;
	}

	/*
	 * Keep packets with CRC errors (and with overrun) for monitor mode
	 * (otherwise the firmware discards them) but mark them as bad.
	 */
	if (!(rx_pkt_status & RX_MPDU_RES_STATUS_CRC_OK) ||
	    !(rx_pkt_status & RX_MPDU_RES_STATUS_OVERRUN_OK)) {
		IWL_DEBUG_RX(mvm, "Bad CRC or FIFO: 0x%08X.\n", rx_pkt_status);
		rx_status->flag |= RX_FLAG_FAILED_FCS_CRC;
	}

	/* This will be used in several places later */
	rate_n_flags = le32_to_cpu(phy_info->rate_n_flags);

	/* rx_status carries information about the packet to mac80211 */
	rx_status->mactime = le64_to_cpu(phy_info->timestamp);
	rx_status->device_timestamp = le32_to_cpu(phy_info->system_timestamp);
	rx_status->band =
		(phy_info->phy_flags & cpu_to_le16(RX_RES_PHY_FLAGS_BAND_24)) ?
				NL80211_BAND_2GHZ : NL80211_BAND_5GHZ;
	rx_status->freq =
		ieee80211_channel_to_frequency(le16_to_cpu(phy_info->channel),
					       rx_status->band);

	/* TSF as indicated by the firmware  is at INA time */
	rx_status->flag |= RX_FLAG_MACTIME_PLCP_START;

	iwl_mvm_get_signal_strength(mvm, phy_info, rx_status);

	IWL_DEBUG_STATS_LIMIT(mvm, "Rssi %d, TSF %llu\n", rx_status->signal,
			      (unsigned long long)rx_status->mactime);

	rcu_read_lock();
	if (rx_pkt_status & RX_MPDU_RES_STATUS_SRC_STA_FOUND) {
		u32 id = rx_pkt_status & RX_MPDU_RES_STATUS_STA_ID_MSK;

		id >>= RX_MDPU_RES_STATUS_STA_ID_SHIFT;

		if (!WARN_ON_ONCE(id >= ARRAY_SIZE(mvm->fw_id_to_mac_id))) {
			sta = rcu_dereference(mvm->fw_id_to_mac_id[id]);
			if (IS_ERR(sta))
				sta = NULL;
		}
	} else if (!is_multicast_ether_addr(hdr->addr2)) {
		/* This is fine since we prevent two stations with the same
		 * address from being added.
		 */
		sta = ieee80211_find_sta_by_ifaddr(mvm->hw, hdr->addr2, NULL);
	}

	if (sta) {
		struct iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
		struct ieee80211_vif *tx_blocked_vif =
			rcu_dereference(mvm->csa_tx_blocked_vif);
		struct iwl_fw_dbg_trigger_tlv *trig;
		struct ieee80211_vif *vif = mvmsta->vif;

		/* We have tx blocked stations (with CS bit). If we heard
		 * frames from a blocked station on a new channel we can
		 * TX to it again.
		 */
		if (unlikely(tx_blocked_vif) && vif == tx_blocked_vif) {
			struct iwl_mvm_vif *mvmvif =
				iwl_mvm_vif_from_mac80211(tx_blocked_vif);

			if (mvmvif->csa_target_freq == rx_status->freq)
				iwl_mvm_sta_modify_disable_tx_ap(mvm, sta,
								 false);
		}

		rs_update_last_rssi(mvm, mvmsta, rx_status);

		trig = iwl_fw_dbg_trigger_on(&mvm->fwrt,
					     ieee80211_vif_to_wdev(vif),
					     FW_DBG_TRIGGER_RSSI);

		if (trig && ieee80211_is_beacon(hdr->frame_control)) {
			struct iwl_fw_dbg_trigger_low_rssi *rssi_trig;
			s32 rssi;

			rssi_trig = (void *)trig->data;
			rssi = le32_to_cpu(rssi_trig->rssi);

			if (rx_status->signal < rssi)
				iwl_fw_dbg_collect_trig(&mvm->fwrt, trig,
							NULL);
		}

		if (!mvm->tcm.paused && len >= sizeof(*hdr) &&
		    !is_multicast_ether_addr(hdr->addr1) &&
		    ieee80211_is_data(hdr->frame_control))
			iwl_mvm_rx_handle_tcm(mvm, sta, hdr, len, phy_info,
					      rate_n_flags);

		if (ieee80211_is_data(hdr->frame_control))
			iwl_mvm_rx_csum(sta, skb, rx_pkt_status);
	}
	rcu_read_unlock();

	/* set the preamble flag if appropriate */
	if (phy_info->phy_flags & cpu_to_le16(RX_RES_PHY_FLAGS_SHORT_PREAMBLE))
		rx_status->enc_flags |= RX_ENC_FLAG_SHORTPRE;

	if (phy_info->phy_flags & cpu_to_le16(RX_RES_PHY_FLAGS_AGG)) {
		/*
		 * We know which subframes of an A-MPDU belong
		 * together since we get a single PHY response
		 * from the firmware for all of them
		 */
		rx_status->flag |= RX_FLAG_AMPDU_DETAILS;
		rx_status->ampdu_reference = mvm->ampdu_ref;
	}

	/* Set up the HT phy flags */
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
		rx_status->nss =
			((rate_n_flags & RATE_VHT_MCS_NSS_MSK) >>
						RATE_VHT_MCS_NSS_POS) + 1;
		rx_status->rate_idx = rate_n_flags & RATE_VHT_MCS_RATE_CODE_MSK;
		rx_status->encoding = RX_ENC_VHT;
		rx_status->enc_flags |= stbc << RX_ENC_FLAG_STBC_SHIFT;
		if (rate_n_flags & RATE_MCS_BF_MSK)
			rx_status->enc_flags |= RX_ENC_FLAG_BF;
	} else {
		int rate = iwl_mvm_legacy_rate_to_mac80211_idx(rate_n_flags,
							       rx_status->band);

		if (WARN(rate < 0 || rate > 0xFF,
			 "Invalid rate flags 0x%x, band %d,\n",
			 rate_n_flags, rx_status->band)) {
			kfree_skb(skb);
			return;
		}
		rx_status->rate_idx = rate;
	}

#ifdef CONFIG_IWLWIFI_DEBUGFS
	iwl_mvm_update_frame_stats(mvm, rate_n_flags,
				   rx_status->flag & RX_FLAG_AMPDU_DETAILS);
#endif

	if (unlikely((ieee80211_is_beacon(hdr->frame_control) ||
		      ieee80211_is_probe_resp(hdr->frame_control)) &&
		     mvm->sched_scan_pass_all == SCHED_SCAN_PASS_ALL_ENABLED))
		mvm->sched_scan_pass_all = SCHED_SCAN_PASS_ALL_FOUND;

	if (unlikely(ieee80211_is_beacon(hdr->frame_control) ||
		     ieee80211_is_probe_resp(hdr->frame_control)))
		rx_status->boottime_ns = ktime_get_boottime_ns();

	iwl_mvm_pass_packet_to_mac80211(mvm, sta, napi, skb, hdr, len,
					crypt_len, rxb);
}