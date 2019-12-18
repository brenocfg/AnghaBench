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
struct urb {scalar_t__ status; scalar_t__ context; } ;
struct rt2x00_dev {int /*<<< orphan*/  txdone_work; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  txstatus_fifo; TYPE_3__* ops; } ;
struct queue_entry {int /*<<< orphan*/  flags; TYPE_1__* queue; } ;
struct TYPE_6__ {TYPE_2__* lib; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* tx_dma_done ) (struct queue_entry*) ;} ;
struct TYPE_4__ {struct rt2x00_dev* rt2x00dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTRY_DATA_IO_FAILED ; 
 int /*<<< orphan*/  ENTRY_OWNER_DEVICE_DATA ; 
 int /*<<< orphan*/  REQUIRE_TXSTATUS_FIFO ; 
 int /*<<< orphan*/  kfifo_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2x00_has_cap_flag (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00lib_dmadone (struct queue_entry*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct queue_entry*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rt2x00usb_interrupt_txdone(struct urb *urb)
{
	struct queue_entry *entry = (struct queue_entry *)urb->context;
	struct rt2x00_dev *rt2x00dev = entry->queue->rt2x00dev;

	if (!test_bit(ENTRY_OWNER_DEVICE_DATA, &entry->flags))
		return;
	/*
	 * Check if the frame was correctly uploaded
	 */
	if (urb->status)
		set_bit(ENTRY_DATA_IO_FAILED, &entry->flags);
	/*
	 * Report the frame as DMA done
	 */
	rt2x00lib_dmadone(entry);

	if (rt2x00dev->ops->lib->tx_dma_done)
		rt2x00dev->ops->lib->tx_dma_done(entry);
	/*
	 * Schedule the delayed work for reading the TX status
	 * from the device.
	 */
	if (!rt2x00_has_cap_flag(rt2x00dev, REQUIRE_TXSTATUS_FIFO) ||
	    !kfifo_is_empty(&rt2x00dev->txstatus_fifo))
		queue_work(rt2x00dev->workqueue, &rt2x00dev->txdone_work);
}