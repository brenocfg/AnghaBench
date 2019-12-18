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
struct sk_buff {scalar_t__ data; } ;
struct ieee80211_vif {scalar_t__ drv_priv; } ;
struct ieee80211_tx_info {int flags; } ;
struct ieee80211_hdr {int /*<<< orphan*/  seq_ctrl; } ;
struct ath10k_vif {int tx_seq_no; } ;

/* Variables and functions */
 int IEEE80211_SCTL_FRAG ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_CTL_ASSIGN_SEQ ; 
 int IEEE80211_TX_CTL_FIRST_FRAGMENT ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 

__attribute__((used)) static inline void ath10k_tx_h_seq_no(struct ieee80211_vif *vif,
				      struct sk_buff *skb)
{
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)skb->data;
	struct ath10k_vif *arvif = (void *)vif->drv_priv;

	if (info->flags  & IEEE80211_TX_CTL_ASSIGN_SEQ) {
		if (arvif->tx_seq_no == 0)
			arvif->tx_seq_no = 0x1000;

		if (info->flags & IEEE80211_TX_CTL_FIRST_FRAGMENT)
			arvif->tx_seq_no += 0x10;
		hdr->seq_ctrl &= cpu_to_le16(IEEE80211_SCTL_FRAG);
		hdr->seq_ctrl |= cpu_to_le16(arvif->tx_seq_no);
	}
}