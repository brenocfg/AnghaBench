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
struct mt76_sw_queue {int swq_queued; } ;
struct mt76_dev {int /*<<< orphan*/  hw; struct mt76_sw_queue* q_tx; } ;
typedef  enum mt76_txq_id { ____Placeholder_mt76_txq_id } mt76_txq_id ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_txq_schedule_end (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ieee80211_txq_schedule_start (int /*<<< orphan*/ ,int) ; 
 int mt76_txq_schedule_list (struct mt76_dev*,int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

void mt76_txq_schedule(struct mt76_dev *dev, enum mt76_txq_id qid)
{
	struct mt76_sw_queue *sq = &dev->q_tx[qid];
	int len;

	if (qid >= 4)
		return;

	if (sq->swq_queued >= 4)
		return;

	rcu_read_lock();

	do {
		ieee80211_txq_schedule_start(dev->hw, qid);
		len = mt76_txq_schedule_list(dev, qid);
		ieee80211_txq_schedule_end(dev->hw, qid);
	} while (len > 0);

	rcu_read_unlock();
}