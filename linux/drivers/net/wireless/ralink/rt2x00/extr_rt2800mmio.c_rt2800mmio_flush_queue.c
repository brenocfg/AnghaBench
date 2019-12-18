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
struct rt2x00_dev {int /*<<< orphan*/  txdone_work; int /*<<< orphan*/  workqueue; } ;
struct data_queue {int qid; struct rt2x00_dev* rt2x00dev; } ;

/* Variables and functions */
#define  QID_AC_BE 132 
#define  QID_AC_BK 131 
#define  QID_AC_VI 130 
#define  QID_AC_VO 129 
#define  QID_RX 128 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ rt2x00queue_empty (struct data_queue*) ; 

void rt2800mmio_flush_queue(struct data_queue *queue, bool drop)
{
	struct rt2x00_dev *rt2x00dev = queue->rt2x00dev;
	bool tx_queue = false;
	unsigned int i;

	switch (queue->qid) {
	case QID_AC_VO:
	case QID_AC_VI:
	case QID_AC_BE:
	case QID_AC_BK:
		tx_queue = true;
		break;
	case QID_RX:
		break;
	default:
		return;
	}

	for (i = 0; i < 5; i++) {
		/*
		 * Check if the driver is already done, otherwise we
		 * have to sleep a little while to give the driver/hw
		 * the oppurtunity to complete interrupt process itself.
		 */
		if (rt2x00queue_empty(queue))
			break;

		/*
		 * For TX queues schedule completion tasklet to catch
		 * tx status timeouts, othewise just wait.
		 */
		if (tx_queue)
			queue_work(rt2x00dev->workqueue, &rt2x00dev->txdone_work);

		/*
		 * Wait for a little while to give the driver
		 * the oppurtunity to recover itself.
		 */
		msleep(50);
	}
}