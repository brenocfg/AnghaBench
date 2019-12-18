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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct mt76_wcid {int /*<<< orphan*/  flags; } ;
struct mt76_txq {int send_bar; int /*<<< orphan*/  retry_q; int /*<<< orphan*/  agg_ssn; scalar_t__ aggr; struct mt76_wcid* wcid; } ;
struct mt76_sw_queue {int swq_queued; struct mt76_queue* q; } ;
struct mt76_queue {int /*<<< orphan*/  lock; } ;
struct mt76_dev {int /*<<< orphan*/  hw; int /*<<< orphan*/  state; struct mt76_sw_queue* q_tx; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_txq {int /*<<< orphan*/  tid; struct ieee80211_vif* vif; struct ieee80211_sta* sta; scalar_t__ drv_priv; } ;
struct ieee80211_sta {int /*<<< orphan*/  addr; } ;
typedef  enum mt76_txq_id { ____Placeholder_mt76_txq_id } mt76_txq_id ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  MT76_RESET ; 
 int /*<<< orphan*/  MT_WCID_FLAG_PS ; 
 struct ieee80211_txq* ieee80211_next_txq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ieee80211_return_txq (int /*<<< orphan*/ ,struct ieee80211_txq*,int) ; 
 int /*<<< orphan*/  ieee80211_send_bar (struct ieee80211_vif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mt76_txq_send_burst (struct mt76_dev*,struct mt76_sw_queue*,struct mt76_txq*,int*) ; 
 struct ieee80211_txq* mtxq_to_txq (struct mt76_txq*) ; 
 scalar_t__ skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mt76_txq_schedule_list(struct mt76_dev *dev, enum mt76_txq_id qid)
{
	struct mt76_sw_queue *sq = &dev->q_tx[qid];
	struct mt76_queue *hwq = sq->q;
	struct ieee80211_txq *txq;
	struct mt76_txq *mtxq;
	struct mt76_wcid *wcid;
	int ret = 0;

	spin_lock_bh(&hwq->lock);
	while (1) {
		bool empty = false;

		if (sq->swq_queued >= 4)
			break;

		if (test_bit(MT76_RESET, &dev->state)) {
			ret = -EBUSY;
			break;
		}

		txq = ieee80211_next_txq(dev->hw, qid);
		if (!txq)
			break;

		mtxq = (struct mt76_txq *)txq->drv_priv;
		wcid = mtxq->wcid;
		if (wcid && test_bit(MT_WCID_FLAG_PS, &wcid->flags))
			continue;

		if (mtxq->send_bar && mtxq->aggr) {
			struct ieee80211_txq *txq = mtxq_to_txq(mtxq);
			struct ieee80211_sta *sta = txq->sta;
			struct ieee80211_vif *vif = txq->vif;
			u16 agg_ssn = mtxq->agg_ssn;
			u8 tid = txq->tid;

			mtxq->send_bar = false;
			spin_unlock_bh(&hwq->lock);
			ieee80211_send_bar(vif, sta->addr, tid, agg_ssn);
			spin_lock_bh(&hwq->lock);
		}

		ret += mt76_txq_send_burst(dev, sq, mtxq, &empty);
		if (skb_queue_empty(&mtxq->retry_q))
			empty = true;
		ieee80211_return_txq(dev->hw, txq, !empty);
	}
	spin_unlock_bh(&hwq->lock);

	return ret;
}