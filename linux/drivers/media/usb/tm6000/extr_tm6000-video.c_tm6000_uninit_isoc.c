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
struct urb {int dummy; } ;
struct TYPE_2__ {int num_bufs; struct urb** transfer_buffer; struct urb** urb; int /*<<< orphan*/ * buf; } ;
struct tm6000_core {TYPE_1__ isoc_ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  keep_urb ; 
 int /*<<< orphan*/  kfree (struct urb**) ; 
 int /*<<< orphan*/  tm6000_free_urb_buffers (struct tm6000_core*) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_kill_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_unlink_urb (struct urb*) ; 

__attribute__((used)) static void tm6000_uninit_isoc(struct tm6000_core *dev)
{
	struct urb *urb;
	int i;

	dev->isoc_ctl.buf = NULL;
	for (i = 0; i < dev->isoc_ctl.num_bufs; i++) {
		urb = dev->isoc_ctl.urb[i];
		if (urb) {
			usb_kill_urb(urb);
			usb_unlink_urb(urb);
			usb_free_urb(urb);
			dev->isoc_ctl.urb[i] = NULL;
		}
		dev->isoc_ctl.transfer_buffer[i] = NULL;
	}

	if (!keep_urb)
		tm6000_free_urb_buffers(dev);

	kfree(dev->isoc_ctl.urb);
	kfree(dev->isoc_ctl.transfer_buffer);

	dev->isoc_ctl.urb = NULL;
	dev->isoc_ctl.transfer_buffer = NULL;
	dev->isoc_ctl.num_bufs = 0;
}