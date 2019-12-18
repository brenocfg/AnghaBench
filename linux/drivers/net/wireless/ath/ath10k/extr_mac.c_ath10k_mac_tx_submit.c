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
struct ath10k_htt {int dummy; } ;
struct ath10k {int /*<<< orphan*/  hw; struct ath10k_htt htt; } ;
typedef  enum ath10k_mac_tx_path { ____Placeholder_ath10k_mac_tx_path } ath10k_mac_tx_path ;
typedef  enum ath10k_hw_txrx_mode { ____Placeholder_ath10k_hw_txrx_mode } ath10k_hw_txrx_mode ;

/* Variables and functions */
#define  ATH10K_MAC_TX_HTT 131 
#define  ATH10K_MAC_TX_HTT_MGMT 130 
#define  ATH10K_MAC_TX_UNKNOWN 129 
#define  ATH10K_MAC_TX_WMI_MGMT 128 
 int EINVAL ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int ath10k_htt_mgmt_tx (struct ath10k_htt*,struct sk_buff*) ; 
 int ath10k_htt_tx (struct ath10k_htt*,int,struct sk_buff*) ; 
 int ath10k_mac_tx_wmi_mgmt (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 int /*<<< orphan*/  ieee80211_free_txskb (int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static int ath10k_mac_tx_submit(struct ath10k *ar,
				enum ath10k_hw_txrx_mode txmode,
				enum ath10k_mac_tx_path txpath,
				struct sk_buff *skb)
{
	struct ath10k_htt *htt = &ar->htt;
	int ret = -EINVAL;

	switch (txpath) {
	case ATH10K_MAC_TX_HTT:
		ret = ath10k_htt_tx(htt, txmode, skb);
		break;
	case ATH10K_MAC_TX_HTT_MGMT:
		ret = ath10k_htt_mgmt_tx(htt, skb);
		break;
	case ATH10K_MAC_TX_WMI_MGMT:
		ret = ath10k_mac_tx_wmi_mgmt(ar, skb);
		break;
	case ATH10K_MAC_TX_UNKNOWN:
		WARN_ON_ONCE(1);
		ret = -EINVAL;
		break;
	}

	if (ret) {
		ath10k_warn(ar, "failed to transmit packet, dropping: %d\n",
			    ret);
		ieee80211_free_txskb(ar->hw, skb);
	}

	return ret;
}