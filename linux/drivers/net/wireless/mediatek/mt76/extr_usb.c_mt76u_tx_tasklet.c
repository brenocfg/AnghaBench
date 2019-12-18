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
typedef  scalar_t__ u32 ;
struct mt76_sw_queue {int /*<<< orphan*/  swq_queued; struct mt76_queue* q; } ;
struct mt76_queue_entry {int done; int schedule; } ;
struct mt76_queue {scalar_t__ queued; size_t head; int ndesc; int stopped; int /*<<< orphan*/  lock; struct mt76_queue_entry* entry; } ;
struct TYPE_4__ {int /*<<< orphan*/  stat_work; } ;
struct mt76_dev {int /*<<< orphan*/  hw; TYPE_2__ usb; int /*<<< orphan*/  state; int /*<<< orphan*/  tx_wait; TYPE_1__* drv; struct mt76_sw_queue* q_tx; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* tx_complete_skb ) (struct mt76_dev*,int,struct mt76_queue_entry*) ;} ;

/* Variables and functions */
 int IEEE80211_NUM_ACS ; 
 int /*<<< orphan*/  MT76_READING_STATS ; 
 int /*<<< orphan*/  ieee80211_queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_wake_queue (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mt76_txq_schedule (struct mt76_dev*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct mt76_dev*,int,struct mt76_queue_entry*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mt76u_tx_tasklet(unsigned long data)
{
	struct mt76_dev *dev = (struct mt76_dev *)data;
	struct mt76_queue_entry entry;
	struct mt76_sw_queue *sq;
	struct mt76_queue *q;
	bool wake;
	int i;

	for (i = 0; i < IEEE80211_NUM_ACS; i++) {
		u32 n_dequeued = 0, n_sw_dequeued = 0;

		sq = &dev->q_tx[i];
		q = sq->q;

		while (q->queued > n_dequeued) {
			if (!q->entry[q->head].done)
				break;

			if (q->entry[q->head].schedule) {
				q->entry[q->head].schedule = false;
				n_sw_dequeued++;
			}

			entry = q->entry[q->head];
			q->entry[q->head].done = false;
			q->head = (q->head + 1) % q->ndesc;
			n_dequeued++;

			dev->drv->tx_complete_skb(dev, i, &entry);
		}

		spin_lock_bh(&q->lock);

		sq->swq_queued -= n_sw_dequeued;
		q->queued -= n_dequeued;

		wake = q->stopped && q->queued < q->ndesc - 8;
		if (wake)
			q->stopped = false;

		if (!q->queued)
			wake_up(&dev->tx_wait);

		spin_unlock_bh(&q->lock);

		mt76_txq_schedule(dev, i);

		if (!test_and_set_bit(MT76_READING_STATS, &dev->state))
			ieee80211_queue_delayed_work(dev->hw,
						     &dev->usb.stat_work,
						     msecs_to_jiffies(10));

		if (wake)
			ieee80211_wake_queue(dev->hw, i);
	}
}