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
struct TYPE_2__ {int /*<<< orphan*/  hw_key; } ;
struct ieee80211_tx_info {TYPE_1__ control; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
struct ath10k_skb_cb {int /*<<< orphan*/  airtime_est; struct ieee80211_txq* txq; struct ieee80211_vif* vif; int /*<<< orphan*/  flags; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 struct ath10k_skb_cb* ATH10K_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  ATH10K_SKB_F_MGMT ; 
 int /*<<< orphan*/  ATH10K_SKB_F_NO_HWCRYPT ; 
 int /*<<< orphan*/  ATH10K_SKB_F_QOS ; 
 int /*<<< orphan*/  ATH10K_SKB_F_RAW_TX ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_tx_h_use_hwcrypto (struct ieee80211_vif*,struct sk_buff*) ; 
 scalar_t__ ieee80211_has_protected (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_data (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_data_qos (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_mgmt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath10k_mac_tx_h_fill_cb(struct ath10k *ar,
				    struct ieee80211_vif *vif,
				    struct ieee80211_txq *txq,
				    struct sk_buff *skb, u16 airtime)
{
	struct ieee80211_hdr *hdr = (void *)skb->data;
	struct ath10k_skb_cb *cb = ATH10K_SKB_CB(skb);
	const struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	bool is_data = ieee80211_is_data(hdr->frame_control) ||
			ieee80211_is_data_qos(hdr->frame_control);

	cb->flags = 0;
	if (!ath10k_tx_h_use_hwcrypto(vif, skb))
		cb->flags |= ATH10K_SKB_F_NO_HWCRYPT;

	if (ieee80211_is_mgmt(hdr->frame_control))
		cb->flags |= ATH10K_SKB_F_MGMT;

	if (ieee80211_is_data_qos(hdr->frame_control))
		cb->flags |= ATH10K_SKB_F_QOS;

	/* Data frames encrypted in software will be posted to firmware
	 * with tx encap mode set to RAW. Ex: Multicast traffic generated
	 * for a specific VLAN group will always be encrypted in software.
	 */
	if (is_data && ieee80211_has_protected(hdr->frame_control) &&
	    !info->control.hw_key) {
		cb->flags |= ATH10K_SKB_F_NO_HWCRYPT;
		cb->flags |= ATH10K_SKB_F_RAW_TX;
	}

	cb->vif = vif;
	cb->txq = txq;
	cb->airtime_est = airtime;
}