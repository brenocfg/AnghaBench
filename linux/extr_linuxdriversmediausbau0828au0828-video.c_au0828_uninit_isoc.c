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
struct TYPE_2__ {int nfields; int num_bufs; struct urb** transfer_buffer; struct urb** urb; } ;
struct au0828_dev {int /*<<< orphan*/  stream_state; TYPE_1__ isoc_ctl; int /*<<< orphan*/  usbdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  STREAM_OFF ; 
 int /*<<< orphan*/  au0828_isocdbg (char*) ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int /*<<< orphan*/  kfree (struct urb**) ; 
 int /*<<< orphan*/  usb_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_kill_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_unlink_urb (struct urb*) ; 

__attribute__((used)) static void au0828_uninit_isoc(struct au0828_dev *dev)
{
	struct urb *urb;
	int i;

	au0828_isocdbg("au0828: called au0828_uninit_isoc\n");

	dev->isoc_ctl.nfields = -1;
	for (i = 0; i < dev->isoc_ctl.num_bufs; i++) {
		urb = dev->isoc_ctl.urb[i];
		if (urb) {
			if (!irqs_disabled())
				usb_kill_urb(urb);
			else
				usb_unlink_urb(urb);

			if (dev->isoc_ctl.transfer_buffer[i]) {
				usb_free_coherent(dev->usbdev,
					urb->transfer_buffer_length,
					dev->isoc_ctl.transfer_buffer[i],
					urb->transfer_dma);
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

	dev->stream_state = STREAM_OFF;
}