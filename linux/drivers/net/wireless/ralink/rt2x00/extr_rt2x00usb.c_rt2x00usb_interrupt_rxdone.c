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
struct urb {scalar_t__ actual_length; scalar_t__ status; scalar_t__ context; } ;
struct rt2x00_dev {int /*<<< orphan*/  rxdone_work; int /*<<< orphan*/  workqueue; } ;
struct queue_entry {int /*<<< orphan*/  flags; TYPE_1__* queue; } ;
struct TYPE_2__ {scalar_t__ desc_size; struct rt2x00_dev* rt2x00dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTRY_DATA_IO_FAILED ; 
 int /*<<< orphan*/  ENTRY_OWNER_DEVICE_DATA ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2x00lib_dmadone (struct queue_entry*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rt2x00usb_interrupt_rxdone(struct urb *urb)
{
	struct queue_entry *entry = (struct queue_entry *)urb->context;
	struct rt2x00_dev *rt2x00dev = entry->queue->rt2x00dev;

	if (!test_bit(ENTRY_OWNER_DEVICE_DATA, &entry->flags))
		return;

	/*
	 * Check if the received data is simply too small
	 * to be actually valid, or if the urb is signaling
	 * a problem.
	 */
	if (urb->actual_length < entry->queue->desc_size || urb->status)
		set_bit(ENTRY_DATA_IO_FAILED, &entry->flags);

	/*
	 * Report the frame as DMA done
	 */
	rt2x00lib_dmadone(entry);

	/*
	 * Schedule the delayed work for processing RX data
	 */
	queue_work(rt2x00dev->workqueue, &rt2x00dev->rxdone_work);
}