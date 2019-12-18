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
struct rt2x00_dev {int dummy; } ;
struct queue_entry {int entry_idx; } ;
struct data_queue {int qid; struct rt2x00_dev* rt2x00dev; } ;

/* Variables and functions */
#define  QID_AC_BE 133 
#define  QID_AC_BK 132 
#define  QID_AC_VI 131 
#define  QID_AC_VO 130 
#define  QID_MGMT 129 
#define  QID_RX 128 
 int /*<<< orphan*/  Q_INDEX_DMA_DONE ; 
 int /*<<< orphan*/  TX_DTX_IDX (int) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int rt2x00mmio_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 struct queue_entry* rt2x00queue_get_entry (struct data_queue*,int /*<<< orphan*/ ) ; 

unsigned int rt2800mmio_get_dma_done(struct data_queue *queue)
{
	struct rt2x00_dev *rt2x00dev = queue->rt2x00dev;
	struct queue_entry *entry;
	int idx, qid;

	switch (queue->qid) {
	case QID_AC_VO:
	case QID_AC_VI:
	case QID_AC_BE:
	case QID_AC_BK:
		qid = queue->qid;
		idx = rt2x00mmio_register_read(rt2x00dev, TX_DTX_IDX(qid));
		break;
	case QID_MGMT:
		idx = rt2x00mmio_register_read(rt2x00dev, TX_DTX_IDX(5));
		break;
	case QID_RX:
		entry = rt2x00queue_get_entry(queue, Q_INDEX_DMA_DONE);
		idx = entry->entry_idx;
		break;
	default:
		WARN_ON_ONCE(1);
		idx = 0;
		break;
	}

	return idx;
}