#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct mt7601u_dev {int /*<<< orphan*/  mac_lock; int /*<<< orphan*/  hw; } ;
struct TYPE_4__ {TYPE_1__* rates; } ;
struct ieee80211_tx_info {int /*<<< orphan*/  flags; TYPE_2__ status; } ;
struct TYPE_3__ {int idx; } ;

/* Variables and functions */
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  IEEE80211_TX_STAT_ACK ; 
 int /*<<< orphan*/  ieee80211_tx_info_clear_status (struct ieee80211_tx_info*) ; 
 int /*<<< orphan*/  ieee80211_tx_status (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  mt7601u_tx_skb_remove_dma_overhead (struct sk_buff*,struct ieee80211_tx_info*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void mt7601u_tx_status(struct mt7601u_dev *dev, struct sk_buff *skb)
{
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);

	mt7601u_tx_skb_remove_dma_overhead(skb, info);

	ieee80211_tx_info_clear_status(info);
	info->status.rates[0].idx = -1;
	info->flags |= IEEE80211_TX_STAT_ACK;

	spin_lock_bh(&dev->mac_lock);
	ieee80211_tx_status(dev->hw, skb);
	spin_unlock_bh(&dev->mac_lock);
}