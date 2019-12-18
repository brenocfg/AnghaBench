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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {size_t len; scalar_t__ data; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_txq {struct ieee80211_sta* sta; struct ieee80211_vif* vif; scalar_t__ drv_priv; } ;
struct ieee80211_sta {int dummy; } ;
struct ieee80211_hw {struct ath10k* priv; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
struct ath10k_txq {int /*<<< orphan*/  num_fw_queued; } ;
struct ath10k_htt {int /*<<< orphan*/  tx_lock; } ;
struct ath10k {struct ath10k_htt htt; } ;
typedef  enum ath10k_mac_tx_path { ____Placeholder_ath10k_mac_tx_path } ath10k_mac_tx_path ;
typedef  enum ath10k_hw_txrx_mode { ____Placeholder_ath10k_hw_txrx_mode } ath10k_hw_txrx_mode ;

/* Variables and functions */
 int ATH10K_MAC_TX_HTT_MGMT ; 
 int ENOENT ; 
 int /*<<< orphan*/  ath10k_htt_tx_dec_pending (struct ath10k_htt*) ; 
 int ath10k_htt_tx_inc_pending (struct ath10k_htt*) ; 
 int /*<<< orphan*/  ath10k_htt_tx_mgmt_dec_pending (struct ath10k_htt*) ; 
 int ath10k_htt_tx_mgmt_inc_pending (struct ath10k_htt*,int,int) ; 
 int ath10k_mac_tx (struct ath10k*,struct ieee80211_vif*,int,int,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_mac_tx_h_fill_cb (struct ath10k*,struct ieee80211_vif*,struct ieee80211_txq*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int ath10k_mac_tx_h_get_txmode (struct ath10k*,struct ieee80211_vif*,struct ieee80211_sta*,struct sk_buff*) ; 
 int ath10k_mac_tx_h_get_txpath (struct ath10k*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  ath10k_mac_update_airtime (struct ath10k*,struct ieee80211_txq*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 int ieee80211_is_probe_resp (int /*<<< orphan*/ ) ; 
 struct sk_buff* ieee80211_tx_dequeue (struct ieee80211_hw*,struct ieee80211_txq*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int ath10k_mac_tx_push_txq(struct ieee80211_hw *hw,
			   struct ieee80211_txq *txq)
{
	struct ath10k *ar = hw->priv;
	struct ath10k_htt *htt = &ar->htt;
	struct ath10k_txq *artxq = (void *)txq->drv_priv;
	struct ieee80211_vif *vif = txq->vif;
	struct ieee80211_sta *sta = txq->sta;
	enum ath10k_hw_txrx_mode txmode;
	enum ath10k_mac_tx_path txpath;
	struct sk_buff *skb;
	struct ieee80211_hdr *hdr;
	size_t skb_len;
	bool is_mgmt, is_presp;
	int ret;
	u16 airtime;

	spin_lock_bh(&ar->htt.tx_lock);
	ret = ath10k_htt_tx_inc_pending(htt);
	spin_unlock_bh(&ar->htt.tx_lock);

	if (ret)
		return ret;

	skb = ieee80211_tx_dequeue(hw, txq);
	if (!skb) {
		spin_lock_bh(&ar->htt.tx_lock);
		ath10k_htt_tx_dec_pending(htt);
		spin_unlock_bh(&ar->htt.tx_lock);

		return -ENOENT;
	}

	airtime = ath10k_mac_update_airtime(ar, txq, skb);
	ath10k_mac_tx_h_fill_cb(ar, vif, txq, skb, airtime);

	skb_len = skb->len;
	txmode = ath10k_mac_tx_h_get_txmode(ar, vif, sta, skb);
	txpath = ath10k_mac_tx_h_get_txpath(ar, skb, txmode);
	is_mgmt = (txpath == ATH10K_MAC_TX_HTT_MGMT);

	if (is_mgmt) {
		hdr = (struct ieee80211_hdr *)skb->data;
		is_presp = ieee80211_is_probe_resp(hdr->frame_control);

		spin_lock_bh(&ar->htt.tx_lock);
		ret = ath10k_htt_tx_mgmt_inc_pending(htt, is_mgmt, is_presp);

		if (ret) {
			ath10k_htt_tx_dec_pending(htt);
			spin_unlock_bh(&ar->htt.tx_lock);
			return ret;
		}
		spin_unlock_bh(&ar->htt.tx_lock);
	}

	ret = ath10k_mac_tx(ar, vif, txmode, txpath, skb);
	if (unlikely(ret)) {
		ath10k_warn(ar, "failed to push frame: %d\n", ret);

		spin_lock_bh(&ar->htt.tx_lock);
		ath10k_htt_tx_dec_pending(htt);
		if (is_mgmt)
			ath10k_htt_tx_mgmt_dec_pending(htt);
		spin_unlock_bh(&ar->htt.tx_lock);

		return ret;
	}

	spin_lock_bh(&ar->htt.tx_lock);
	artxq->num_fw_queued++;
	spin_unlock_bh(&ar->htt.tx_lock);

	return skb_len;
}