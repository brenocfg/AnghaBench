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
struct mt76_wcid {int dummy; } ;
struct mt76_dev {TYPE_2__* queue_ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;
struct ieee80211_tx_info {int flags; TYPE_1__ control; } ;
struct ieee80211_sta {scalar_t__ drv_priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* tx_queue_skb ) (struct mt76_dev*,int /*<<< orphan*/ ,struct sk_buff*,struct mt76_wcid*,struct ieee80211_sta*) ;} ;

/* Variables and functions */
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_CTL_REQ_TX_STATUS ; 
 int /*<<< orphan*/  IEEE80211_TX_CTRL_PS_RESPONSE ; 
 int IEEE80211_TX_STATUS_EOSP ; 
 int /*<<< orphan*/  MT_TXQ_PSD ; 
 int /*<<< orphan*/  mt76_skb_set_moredata (struct sk_buff*,int) ; 
 int /*<<< orphan*/  stub1 (struct mt76_dev*,int /*<<< orphan*/ ,struct sk_buff*,struct mt76_wcid*,struct ieee80211_sta*) ; 

__attribute__((used)) static void
mt76_queue_ps_skb(struct mt76_dev *dev, struct ieee80211_sta *sta,
		  struct sk_buff *skb, bool last)
{
	struct mt76_wcid *wcid = (struct mt76_wcid *)sta->drv_priv;
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);

	info->control.flags |= IEEE80211_TX_CTRL_PS_RESPONSE;
	if (last)
		info->flags |= IEEE80211_TX_STATUS_EOSP |
			       IEEE80211_TX_CTL_REQ_TX_STATUS;

	mt76_skb_set_moredata(skb, !last);
	dev->queue_ops->tx_queue_skb(dev, MT_TXQ_PSD, skb, wcid, sta);
}