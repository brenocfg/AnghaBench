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
struct sk_buff {int dummy; } ;
struct mt76_wcid {int packet_id; int /*<<< orphan*/  idx; } ;
struct mt76_tx_cb {int pktid; int /*<<< orphan*/  jiffies; int /*<<< orphan*/  wcid; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct mt76_dev {TYPE_1__ status_list; } ;
struct ieee80211_tx_info {int flags; } ;

/* Variables and functions */
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_CTL_NO_ACK ; 
 int IEEE80211_TX_CTL_RATE_CTRL_PROBE ; 
 int IEEE80211_TX_CTL_REQ_TX_STATUS ; 
 int MT_PACKET_ID_FIRST ; 
 int MT_PACKET_ID_MASK ; 
 int MT_PACKET_ID_NO_ACK ; 
 int MT_PACKET_ID_NO_SKB ; 
 int /*<<< orphan*/  __skb_queue_tail (TYPE_1__*,struct sk_buff*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  memset (struct mt76_tx_cb*,int /*<<< orphan*/ ,int) ; 
 struct mt76_tx_cb* mt76_tx_skb_cb (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int
mt76_tx_status_skb_add(struct mt76_dev *dev, struct mt76_wcid *wcid,
		       struct sk_buff *skb)
{
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	struct mt76_tx_cb *cb = mt76_tx_skb_cb(skb);
	int pid;

	if (!wcid)
		return MT_PACKET_ID_NO_ACK;

	if (info->flags & IEEE80211_TX_CTL_NO_ACK)
		return MT_PACKET_ID_NO_ACK;

	if (!(info->flags & (IEEE80211_TX_CTL_REQ_TX_STATUS |
			     IEEE80211_TX_CTL_RATE_CTRL_PROBE)))
		return MT_PACKET_ID_NO_SKB;

	spin_lock_bh(&dev->status_list.lock);

	memset(cb, 0, sizeof(*cb));
	wcid->packet_id = (wcid->packet_id + 1) & MT_PACKET_ID_MASK;
	if (wcid->packet_id == MT_PACKET_ID_NO_ACK ||
	    wcid->packet_id == MT_PACKET_ID_NO_SKB)
		wcid->packet_id = MT_PACKET_ID_FIRST;

	pid = wcid->packet_id;
	cb->wcid = wcid->idx;
	cb->pktid = pid;
	cb->jiffies = jiffies;

	__skb_queue_tail(&dev->status_list, skb);
	spin_unlock_bh(&dev->status_list.lock);

	return pid;
}