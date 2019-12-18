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
struct work_struct {int dummy; } ;
struct data_queue {int qid; TYPE_1__* rt2x00dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  workqueue; struct work_struct rxdone_work; struct work_struct txdone_work; } ;

/* Variables and functions */
#define  QID_AC_BE 132 
#define  QID_AC_BK 131 
#define  QID_AC_VI 130 
#define  QID_AC_VO 129 
#define  QID_RX 128 
 int /*<<< orphan*/  Q_INDEX ; 
 int /*<<< orphan*/  Q_INDEX_DONE ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,struct work_struct*) ; 
 scalar_t__ rt2x00queue_empty (struct data_queue*) ; 
 int /*<<< orphan*/  rt2x00queue_for_each_entry (struct data_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00usb_flush_entry ; 

void rt2x00usb_flush_queue(struct data_queue *queue, bool drop)
{
	struct work_struct *completion;
	unsigned int i;

	if (drop)
		rt2x00queue_for_each_entry(queue, Q_INDEX_DONE, Q_INDEX, NULL,
					   rt2x00usb_flush_entry);

	/*
	 * Obtain the queue completion handler
	 */
	switch (queue->qid) {
	case QID_AC_VO:
	case QID_AC_VI:
	case QID_AC_BE:
	case QID_AC_BK:
		completion = &queue->rt2x00dev->txdone_work;
		break;
	case QID_RX:
		completion = &queue->rt2x00dev->rxdone_work;
		break;
	default:
		return;
	}

	for (i = 0; i < 10; i++) {
		/*
		 * Check if the driver is already done, otherwise we
		 * have to sleep a little while to give the driver/hw
		 * the oppurtunity to complete interrupt process itself.
		 */
		if (rt2x00queue_empty(queue))
			break;

		/*
		 * Schedule the completion handler manually, when this
		 * worker function runs, it should cleanup the queue.
		 */
		queue_work(queue->rt2x00dev->workqueue, completion);

		/*
		 * Wait for a little while to give the driver
		 * the oppurtunity to recover itself.
		 */
		msleep(50);
	}
}