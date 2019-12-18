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
typedef  int u16 ;
struct sk_buff {int len; int priority; scalar_t__ data; } ;
struct mt76_wcid {int idx; } ;
struct mt7615_vif {int omac_idx; int wmm_idx; } ;
struct mt7615_sta {int rate_count; } ;
struct mt7615_dev {int dummy; } ;
struct ieee80211_vif {scalar_t__ drv_priv; } ;
struct ieee80211_tx_rate {scalar_t__ idx; int count; int flags; } ;
struct TYPE_2__ {struct ieee80211_vif* vif; struct ieee80211_tx_rate* rates; } ;
struct ieee80211_tx_info {int flags; TYPE_1__ control; } ;
struct ieee80211_sta {scalar_t__ drv_priv; } ;
struct ieee80211_key_conf {scalar_t__ cipher; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; int /*<<< orphan*/  seq_ctrl; int /*<<< orphan*/  addr1; } ;
struct ieee80211_bar {int /*<<< orphan*/  start_seq_num; } ;
typedef  int __le32 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int IEEE80211_FCTL_FTYPE ; 
 int IEEE80211_FCTL_STYPE ; 
 int IEEE80211_QOS_CTL_TID_MASK ; 
 int IEEE80211_SEQ_TO_SN (int) ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_CTL_AMPDU ; 
 int IEEE80211_TX_CTL_LDPC ; 
 int IEEE80211_TX_CTL_NO_ACK ; 
 int IEEE80211_TX_CTL_RATE_CTRL_PROBE ; 
 int IEEE80211_TX_CTL_STBC ; 
 int IEEE80211_TX_RC_MCS ; 
 int IEEE80211_TX_RC_SHORT_GI ; 
 int IEEE80211_TX_RC_VHT_MCS ; 
 int MT7615_MAX_WMM_SETS ; 
 int MT_HDR_FORMAT_802_11 ; 
 int MT_LMAC_ALTX0 ; 
 int MT_LMAC_BCN0 ; 
 int /*<<< orphan*/  MT_TXD0_P_IDX ; 
 int /*<<< orphan*/  MT_TXD0_Q_IDX ; 
 int /*<<< orphan*/  MT_TXD0_TX_BYTES ; 
 int /*<<< orphan*/  MT_TXD1_HDR_FORMAT ; 
 int /*<<< orphan*/  MT_TXD1_HDR_INFO ; 
 int MT_TXD1_LONG_FORMAT ; 
 int /*<<< orphan*/  MT_TXD1_OWN_MAC ; 
 int /*<<< orphan*/  MT_TXD1_PKT_FMT ; 
 int /*<<< orphan*/  MT_TXD1_TID ; 
 int /*<<< orphan*/  MT_TXD1_WLAN_IDX ; 
 int MT_TXD2_BA_DISABLE ; 
 int MT_TXD2_BIP ; 
 int MT_TXD2_FIX_RATE ; 
 int /*<<< orphan*/  MT_TXD2_FRAME_TYPE ; 
 int /*<<< orphan*/  MT_TXD2_MULTICAST ; 
 int /*<<< orphan*/  MT_TXD2_SUB_TYPE ; 
 int MT_TXD3_NO_ACK ; 
 int MT_TXD3_PROTECT_FRAME ; 
 int /*<<< orphan*/  MT_TXD3_REM_TX_COUNT ; 
 int /*<<< orphan*/  MT_TXD3_SEQ ; 
 int MT_TXD3_SN_VALID ; 
 int /*<<< orphan*/  MT_TXD5_PID ; 
 int MT_TXD5_SW_POWER_MGMT ; 
 int MT_TXD5_TX_STATUS_HOST ; 
 int /*<<< orphan*/  MT_TXD6_BW ; 
 int MT_TXD6_FIXED_BW ; 
 int MT_TXD6_LDPC ; 
 int MT_TXD6_SGI ; 
 int /*<<< orphan*/  MT_TXD6_TX_RATE ; 
 int /*<<< orphan*/  MT_TXD7_SUB_TYPE ; 
 int /*<<< orphan*/  MT_TXD7_TYPE ; 
 int MT_TXD_SIZE ; 
 int MT_TX_PORT_IDX_LMAC ; 
 int MT_TX_TYPE_CT ; 
 int MT_TX_TYPE_FW ; 
 scalar_t__ WLAN_CIPHER_SUITE_AES_CMAC ; 
 int cpu_to_le32 (int) ; 
 int ieee80211_get_hdrlen_from_skb (struct sk_buff*) ; 
 scalar_t__ ieee80211_is_back_req (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_beacon (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_bufferable_mmpdu (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_data (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_data_qos (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_robust_mgmt_frame (struct sk_buff*) ; 
 int is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int mt7615_mac_tx_rate_val (struct mt7615_dev*,struct ieee80211_tx_rate*,int,int*) ; 
 int skb_get_queue_mapping (struct sk_buff*) ; 

int mt7615_mac_write_txwi(struct mt7615_dev *dev, __le32 *txwi,
			  struct sk_buff *skb, struct mt76_wcid *wcid,
			  struct ieee80211_sta *sta, int pid,
			  struct ieee80211_key_conf *key)
{
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	struct ieee80211_tx_rate *rate = &info->control.rates[0];
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)skb->data;
	bool multicast = is_multicast_ether_addr(hdr->addr1);
	struct ieee80211_vif *vif = info->control.vif;
	int tx_count = 8;
	u8 fc_type, fc_stype, p_fmt, q_idx, omac_idx = 0, wmm_idx = 0;
	__le16 fc = hdr->frame_control;
	u16 seqno = 0;
	u32 val;

	if (vif) {
		struct mt7615_vif *mvif = (struct mt7615_vif *)vif->drv_priv;

		omac_idx = mvif->omac_idx;
		wmm_idx = mvif->wmm_idx;
	}

	if (sta) {
		struct mt7615_sta *msta = (struct mt7615_sta *)sta->drv_priv;

		tx_count = msta->rate_count;
	}

	fc_type = (le16_to_cpu(fc) & IEEE80211_FCTL_FTYPE) >> 2;
	fc_stype = (le16_to_cpu(fc) & IEEE80211_FCTL_STYPE) >> 4;

	if (ieee80211_is_data(fc) || ieee80211_is_bufferable_mmpdu(fc)) {
		q_idx = wmm_idx * MT7615_MAX_WMM_SETS +
			skb_get_queue_mapping(skb);
		p_fmt = MT_TX_TYPE_CT;
	} else if (ieee80211_is_beacon(fc)) {
		q_idx = MT_LMAC_BCN0;
		p_fmt = MT_TX_TYPE_FW;
	} else {
		q_idx = MT_LMAC_ALTX0;
		p_fmt = MT_TX_TYPE_CT;
	}

	val = FIELD_PREP(MT_TXD0_TX_BYTES, skb->len + MT_TXD_SIZE) |
	      FIELD_PREP(MT_TXD0_P_IDX, MT_TX_PORT_IDX_LMAC) |
	      FIELD_PREP(MT_TXD0_Q_IDX, q_idx);
	txwi[0] = cpu_to_le32(val);

	val = MT_TXD1_LONG_FORMAT |
	      FIELD_PREP(MT_TXD1_WLAN_IDX, wcid->idx) |
	      FIELD_PREP(MT_TXD1_HDR_FORMAT, MT_HDR_FORMAT_802_11) |
	      FIELD_PREP(MT_TXD1_HDR_INFO,
			 ieee80211_get_hdrlen_from_skb(skb) / 2) |
	      FIELD_PREP(MT_TXD1_TID,
			 skb->priority & IEEE80211_QOS_CTL_TID_MASK) |
	      FIELD_PREP(MT_TXD1_PKT_FMT, p_fmt) |
	      FIELD_PREP(MT_TXD1_OWN_MAC, omac_idx);
	txwi[1] = cpu_to_le32(val);

	val = FIELD_PREP(MT_TXD2_FRAME_TYPE, fc_type) |
	      FIELD_PREP(MT_TXD2_SUB_TYPE, fc_stype) |
	      FIELD_PREP(MT_TXD2_MULTICAST, multicast);
	if (key) {
		if (multicast && ieee80211_is_robust_mgmt_frame(skb) &&
		    key->cipher == WLAN_CIPHER_SUITE_AES_CMAC) {
			val |= MT_TXD2_BIP;
			txwi[3] = 0;
		} else {
			txwi[3] = cpu_to_le32(MT_TXD3_PROTECT_FRAME);
		}
	} else {
		txwi[3] = 0;
	}
	txwi[2] = cpu_to_le32(val);

	if (!(info->flags & IEEE80211_TX_CTL_AMPDU))
		txwi[2] |= cpu_to_le32(MT_TXD2_BA_DISABLE);

	txwi[4] = 0;
	txwi[6] = 0;

	if (rate->idx >= 0 && rate->count &&
	    !(info->flags & IEEE80211_TX_CTL_RATE_CTRL_PROBE)) {
		bool stbc = info->flags & IEEE80211_TX_CTL_STBC;
		u8 bw;
		u16 rateval = mt7615_mac_tx_rate_val(dev, rate, stbc, &bw);

		txwi[2] |= cpu_to_le32(MT_TXD2_FIX_RATE);

		val = MT_TXD6_FIXED_BW |
		      FIELD_PREP(MT_TXD6_BW, bw) |
		      FIELD_PREP(MT_TXD6_TX_RATE, rateval);
		txwi[6] |= cpu_to_le32(val);

		if (rate->flags & IEEE80211_TX_RC_SHORT_GI)
			txwi[6] |= cpu_to_le32(MT_TXD6_SGI);

		if (info->flags & IEEE80211_TX_CTL_LDPC)
			txwi[6] |= cpu_to_le32(MT_TXD6_LDPC);

		if (!(rate->flags & (IEEE80211_TX_RC_MCS |
				     IEEE80211_TX_RC_VHT_MCS)))
			txwi[2] |= cpu_to_le32(MT_TXD2_BA_DISABLE);

		tx_count = rate->count;
	}

	if (!ieee80211_is_beacon(fc)) {
		val = MT_TXD5_TX_STATUS_HOST | MT_TXD5_SW_POWER_MGMT |
		      FIELD_PREP(MT_TXD5_PID, pid);
		txwi[5] = cpu_to_le32(val);
	} else {
		txwi[5] = 0;
		/* use maximum tx count for beacons */
		tx_count = 0x1f;
	}

	val = FIELD_PREP(MT_TXD3_REM_TX_COUNT, tx_count);
	if (ieee80211_is_data_qos(hdr->frame_control)) {
		seqno = IEEE80211_SEQ_TO_SN(le16_to_cpu(hdr->seq_ctrl));
		val |= MT_TXD3_SN_VALID;
	} else if (ieee80211_is_back_req(hdr->frame_control)) {
		struct ieee80211_bar *bar = (struct ieee80211_bar *)skb->data;

		seqno = IEEE80211_SEQ_TO_SN(le16_to_cpu(bar->start_seq_num));
		val |= MT_TXD3_SN_VALID;
	}
	val |= FIELD_PREP(MT_TXD3_SEQ, seqno);

	txwi[3] |= cpu_to_le32(val);

	if (info->flags & IEEE80211_TX_CTL_NO_ACK)
		txwi[3] |= cpu_to_le32(MT_TXD3_NO_ACK);

	txwi[7] = FIELD_PREP(MT_TXD7_TYPE, fc_type) |
		  FIELD_PREP(MT_TXD7_SUB_TYPE, fc_stype);

	return 0;
}