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
struct queue_entry_priv_mmio {int dummy; } ;
struct data_queue {int qid; int limit; int priv_size; int /*<<< orphan*/  desc_size; void* data_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 void* DATA_FRAME_SIZE ; 
#define  QID_AC_BE 134 
#define  QID_AC_BK 133 
#define  QID_AC_VI 132 
#define  QID_AC_VO 131 
#define  QID_ATIM 130 
#define  QID_BEACON 129 
#define  QID_RX 128 
 int /*<<< orphan*/  RXD_DESC_SIZE ; 
 int /*<<< orphan*/  TXD_DESC_SIZE ; 
 int /*<<< orphan*/  TXINFO_SIZE ; 

__attribute__((used)) static void rt61pci_queue_init(struct data_queue *queue)
{
	switch (queue->qid) {
	case QID_RX:
		queue->limit = 32;
		queue->data_size = DATA_FRAME_SIZE;
		queue->desc_size = RXD_DESC_SIZE;
		queue->priv_size = sizeof(struct queue_entry_priv_mmio);
		break;

	case QID_AC_VO:
	case QID_AC_VI:
	case QID_AC_BE:
	case QID_AC_BK:
		queue->limit = 32;
		queue->data_size = DATA_FRAME_SIZE;
		queue->desc_size = TXD_DESC_SIZE;
		queue->priv_size = sizeof(struct queue_entry_priv_mmio);
		break;

	case QID_BEACON:
		queue->limit = 4;
		queue->data_size = 0; /* No DMA required for beacons */
		queue->desc_size = TXINFO_SIZE;
		queue->priv_size = sizeof(struct queue_entry_priv_mmio);
		break;

	case QID_ATIM:
		/* fallthrough */
	default:
		BUG();
		break;
	}
}