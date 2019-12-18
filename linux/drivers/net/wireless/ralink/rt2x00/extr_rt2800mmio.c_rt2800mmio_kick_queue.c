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
struct rt2x00_dev {int /*<<< orphan*/  txstatus_timer; } ;
struct queue_entry {int /*<<< orphan*/  entry_idx; } ;
struct data_queue {int qid; struct rt2x00_dev* rt2x00dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
#define  QID_AC_BE 132 
#define  QID_AC_BK 131 
#define  QID_AC_VI 130 
#define  QID_AC_VO 129 
#define  QID_MGMT 128 
 int /*<<< orphan*/  Q_INDEX ; 
 int /*<<< orphan*/  TXSTATUS_TIMEOUT ; 
 int /*<<< orphan*/  TX_CTX_IDX (int) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00mmio_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00queue_empty (struct data_queue*) ; 
 struct queue_entry* rt2x00queue_get_entry (struct data_queue*,int /*<<< orphan*/ ) ; 

void rt2800mmio_kick_queue(struct data_queue *queue)
{
	struct rt2x00_dev *rt2x00dev = queue->rt2x00dev;
	struct queue_entry *entry;

	switch (queue->qid) {
	case QID_AC_VO:
	case QID_AC_VI:
	case QID_AC_BE:
	case QID_AC_BK:
		WARN_ON_ONCE(rt2x00queue_empty(queue));
		entry = rt2x00queue_get_entry(queue, Q_INDEX);
		rt2x00mmio_register_write(rt2x00dev, TX_CTX_IDX(queue->qid),
					  entry->entry_idx);
		hrtimer_start(&rt2x00dev->txstatus_timer,
			      TXSTATUS_TIMEOUT, HRTIMER_MODE_REL);
		break;
	case QID_MGMT:
		entry = rt2x00queue_get_entry(queue, Q_INDEX);
		rt2x00mmio_register_write(rt2x00dev, TX_CTX_IDX(5),
					  entry->entry_idx);
		break;
	default:
		break;
	}
}