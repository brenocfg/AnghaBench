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
typedef  int u16 ;
struct sk_buff {int dummy; } ;
struct mt76_txq {scalar_t__ aggr; } ;
struct mt76_queue {int /*<<< orphan*/  lock; } ;
struct mt76_dev {TYPE_2__* queue_ops; TYPE_1__* q_tx; } ;
struct ieee80211_txq {scalar_t__ drv_priv; } ;
struct ieee80211_sta {struct ieee80211_txq** txq; } ;
struct ieee80211_hw {struct mt76_dev* priv; } ;
typedef  enum ieee80211_frame_release_type { ____Placeholder_ieee80211_frame_release_type } ieee80211_frame_release_type ;
struct TYPE_4__ {int /*<<< orphan*/  (* kick ) (struct mt76_dev*,struct mt76_queue*) ;} ;
struct TYPE_3__ {struct mt76_queue* q; } ;

/* Variables and functions */
 size_t MT_TXQ_PSD ; 
 int /*<<< orphan*/  ieee80211_sta_eosp (struct ieee80211_sta*) ; 
 int /*<<< orphan*/  mt76_check_agg_ssn (struct mt76_txq*,struct sk_buff*) ; 
 int /*<<< orphan*/  mt76_queue_ps_skb (struct mt76_dev*,struct ieee80211_sta*,struct sk_buff*,int) ; 
 struct sk_buff* mt76_txq_dequeue (struct mt76_dev*,struct mt76_txq*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct mt76_dev*,struct mt76_queue*) ; 

void
mt76_release_buffered_frames(struct ieee80211_hw *hw, struct ieee80211_sta *sta,
			     u16 tids, int nframes,
			     enum ieee80211_frame_release_type reason,
			     bool more_data)
{
	struct mt76_dev *dev = hw->priv;
	struct sk_buff *last_skb = NULL;
	struct mt76_queue *hwq = dev->q_tx[MT_TXQ_PSD].q;
	int i;

	spin_lock_bh(&hwq->lock);
	for (i = 0; tids && nframes; i++, tids >>= 1) {
		struct ieee80211_txq *txq = sta->txq[i];
		struct mt76_txq *mtxq = (struct mt76_txq *)txq->drv_priv;
		struct sk_buff *skb;

		if (!(tids & 1))
			continue;

		do {
			skb = mt76_txq_dequeue(dev, mtxq, true);
			if (!skb)
				break;

			if (mtxq->aggr)
				mt76_check_agg_ssn(mtxq, skb);

			nframes--;
			if (last_skb)
				mt76_queue_ps_skb(dev, sta, last_skb, false);

			last_skb = skb;
		} while (nframes);
	}

	if (last_skb) {
		mt76_queue_ps_skb(dev, sta, last_skb, true);
		dev->queue_ops->kick(dev, hwq);
	} else {
		ieee80211_sta_eosp(sta);
	}

	spin_unlock_bh(&hwq->lock);
}