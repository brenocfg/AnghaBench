#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct sk_buff {int dummy; } ;
struct napi_struct {int dummy; } ;
struct iwl_rx_packet {int /*<<< orphan*/  len_n_flags; scalar_t__ data; } ;
struct TYPE_7__ {int channel; int energy_a; int energy_b; int /*<<< orphan*/  tsf_on_air_rise; int /*<<< orphan*/  phy_data3; int /*<<< orphan*/  phy_data2; int /*<<< orphan*/  phy_data1; int /*<<< orphan*/  phy_data0; int /*<<< orphan*/  gp2_on_air_rise; int /*<<< orphan*/  rate_n_flags; } ;
struct TYPE_6__ {int channel; int energy_a; int energy_b; int /*<<< orphan*/  tsf_on_air_rise; int /*<<< orphan*/  phy_data3; int /*<<< orphan*/  phy_data2; int /*<<< orphan*/  phy_data1; int /*<<< orphan*/  phy_data0; int /*<<< orphan*/  gp2_on_air_rise; int /*<<< orphan*/  rate_n_flags; } ;
struct iwl_rx_mpdu_desc {int mpdu_len; int phy_info; int mac_flags2; int status; int sta_id_flags; int /*<<< orphan*/  reorder_data; TYPE_2__ v1; TYPE_1__ v3; int /*<<< orphan*/  phy_data4; } ;
struct iwl_rx_cmd_buffer {int dummy; } ;
struct iwl_mvm_vif {scalar_t__ csa_target_freq; } ;
struct iwl_mvm_sta {struct ieee80211_vif* vif; } ;
struct iwl_mvm_rx_phy_data {int /*<<< orphan*/  d1; int /*<<< orphan*/  info_type; int /*<<< orphan*/  d3; int /*<<< orphan*/  d2; int /*<<< orphan*/  d0; int /*<<< orphan*/  d4; } ;
struct TYPE_8__ {int /*<<< orphan*/  work; scalar_t__ ts; int /*<<< orphan*/  paused; } ;
struct iwl_mvm {int ampdu_toggle; scalar_t__ ampdu_ref; int monitor_on; scalar_t__ sched_scan_pass_all; TYPE_5__* trans; int /*<<< orphan*/  fwrt; TYPE_3__ tcm; int /*<<< orphan*/  csa_tx_blocked_vif; int /*<<< orphan*/  hw; int /*<<< orphan*/ * fw_id_to_mac_id; int /*<<< orphan*/  status; } ;
struct iwl_fw_dbg_trigger_tlv {scalar_t__ data; } ;
struct iwl_fw_dbg_trigger_low_rssi {int /*<<< orphan*/  rssi; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {int dummy; } ;
struct ieee80211_rx_status {int enc_flags; int device_timestamp; scalar_t__ freq; scalar_t__ ampdu_reference; scalar_t__ signal; int rate_idx; int nss; int /*<<< orphan*/  boottime_ns; int /*<<< orphan*/  band; int /*<<< orphan*/  encoding; int /*<<< orphan*/  flag; int /*<<< orphan*/  mactime; int /*<<< orphan*/  bw; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; int /*<<< orphan*/  addr4; int /*<<< orphan*/  addr3; int /*<<< orphan*/  addr1; int /*<<< orphan*/  addr2; } ;
typedef  scalar_t__ s32 ;
struct TYPE_10__ {TYPE_4__* trans_cfg; } ;
struct TYPE_9__ {scalar_t__ device_family; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FW_DBG_TRIGGER_RSSI ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int IEEE80211_QOS_CTL_A_MSDU_PRESENT ; 
 struct ieee80211_rx_status* IEEE80211_SKB_RXCB (struct sk_buff*) ; 
 scalar_t__ IS_ERR (struct ieee80211_sta*) ; 
 int /*<<< orphan*/  IWL_DEBUG_RX (struct iwl_mvm*,char*,int) ; 
 scalar_t__ IWL_DEVICE_FAMILY_22560 ; 
 scalar_t__ IWL_DEVICE_FAMILY_9000 ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*) ; 
 int /*<<< orphan*/  IWL_MVM_STATUS_IN_HW_RESTART ; 
 size_t IWL_RX_DESC_SIZE_V1 ; 
 int IWL_RX_MPDU_MFLG2_AMSDU ; 
 int IWL_RX_MPDU_MFLG2_PAD ; 
 int IWL_RX_MPDU_PHY_AMPDU ; 
 int IWL_RX_MPDU_PHY_AMPDU_TOGGLE ; 
 int IWL_RX_MPDU_PHY_SHORT_PREAMBLE ; 
 int IWL_RX_MPDU_PHY_TSF_OVERLOAD ; 
 int IWL_RX_MPDU_REORDER_BAID_MASK ; 
 int IWL_RX_MPDU_REORDER_BAID_SHIFT ; 
 int IWL_RX_MPDU_SIF_STA_ID_MASK ; 
 int /*<<< orphan*/  IWL_RX_MPDU_STATUS_CRC_OK ; 
 int /*<<< orphan*/  IWL_RX_MPDU_STATUS_OVERRUN_OK ; 
 int /*<<< orphan*/  IWL_RX_MPDU_STATUS_SRC_STA_FOUND ; 
 int /*<<< orphan*/  IWL_RX_PHY_DATA1_INFO_TYPE_MASK ; 
 int /*<<< orphan*/  IWL_RX_PHY_INFO_TYPE_NONE ; 
 int IWL_RX_REORDER_DATA_INVALID_BAID ; 
 scalar_t__ MVM_TCM_PERIOD ; 
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
 int RATE_MCS_HE_MSK ; 
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
 int /*<<< orphan*/  RX_FLAG_AMPDU_DETAILS ; 
 int /*<<< orphan*/  RX_FLAG_FAILED_FCS_CRC ; 
 int /*<<< orphan*/  RX_FLAG_MACTIME_PLCP_START ; 
 scalar_t__ SCHED_SCAN_PASS_ALL_ENABLED ; 
 scalar_t__ SCHED_SCAN_PASS_ALL_FOUND ; 
 scalar_t__ WARN (int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int cpu_to_le16 (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_channel_to_frequency (int,int /*<<< orphan*/ ) ; 
 struct ieee80211_sta* ieee80211_find_sta_by_ifaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int* ieee80211_get_qos_ctl (struct ieee80211_hdr*) ; 
 scalar_t__ ieee80211_has_a4 (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_beacon (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_data_qos (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_probe_resp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_vif_to_wdev (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_fw_dbg_collect_trig (int /*<<< orphan*/ *,struct iwl_fw_dbg_trigger_tlv*,int /*<<< orphan*/ *) ; 
 struct iwl_fw_dbg_trigger_tlv* iwl_fw_dbg_trigger_on (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_add_rtap_sniffer_config (struct iwl_mvm*,struct sk_buff*) ; 
 int /*<<< orphan*/  iwl_mvm_agg_rx_received (struct iwl_mvm*,int,int) ; 
 scalar_t__ iwl_mvm_create_skb (struct iwl_mvm*,struct sk_buff*,struct ieee80211_hdr*,int,int,struct iwl_rx_cmd_buffer*) ; 
 int /*<<< orphan*/  iwl_mvm_decode_lsig (struct sk_buff*,struct iwl_mvm_rx_phy_data*) ; 
 int /*<<< orphan*/  iwl_mvm_flip_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_get_signal_strength (struct iwl_mvm*,struct ieee80211_rx_status*,int,int,int) ; 
 scalar_t__ iwl_mvm_is_dup (struct ieee80211_sta*,int,struct ieee80211_rx_status*,struct ieee80211_hdr*,struct iwl_rx_mpdu_desc*) ; 
 int iwl_mvm_legacy_rate_to_mac80211_idx (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_pass_packet_to_mac80211 (struct iwl_mvm*,struct napi_struct*,struct sk_buff*,int,struct ieee80211_sta*,int) ; 
 int /*<<< orphan*/  iwl_mvm_reorder (struct iwl_mvm*,struct napi_struct*,int,struct ieee80211_sta*,struct sk_buff*,struct iwl_rx_mpdu_desc*) ; 
 scalar_t__ iwl_mvm_rx_crypto (struct iwl_mvm*,struct ieee80211_hdr*,struct ieee80211_rx_status*,int,struct iwl_rx_mpdu_desc*,int,int,int*) ; 
 int /*<<< orphan*/  iwl_mvm_rx_csum (struct ieee80211_sta*,struct sk_buff*,struct iwl_rx_mpdu_desc*) ; 
 int /*<<< orphan*/  iwl_mvm_rx_he (struct iwl_mvm*,struct sk_buff*,struct iwl_mvm_rx_phy_data*,int,int,int) ; 
 struct iwl_mvm_sta* iwl_mvm_sta_from_mac80211 (struct ieee80211_sta*) ; 
 int /*<<< orphan*/  iwl_mvm_sta_modify_disable_tx_ap (struct iwl_mvm*,struct ieee80211_sta*,int) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  ktime_get_boottime_ns () ; 
 int le16_to_cpu (int) ; 
 int /*<<< orphan*/  le32_get_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 void* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  rs_update_last_rssi (struct iwl_mvm*,struct iwl_mvm_sta*,struct ieee80211_rx_status*) ; 
 struct iwl_rx_packet* rxb_addr (struct iwl_rx_cmd_buffer*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

void iwl_mvm_rx_mpdu_mq(struct iwl_mvm *mvm, struct napi_struct *napi,
			struct iwl_rx_cmd_buffer *rxb, int queue)
{
	struct ieee80211_rx_status *rx_status;
	struct iwl_rx_packet *pkt = rxb_addr(rxb);
	struct iwl_rx_mpdu_desc *desc = (void *)pkt->data;
	struct ieee80211_hdr *hdr;
	u32 len = le16_to_cpu(desc->mpdu_len);
	u32 rate_n_flags, gp2_on_air_rise;
	u16 phy_info = le16_to_cpu(desc->phy_info);
	struct ieee80211_sta *sta = NULL;
	struct sk_buff *skb;
	u8 crypt_len = 0, channel, energy_a, energy_b;
	size_t desc_size;
	struct iwl_mvm_rx_phy_data phy_data = {
		.d4 = desc->phy_data4,
		.info_type = IWL_RX_PHY_INFO_TYPE_NONE,
	};
	bool csi = false;

	if (unlikely(test_bit(IWL_MVM_STATUS_IN_HW_RESTART, &mvm->status)))
		return;

	if (mvm->trans->trans_cfg->device_family >= IWL_DEVICE_FAMILY_22560) {
		rate_n_flags = le32_to_cpu(desc->v3.rate_n_flags);
		channel = desc->v3.channel;
		gp2_on_air_rise = le32_to_cpu(desc->v3.gp2_on_air_rise);
		energy_a = desc->v3.energy_a;
		energy_b = desc->v3.energy_b;
		desc_size = sizeof(*desc);

		phy_data.d0 = desc->v3.phy_data0;
		phy_data.d1 = desc->v3.phy_data1;
		phy_data.d2 = desc->v3.phy_data2;
		phy_data.d3 = desc->v3.phy_data3;
	} else {
		rate_n_flags = le32_to_cpu(desc->v1.rate_n_flags);
		channel = desc->v1.channel;
		gp2_on_air_rise = le32_to_cpu(desc->v1.gp2_on_air_rise);
		energy_a = desc->v1.energy_a;
		energy_b = desc->v1.energy_b;
		desc_size = IWL_RX_DESC_SIZE_V1;

		phy_data.d0 = desc->v1.phy_data0;
		phy_data.d1 = desc->v1.phy_data1;
		phy_data.d2 = desc->v1.phy_data2;
		phy_data.d3 = desc->v1.phy_data3;
	}

	if (phy_info & IWL_RX_MPDU_PHY_TSF_OVERLOAD)
		phy_data.info_type =
			le32_get_bits(phy_data.d1,
				      IWL_RX_PHY_DATA1_INFO_TYPE_MASK);

	hdr = (void *)(pkt->data + desc_size);
	/* Dont use dev_alloc_skb(), we'll have enough headroom once
	 * ieee80211_hdr pulled.
	 */
	skb = alloc_skb(128, GFP_ATOMIC);
	if (!skb) {
		IWL_ERR(mvm, "alloc_skb failed\n");
		return;
	}

	if (desc->mac_flags2 & IWL_RX_MPDU_MFLG2_PAD) {
		/*
		 * If the device inserted padding it means that (it thought)
		 * the 802.11 header wasn't a multiple of 4 bytes long. In
		 * this case, reserve two bytes at the start of the SKB to
		 * align the payload properly in case we end up copying it.
		 */
		skb_reserve(skb, 2);
	}

	rx_status = IEEE80211_SKB_RXCB(skb);

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

	rx_status = IEEE80211_SKB_RXCB(skb);

	if (iwl_mvm_rx_crypto(mvm, hdr, rx_status, phy_info, desc,
			      le32_to_cpu(pkt->len_n_flags), queue,
			      &crypt_len)) {
		kfree_skb(skb);
		return;
	}

	/*
	 * Keep packets with CRC errors (and with overrun) for monitor mode
	 * (otherwise the firmware discards them) but mark them as bad.
	 */
	if (!(desc->status & cpu_to_le16(IWL_RX_MPDU_STATUS_CRC_OK)) ||
	    !(desc->status & cpu_to_le16(IWL_RX_MPDU_STATUS_OVERRUN_OK))) {
		IWL_DEBUG_RX(mvm, "Bad CRC or FIFO: 0x%08X.\n",
			     le16_to_cpu(desc->status));
		rx_status->flag |= RX_FLAG_FAILED_FCS_CRC;
	}
	/* set the preamble flag if appropriate */
	if (rate_n_flags & RATE_MCS_CCK_MSK &&
	    phy_info & IWL_RX_MPDU_PHY_SHORT_PREAMBLE)
		rx_status->enc_flags |= RX_ENC_FLAG_SHORTPRE;

	if (likely(!(phy_info & IWL_RX_MPDU_PHY_TSF_OVERLOAD))) {
		u64 tsf_on_air_rise;

		if (mvm->trans->trans_cfg->device_family >=
		    IWL_DEVICE_FAMILY_22560)
			tsf_on_air_rise = le64_to_cpu(desc->v3.tsf_on_air_rise);
		else
			tsf_on_air_rise = le64_to_cpu(desc->v1.tsf_on_air_rise);

		rx_status->mactime = tsf_on_air_rise;
		/* TSF as indicated by the firmware is at INA time */
		rx_status->flag |= RX_FLAG_MACTIME_PLCP_START;
	}

	rx_status->device_timestamp = gp2_on_air_rise;
	rx_status->band = channel > 14 ? NL80211_BAND_5GHZ :
		NL80211_BAND_2GHZ;
	rx_status->freq = ieee80211_channel_to_frequency(channel,
							 rx_status->band);
	iwl_mvm_get_signal_strength(mvm, rx_status, rate_n_flags, energy_a,
				    energy_b);

	/* update aggregation data for monitor sake on default queue */
	if (!queue && (phy_info & IWL_RX_MPDU_PHY_AMPDU)) {
		bool toggle_bit = phy_info & IWL_RX_MPDU_PHY_AMPDU_TOGGLE;

		rx_status->flag |= RX_FLAG_AMPDU_DETAILS;
		/*
		 * Toggle is switched whenever new aggregation starts. Make
		 * sure ampdu_reference is never 0 so we can later use it to
		 * see if the frame was really part of an A-MPDU or not.
		 */
		if (toggle_bit != mvm->ampdu_toggle) {
			mvm->ampdu_ref++;
			if (mvm->ampdu_ref == 0)
				mvm->ampdu_ref++;
			mvm->ampdu_toggle = toggle_bit;
		}
		rx_status->ampdu_reference = mvm->ampdu_ref;
	}

	if (unlikely(mvm->monitor_on))
		iwl_mvm_add_rtap_sniffer_config(mvm, skb);

	rcu_read_lock();

	if (desc->status & cpu_to_le16(IWL_RX_MPDU_STATUS_SRC_STA_FOUND)) {
		u8 id = desc->sta_id_flags & IWL_RX_MPDU_SIF_STA_ID_MASK;

		if (!WARN_ON_ONCE(id >= ARRAY_SIZE(mvm->fw_id_to_mac_id))) {
			sta = rcu_dereference(mvm->fw_id_to_mac_id[id]);
			if (IS_ERR(sta))
				sta = NULL;
		}
	} else if (!is_multicast_ether_addr(hdr->addr2)) {
		/*
		 * This is fine since we prevent two stations with the same
		 * address from being added.
		 */
		sta = ieee80211_find_sta_by_ifaddr(mvm->hw, hdr->addr2, NULL);
	}

	if (sta) {
		struct iwl_mvm_sta *mvmsta = iwl_mvm_sta_from_mac80211(sta);
		struct ieee80211_vif *tx_blocked_vif =
			rcu_dereference(mvm->csa_tx_blocked_vif);
		u8 baid = (u8)((le32_to_cpu(desc->reorder_data) &
			       IWL_RX_MPDU_REORDER_BAID_MASK) >>
			       IWL_RX_MPDU_REORDER_BAID_SHIFT);
		struct iwl_fw_dbg_trigger_tlv *trig;
		struct ieee80211_vif *vif = mvmsta->vif;

		if (!mvm->tcm.paused && len >= sizeof(*hdr) &&
		    !is_multicast_ether_addr(hdr->addr1) &&
		    ieee80211_is_data(hdr->frame_control) &&
		    time_after(jiffies, mvm->tcm.ts + MVM_TCM_PERIOD))
			schedule_delayed_work(&mvm->tcm.work, 0);

		/*
		 * We have tx blocked stations (with CS bit). If we heard
		 * frames from a blocked station on a new channel we can
		 * TX to it again.
		 */
		if (unlikely(tx_blocked_vif) && tx_blocked_vif == vif) {
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

		if (ieee80211_is_data(hdr->frame_control))
			iwl_mvm_rx_csum(sta, skb, desc);

		if (iwl_mvm_is_dup(sta, queue, rx_status, hdr, desc)) {
			kfree_skb(skb);
			goto out;
		}

		/*
		 * Our hardware de-aggregates AMSDUs but copies the mac header
		 * as it to the de-aggregated MPDUs. We need to turn off the
		 * AMSDU bit in the QoS control ourselves.
		 * In addition, HW reverses addr3 and addr4 - reverse it back.
		 */
		if ((desc->mac_flags2 & IWL_RX_MPDU_MFLG2_AMSDU) &&
		    !WARN_ON(!ieee80211_is_data_qos(hdr->frame_control))) {
			u8 *qc = ieee80211_get_qos_ctl(hdr);

			*qc &= ~IEEE80211_QOS_CTL_A_MSDU_PRESENT;

			if (mvm->trans->trans_cfg->device_family ==
			    IWL_DEVICE_FAMILY_9000) {
				iwl_mvm_flip_address(hdr->addr3);

				if (ieee80211_has_a4(hdr->frame_control))
					iwl_mvm_flip_address(hdr->addr4);
			}
		}
		if (baid != IWL_RX_REORDER_DATA_INVALID_BAID) {
			u32 reorder_data = le32_to_cpu(desc->reorder_data);

			iwl_mvm_agg_rx_received(mvm, reorder_data, baid);
		}
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
	} else if (!(rate_n_flags & RATE_MCS_HE_MSK)) {
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

	/* management stuff on default queue */
	if (!queue) {
		if (unlikely((ieee80211_is_beacon(hdr->frame_control) ||
			      ieee80211_is_probe_resp(hdr->frame_control)) &&
			     mvm->sched_scan_pass_all ==
			     SCHED_SCAN_PASS_ALL_ENABLED))
			mvm->sched_scan_pass_all = SCHED_SCAN_PASS_ALL_FOUND;

		if (unlikely(ieee80211_is_beacon(hdr->frame_control) ||
			     ieee80211_is_probe_resp(hdr->frame_control)))
			rx_status->boottime_ns = ktime_get_boottime_ns();
	}

	if (iwl_mvm_create_skb(mvm, skb, hdr, len, crypt_len, rxb)) {
		kfree_skb(skb);
		goto out;
	}

	if (!iwl_mvm_reorder(mvm, napi, queue, sta, skb, desc))
		iwl_mvm_pass_packet_to_mac80211(mvm, napi, skb, queue,
						sta, csi);
out:
	rcu_read_unlock();
}