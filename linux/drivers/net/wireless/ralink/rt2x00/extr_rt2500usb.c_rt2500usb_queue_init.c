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
struct queue_entry_priv_usb_bcn {int dummy; } ;
struct queue_entry_priv_usb {int dummy; } ;
struct data_queue {int qid; int limit; int priv_size; void* desc_size; void* data_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 void* DATA_FRAME_SIZE ; 
 void* MGMT_FRAME_SIZE ; 
#define  QID_AC_BE 134 
#define  QID_AC_BK 133 
#define  QID_AC_VI 132 
#define  QID_AC_VO 131 
#define  QID_ATIM 130 
#define  QID_BEACON 129 
#define  QID_RX 128 
 void* RXD_DESC_SIZE ; 
 void* TXD_DESC_SIZE ; 

__attribute__((used)) static void rt2500usb_queue_init(struct data_queue *queue)
{
	switch (queue->qid) {
	case QID_RX:
		queue->limit = 32;
		queue->data_size = DATA_FRAME_SIZE;
		queue->desc_size = RXD_DESC_SIZE;
		queue->priv_size = sizeof(struct queue_entry_priv_usb);
		break;

	case QID_AC_VO:
	case QID_AC_VI:
	case QID_AC_BE:
	case QID_AC_BK:
		queue->limit = 32;
		queue->data_size = DATA_FRAME_SIZE;
		queue->desc_size = TXD_DESC_SIZE;
		queue->priv_size = sizeof(struct queue_entry_priv_usb);
		break;

	case QID_BEACON:
		queue->limit = 1;
		queue->data_size = MGMT_FRAME_SIZE;
		queue->desc_size = TXD_DESC_SIZE;
		queue->priv_size = sizeof(struct queue_entry_priv_usb_bcn);
		break;

	case QID_ATIM:
		queue->limit = 8;
		queue->data_size = DATA_FRAME_SIZE;
		queue->desc_size = TXD_DESC_SIZE;
		queue->priv_size = sizeof(struct queue_entry_priv_usb);
		break;

	default:
		BUG();
		break;
	}
}