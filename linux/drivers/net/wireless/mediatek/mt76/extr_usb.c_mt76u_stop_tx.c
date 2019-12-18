#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mt76_queue_entry {int /*<<< orphan*/  urb; } ;
struct mt76_queue {int ndesc; size_t head; int /*<<< orphan*/  lock; scalar_t__ queued; struct mt76_queue_entry* entry; } ;
struct TYPE_6__ {int /*<<< orphan*/  stat_work; } ;
struct mt76_dev {int /*<<< orphan*/  state; TYPE_3__ usb; TYPE_2__* drv; TYPE_1__* q_tx; int /*<<< orphan*/  tx_tasklet; int /*<<< orphan*/  dev; int /*<<< orphan*/  tx_wait; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* tx_complete_skb ) (struct mt76_dev*,int,struct mt76_queue_entry*) ;} ;
struct TYPE_4__ {struct mt76_queue* q; } ;

/* Variables and functions */
 int HZ ; 
 int IEEE80211_NUM_ACS ; 
 int /*<<< orphan*/  MT76_READING_STATS ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mt76_has_tx_pending (struct mt76_dev*) ; 
 int /*<<< orphan*/  mt76_tx_status_check (struct mt76_dev*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct mt76_dev*,int,struct mt76_queue_entry*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int) ; 

void mt76u_stop_tx(struct mt76_dev *dev)
{
	struct mt76_queue_entry entry;
	struct mt76_queue *q;
	int i, j, ret;

	ret = wait_event_timeout(dev->tx_wait, !mt76_has_tx_pending(dev),
				 HZ / 5);
	if (!ret) {
		dev_err(dev->dev, "timed out waiting for pending tx\n");

		for (i = 0; i < IEEE80211_NUM_ACS; i++) {
			q = dev->q_tx[i].q;
			for (j = 0; j < q->ndesc; j++)
				usb_kill_urb(q->entry[j].urb);
		}

		tasklet_kill(&dev->tx_tasklet);

		/* On device removal we maight queue skb's, but mt76u_tx_kick()
		 * will fail to submit urb, cleanup those skb's manually.
		 */
		for (i = 0; i < IEEE80211_NUM_ACS; i++) {
			q = dev->q_tx[i].q;

			/* Assure we are in sync with killed tasklet. */
			spin_lock_bh(&q->lock);
			while (q->queued) {
				entry = q->entry[q->head];
				q->head = (q->head + 1) % q->ndesc;
				q->queued--;

				dev->drv->tx_complete_skb(dev, i, &entry);
			}
			spin_unlock_bh(&q->lock);
		}
	}

	cancel_delayed_work_sync(&dev->usb.stat_work);
	clear_bit(MT76_READING_STATS, &dev->state);

	mt76_tx_status_check(dev, NULL, true);
}