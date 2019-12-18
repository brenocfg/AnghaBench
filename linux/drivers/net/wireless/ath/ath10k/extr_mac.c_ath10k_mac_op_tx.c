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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {scalar_t__ data; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_txq {int dummy; } ;
struct TYPE_2__ {struct ieee80211_vif* vif; } ;
struct ieee80211_tx_info {TYPE_1__ control; } ;
struct ieee80211_tx_control {struct ieee80211_sta* sta; } ;
struct ieee80211_sta {int dummy; } ;
struct ieee80211_hw {struct ath10k* priv; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
struct ath10k_htt {int /*<<< orphan*/  tx_lock; } ;
struct ath10k {struct ath10k_htt htt; int /*<<< orphan*/  hw; } ;
typedef  enum ath10k_mac_tx_path { ____Placeholder_ath10k_mac_tx_path } ath10k_mac_tx_path ;
typedef  enum ath10k_hw_txrx_mode { ____Placeholder_ath10k_hw_txrx_mode } ath10k_hw_txrx_mode ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_MAC ; 
 int ATH10K_MAC_TX_HTT ; 
 int ATH10K_MAC_TX_HTT_MGMT ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int) ; 
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
 int /*<<< orphan*/  ieee80211_free_txskb (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int ieee80211_is_probe_resp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath10k_mac_op_tx(struct ieee80211_hw *hw,
			     struct ieee80211_tx_control *control,
			     struct sk_buff *skb)
{
	struct ath10k *ar = hw->priv;
	struct ath10k_htt *htt = &ar->htt;
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	struct ieee80211_vif *vif = info->control.vif;
	struct ieee80211_sta *sta = control->sta;
	struct ieee80211_txq *txq = NULL;
	struct ieee80211_hdr *hdr = (void *)skb->data;
	enum ath10k_hw_txrx_mode txmode;
	enum ath10k_mac_tx_path txpath;
	bool is_htt;
	bool is_mgmt;
	bool is_presp;
	int ret;
	u16 airtime;

	airtime = ath10k_mac_update_airtime(ar, txq, skb);
	ath10k_mac_tx_h_fill_cb(ar, vif, txq, skb, airtime);

	txmode = ath10k_mac_tx_h_get_txmode(ar, vif, sta, skb);
	txpath = ath10k_mac_tx_h_get_txpath(ar, skb, txmode);
	is_htt = (txpath == ATH10K_MAC_TX_HTT ||
		  txpath == ATH10K_MAC_TX_HTT_MGMT);
	is_mgmt = (txpath == ATH10K_MAC_TX_HTT_MGMT);

	if (is_htt) {
		spin_lock_bh(&ar->htt.tx_lock);
		is_presp = ieee80211_is_probe_resp(hdr->frame_control);

		ret = ath10k_htt_tx_inc_pending(htt);
		if (ret) {
			ath10k_warn(ar, "failed to increase tx pending count: %d, dropping\n",
				    ret);
			spin_unlock_bh(&ar->htt.tx_lock);
			ieee80211_free_txskb(ar->hw, skb);
			return;
		}

		ret = ath10k_htt_tx_mgmt_inc_pending(htt, is_mgmt, is_presp);
		if (ret) {
			ath10k_dbg(ar, ATH10K_DBG_MAC, "failed to increase tx mgmt pending count: %d, dropping\n",
				   ret);
			ath10k_htt_tx_dec_pending(htt);
			spin_unlock_bh(&ar->htt.tx_lock);
			ieee80211_free_txskb(ar->hw, skb);
			return;
		}
		spin_unlock_bh(&ar->htt.tx_lock);
	}

	ret = ath10k_mac_tx(ar, vif, txmode, txpath, skb);
	if (ret) {
		ath10k_warn(ar, "failed to transmit frame: %d\n", ret);
		if (is_htt) {
			spin_lock_bh(&ar->htt.tx_lock);
			ath10k_htt_tx_dec_pending(htt);
			if (is_mgmt)
				ath10k_htt_tx_mgmt_dec_pending(htt);
			spin_unlock_bh(&ar->htt.tx_lock);
		}
		return;
	}
}