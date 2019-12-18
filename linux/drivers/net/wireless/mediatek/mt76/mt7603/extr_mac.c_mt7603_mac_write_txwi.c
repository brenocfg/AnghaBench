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
typedef  int u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct sk_buff {int len; int priority; scalar_t__ data; } ;
struct mt76_wcid {int idx; } ;
struct mt76_queue {int hw_idx; } ;
struct mt7603_vif {int idx; } ;
struct mt7603_sta {int rate_count; } ;
struct TYPE_6__ {TYPE_2__* q_tx; } ;
struct mt7603_dev {TYPE_3__ mt76; } ;
struct ieee80211_vif {scalar_t__ drv_priv; } ;
struct ieee80211_tx_rate {scalar_t__ idx; int count; int flags; } ;
struct TYPE_4__ {struct ieee80211_vif* vif; struct ieee80211_tx_rate* rates; } ;
struct ieee80211_tx_info {int flags; TYPE_1__ control; } ;
struct ieee80211_sta {scalar_t__ drv_priv; } ;
struct ieee80211_key_conf {int /*<<< orphan*/  tx_pn; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; int /*<<< orphan*/  seq_ctrl; int /*<<< orphan*/  addr1; } ;
struct ieee80211_bar {int /*<<< orphan*/  start_seq_num; } ;
typedef  enum mt76_txq_id { ____Placeholder_mt76_txq_id } mt76_txq_id ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_5__ {struct mt76_queue* q; } ;

/* Variables and functions */
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int GENMASK (int,int /*<<< orphan*/ ) ; 
 int IEEE80211_FCTL_FTYPE ; 
 int IEEE80211_FCTL_STYPE ; 
 int IEEE80211_QOS_CTL_TID_MASK ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_CTL_AMPDU ; 
 int IEEE80211_TX_CTL_NO_ACK ; 
 int IEEE80211_TX_CTL_RATE_CTRL_PROBE ; 
 int IEEE80211_TX_CTL_STBC ; 
 int IEEE80211_TX_RC_MCS ; 
 int IEEE80211_TX_RC_SHORT_GI ; 
 int MT7603_WTBL_RESERVED ; 
 int MT_HDR_FORMAT_802_11 ; 
 int /*<<< orphan*/  MT_TXD0_Q_IDX ; 
 int /*<<< orphan*/  MT_TXD0_TX_BYTES ; 
 int /*<<< orphan*/  MT_TXD1_HDR_FORMAT ; 
 int /*<<< orphan*/  MT_TXD1_HDR_INFO ; 
 int MT_TXD1_LONG_FORMAT ; 
 int MT_TXD1_NO_ACK ; 
 int /*<<< orphan*/  MT_TXD1_OWN_MAC ; 
 int /*<<< orphan*/  MT_TXD1_PROTECTED ; 
 int /*<<< orphan*/  MT_TXD1_TID ; 
 int /*<<< orphan*/  MT_TXD1_WLAN_IDX ; 
 int MT_TXD2_BA_DISABLE ; 
 int MT_TXD2_FIX_RATE ; 
 int /*<<< orphan*/  MT_TXD2_FRAME_TYPE ; 
 int /*<<< orphan*/  MT_TXD2_MULTICAST ; 
 int /*<<< orphan*/  MT_TXD2_SUB_TYPE ; 
 int MT_TXD3_PN_VALID ; 
 int /*<<< orphan*/  MT_TXD3_REM_TX_COUNT ; 
 int /*<<< orphan*/  MT_TXD3_SEQ ; 
 int MT_TXD3_SN_VALID ; 
 int /*<<< orphan*/  MT_TXD5_PID ; 
 int /*<<< orphan*/  MT_TXD5_PN_HIGH ; 
 int MT_TXD5_SW_POWER_MGMT ; 
 int MT_TXD5_TX_STATUS_HOST ; 
 int /*<<< orphan*/  MT_TXD6_BW ; 
 int MT_TXD6_FIXED_BW ; 
 int MT_TXD6_SGI ; 
 int /*<<< orphan*/  MT_TXD6_TX_RATE ; 
 int MT_TXD_SIZE ; 
 int MT_TXQ_BEACON ; 
 int atomic64_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int ieee80211_get_hdrlen_from_skb (struct sk_buff*) ; 
 scalar_t__ ieee80211_is_back_req (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_data_qos (int /*<<< orphan*/ ) ; 
 int is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int mt7603_mac_tx_rate_val (struct mt7603_dev*,struct ieee80211_tx_rate*,int,int*) ; 

__attribute__((used)) static int
mt7603_mac_write_txwi(struct mt7603_dev *dev, __le32 *txwi,
		      struct sk_buff *skb, enum mt76_txq_id qid,
		      struct mt76_wcid *wcid, struct ieee80211_sta *sta,
		      int pid, struct ieee80211_key_conf *key)
{
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	struct ieee80211_tx_rate *rate = &info->control.rates[0];
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)skb->data;
	struct ieee80211_bar *bar = (struct ieee80211_bar *)skb->data;
	struct ieee80211_vif *vif = info->control.vif;
	struct mt76_queue *q = dev->mt76.q_tx[qid].q;
	struct mt7603_vif *mvif;
	int wlan_idx;
	int hdr_len = ieee80211_get_hdrlen_from_skb(skb);
	int tx_count = 8;
	u8 frame_type, frame_subtype;
	u16 fc = le16_to_cpu(hdr->frame_control);
	u16 seqno = 0;
	u8 vif_idx = 0;
	u32 val;
	u8 bw;

	if (vif) {
		mvif = (struct mt7603_vif *)vif->drv_priv;
		vif_idx = mvif->idx;
		if (vif_idx && qid >= MT_TXQ_BEACON)
			vif_idx += 0x10;
	}

	if (sta) {
		struct mt7603_sta *msta = (struct mt7603_sta *)sta->drv_priv;

		tx_count = msta->rate_count;
	}

	if (wcid)
		wlan_idx = wcid->idx;
	else
		wlan_idx = MT7603_WTBL_RESERVED;

	frame_type = (fc & IEEE80211_FCTL_FTYPE) >> 2;
	frame_subtype = (fc & IEEE80211_FCTL_STYPE) >> 4;

	val = FIELD_PREP(MT_TXD0_TX_BYTES, skb->len + MT_TXD_SIZE) |
	      FIELD_PREP(MT_TXD0_Q_IDX, q->hw_idx);
	txwi[0] = cpu_to_le32(val);

	val = MT_TXD1_LONG_FORMAT |
	      FIELD_PREP(MT_TXD1_OWN_MAC, vif_idx) |
	      FIELD_PREP(MT_TXD1_TID,
			 skb->priority & IEEE80211_QOS_CTL_TID_MASK) |
	      FIELD_PREP(MT_TXD1_HDR_FORMAT, MT_HDR_FORMAT_802_11) |
	      FIELD_PREP(MT_TXD1_HDR_INFO, hdr_len / 2) |
	      FIELD_PREP(MT_TXD1_WLAN_IDX, wlan_idx) |
	      FIELD_PREP(MT_TXD1_PROTECTED, !!key);
	txwi[1] = cpu_to_le32(val);

	if (info->flags & IEEE80211_TX_CTL_NO_ACK)
		txwi[1] |= cpu_to_le32(MT_TXD1_NO_ACK);

	val = FIELD_PREP(MT_TXD2_FRAME_TYPE, frame_type) |
	      FIELD_PREP(MT_TXD2_SUB_TYPE, frame_subtype) |
	      FIELD_PREP(MT_TXD2_MULTICAST,
			 is_multicast_ether_addr(hdr->addr1));
	txwi[2] = cpu_to_le32(val);

	if (!(info->flags & IEEE80211_TX_CTL_AMPDU))
		txwi[2] |= cpu_to_le32(MT_TXD2_BA_DISABLE);

	txwi[4] = 0;

	val = MT_TXD5_TX_STATUS_HOST | MT_TXD5_SW_POWER_MGMT |
	      FIELD_PREP(MT_TXD5_PID, pid);
	txwi[5] = cpu_to_le32(val);

	txwi[6] = 0;

	if (rate->idx >= 0 && rate->count &&
	    !(info->flags & IEEE80211_TX_CTL_RATE_CTRL_PROBE)) {
		bool stbc = info->flags & IEEE80211_TX_CTL_STBC;
		u16 rateval = mt7603_mac_tx_rate_val(dev, rate, stbc, &bw);

		txwi[2] |= cpu_to_le32(MT_TXD2_FIX_RATE);

		val = MT_TXD6_FIXED_BW |
		      FIELD_PREP(MT_TXD6_BW, bw) |
		      FIELD_PREP(MT_TXD6_TX_RATE, rateval);
		txwi[6] |= cpu_to_le32(val);

		if (rate->flags & IEEE80211_TX_RC_SHORT_GI)
			txwi[6] |= cpu_to_le32(MT_TXD6_SGI);

		if (!(rate->flags & IEEE80211_TX_RC_MCS))
			txwi[2] |= cpu_to_le32(MT_TXD2_BA_DISABLE);

		tx_count = rate->count;
	}

	/* use maximum tx count for beacons and buffered multicast */
	if (qid >= MT_TXQ_BEACON)
		tx_count = 0x1f;

	val = FIELD_PREP(MT_TXD3_REM_TX_COUNT, tx_count) |
		  MT_TXD3_SN_VALID;

	if (ieee80211_is_data_qos(hdr->frame_control))
		seqno = le16_to_cpu(hdr->seq_ctrl);
	else if (ieee80211_is_back_req(hdr->frame_control))
		seqno = le16_to_cpu(bar->start_seq_num);
	else
		val &= ~MT_TXD3_SN_VALID;

	val |= FIELD_PREP(MT_TXD3_SEQ, seqno >> 4);

	txwi[3] = cpu_to_le32(val);

	if (key) {
		u64 pn = atomic64_inc_return(&key->tx_pn);

		txwi[3] |= cpu_to_le32(MT_TXD3_PN_VALID);
		txwi[4] = cpu_to_le32(pn & GENMASK(31, 0));
		txwi[5] |= cpu_to_le32(FIELD_PREP(MT_TXD5_PN_HIGH, pn >> 32));
	}

	txwi[7] = 0;

	return 0;
}