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
struct sk_buff_head {int dummy; } ;
struct sk_buff {int dummy; } ;
struct mt76_dev {int dummy; } ;
struct mt7615_sta {int /*<<< orphan*/  wcid; } ;
struct mt7615_dev {struct mt76_dev mt76; } ;
struct TYPE_4__ {TYPE_1__* rates; } ;
struct ieee80211_tx_info {TYPE_2__ status; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_3__ {int idx; } ;

/* Variables and functions */
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int MT_PACKET_ID_FIRST ; 
 int /*<<< orphan*/  ieee80211_tx_info_clear_status (struct ieee80211_tx_info*) ; 
 int /*<<< orphan*/  mt7615_fill_txs (struct mt7615_dev*,struct mt7615_sta*,struct ieee80211_tx_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt76_tx_status_lock (struct mt76_dev*,struct sk_buff_head*) ; 
 int /*<<< orphan*/  mt76_tx_status_skb_done (struct mt76_dev*,struct sk_buff*,struct sk_buff_head*) ; 
 struct sk_buff* mt76_tx_status_skb_get (struct mt76_dev*,int /*<<< orphan*/ *,int,struct sk_buff_head*) ; 
 int /*<<< orphan*/  mt76_tx_status_unlock (struct mt76_dev*,struct sk_buff_head*) ; 

__attribute__((used)) static bool mt7615_mac_add_txs_skb(struct mt7615_dev *dev,
				   struct mt7615_sta *sta, int pid,
				   __le32 *txs_data)
{
	struct mt76_dev *mdev = &dev->mt76;
	struct sk_buff_head list;
	struct sk_buff *skb;

	if (pid < MT_PACKET_ID_FIRST)
		return false;

	mt76_tx_status_lock(mdev, &list);
	skb = mt76_tx_status_skb_get(mdev, &sta->wcid, pid, &list);
	if (skb) {
		struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);

		if (!mt7615_fill_txs(dev, sta, info, txs_data)) {
			ieee80211_tx_info_clear_status(info);
			info->status.rates[0].idx = -1;
		}

		mt76_tx_status_skb_done(mdev, skb, &list);
	}
	mt76_tx_status_unlock(mdev, &list);

	return !!skb;
}