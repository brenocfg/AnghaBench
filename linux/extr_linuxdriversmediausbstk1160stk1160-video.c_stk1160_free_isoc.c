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
struct urb {int /*<<< orphan*/  transfer_dma; int /*<<< orphan*/  transfer_buffer_length; } ;
struct TYPE_2__ {int num_bufs; struct urb** transfer_buffer; struct urb** urb; } ;
struct stk1160 {TYPE_1__ isoc_ctl; int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct urb**) ; 
 int /*<<< orphan*/  stk1160_dbg (char*,...) ; 
 int /*<<< orphan*/  usb_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 

void stk1160_free_isoc(struct stk1160 *dev)
{
	struct urb *urb;
	int i, num_bufs = dev->isoc_ctl.num_bufs;

	stk1160_dbg("freeing %d urb buffers...\n", num_bufs);

	for (i = 0; i < num_bufs; i++) {

		urb = dev->isoc_ctl.urb[i];
		if (urb) {

			if (dev->isoc_ctl.transfer_buffer[i]) {
#ifndef CONFIG_DMA_NONCOHERENT
				usb_free_coherent(dev->udev,
					urb->transfer_buffer_length,
					dev->isoc_ctl.transfer_buffer[i],
					urb->transfer_dma);
#else
				kfree(dev->isoc_ctl.transfer_buffer[i]);
#endif
			}
			usb_free_urb(urb);
			dev->isoc_ctl.urb[i] = NULL;
		}
		dev->isoc_ctl.transfer_buffer[i] = NULL;
	}

	kfree(dev->isoc_ctl.urb);
	kfree(dev->isoc_ctl.transfer_buffer);

	dev->isoc_ctl.urb = NULL;
	dev->isoc_ctl.transfer_buffer = NULL;
	dev->isoc_ctl.num_bufs = 0;

	stk1160_dbg("all urb buffers freed\n");
}