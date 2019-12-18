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
typedef  int /*<<< orphan*/  u32 ;
struct rt2x00_dev {int /*<<< orphan*/  txstatus_fifo; } ;
struct queue_entry {int /*<<< orphan*/  entry_idx; int /*<<< orphan*/  flags; } ;
struct data_queue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTRY_DATA_STATUS_PENDING ; 
 int /*<<< orphan*/  ENTRY_OWNER_DEVICE_DATA ; 
 int /*<<< orphan*/  Q_INDEX_DONE ; 
 int /*<<< orphan*/  TX_STA_FIFO_PID_QUEUE ; 
 scalar_t__ kfifo_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2800_drv_get_txwi (struct queue_entry*) ; 
 int /*<<< orphan*/  rt2800_txdone_entry (struct queue_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int rt2800_txdone_entry_check (struct queue_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_dbg (struct rt2x00_dev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_get_field32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_warn (struct rt2x00_dev*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rt2x00queue_empty (struct data_queue*) ; 
 struct queue_entry* rt2x00queue_get_entry (struct data_queue*,int /*<<< orphan*/ ) ; 
 struct data_queue* rt2x00queue_get_tx_queue (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

void rt2800_txdone(struct rt2x00_dev *rt2x00dev, unsigned int quota)
{
	struct data_queue *queue;
	struct queue_entry *entry;
	u32 reg;
	u8 qid;
	bool match;

	while (quota-- > 0 && kfifo_get(&rt2x00dev->txstatus_fifo, &reg)) {
		/*
		 * TX_STA_FIFO_PID_QUEUE is a 2-bit field, thus qid is
		 * guaranteed to be one of the TX QIDs .
		 */
		qid = rt2x00_get_field32(reg, TX_STA_FIFO_PID_QUEUE);
		queue = rt2x00queue_get_tx_queue(rt2x00dev, qid);

		if (unlikely(rt2x00queue_empty(queue))) {
			rt2x00_dbg(rt2x00dev, "Got TX status for an empty queue %u, dropping\n",
				   qid);
			break;
		}

		entry = rt2x00queue_get_entry(queue, Q_INDEX_DONE);

		if (unlikely(test_bit(ENTRY_OWNER_DEVICE_DATA, &entry->flags) ||
			     !test_bit(ENTRY_DATA_STATUS_PENDING, &entry->flags))) {
			rt2x00_warn(rt2x00dev, "Data pending for entry %u in queue %u\n",
				    entry->entry_idx, qid);
			break;
		}

		match = rt2800_txdone_entry_check(entry, reg);
		rt2800_txdone_entry(entry, reg, rt2800_drv_get_txwi(entry), match);
	}
}