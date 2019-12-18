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
struct ieee80211_vif {int dummy; } ;
struct ieee80211_tx_info {int flags; } ;
struct ieee80211_hw {int dummy; } ;
struct ath10k_skb_cb {int flags; } ;
struct ath10k {int /*<<< orphan*/  offchan_tx_work; int /*<<< orphan*/  offchan_tx_queue; int /*<<< orphan*/  dev_flags; struct ieee80211_hw* hw; } ;
typedef  enum ath10k_mac_tx_path { ____Placeholder_ath10k_mac_tx_path } ath10k_mac_tx_path ;
typedef  enum ath10k_hw_txrx_mode { ____Placeholder_ath10k_hw_txrx_mode } ath10k_hw_txrx_mode ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_MAC ; 
 int /*<<< orphan*/  ATH10K_FLAG_RAW_MODE ; 
#define  ATH10K_HW_TXRX_ETHERNET 131 
#define  ATH10K_HW_TXRX_MGMT 130 
#define  ATH10K_HW_TXRX_NATIVE_WIFI 129 
#define  ATH10K_HW_TXRX_RAW 128 
 struct ath10k_skb_cb* ATH10K_SKB_CB (struct sk_buff*) ; 
 int ATH10K_SKB_F_RAW_TX ; 
 int ENOTSUPP ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_CTL_NO_CCK_RATE ; 
 int IEEE80211_TX_CTL_TX_OFFCHAN ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ath10k_mac_tx_frm_has_freq (struct ath10k*) ; 
 int ath10k_mac_tx_submit (struct ath10k*,int,int,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_tx_h_8023 (struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_tx_h_add_p2p_noa_ie (struct ath10k*,struct ieee80211_vif*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_tx_h_nwifi (struct ieee80211_hw*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_tx_h_seq_no (struct ieee80211_vif*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 int /*<<< orphan*/  ieee80211_free_txskb (struct ieee80211_hw*,struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_queue_work (struct ieee80211_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath10k_mac_tx(struct ath10k *ar,
			 struct ieee80211_vif *vif,
			 enum ath10k_hw_txrx_mode txmode,
			 enum ath10k_mac_tx_path txpath,
			 struct sk_buff *skb)
{
	struct ieee80211_hw *hw = ar->hw;
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	const struct ath10k_skb_cb *skb_cb = ATH10K_SKB_CB(skb);
	int ret;

	/* We should disable CCK RATE due to P2P */
	if (info->flags & IEEE80211_TX_CTL_NO_CCK_RATE)
		ath10k_dbg(ar, ATH10K_DBG_MAC, "IEEE80211_TX_CTL_NO_CCK_RATE\n");

	switch (txmode) {
	case ATH10K_HW_TXRX_MGMT:
	case ATH10K_HW_TXRX_NATIVE_WIFI:
		ath10k_tx_h_nwifi(hw, skb);
		ath10k_tx_h_add_p2p_noa_ie(ar, vif, skb);
		ath10k_tx_h_seq_no(vif, skb);
		break;
	case ATH10K_HW_TXRX_ETHERNET:
		ath10k_tx_h_8023(skb);
		break;
	case ATH10K_HW_TXRX_RAW:
		if (!test_bit(ATH10K_FLAG_RAW_MODE, &ar->dev_flags) &&
		    !(skb_cb->flags & ATH10K_SKB_F_RAW_TX)) {
			WARN_ON_ONCE(1);
			ieee80211_free_txskb(hw, skb);
			return -ENOTSUPP;
		}
	}

	if (info->flags & IEEE80211_TX_CTL_TX_OFFCHAN) {
		if (!ath10k_mac_tx_frm_has_freq(ar)) {
			ath10k_dbg(ar, ATH10K_DBG_MAC, "queued offchannel skb %pK\n",
				   skb);

			skb_queue_tail(&ar->offchan_tx_queue, skb);
			ieee80211_queue_work(hw, &ar->offchan_tx_work);
			return 0;
		}
	}

	ret = ath10k_mac_tx_submit(ar, txmode, txpath, skb);
	if (ret) {
		ath10k_warn(ar, "failed to submit frame: %d\n", ret);
		return ret;
	}

	return 0;
}