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
struct usbduxfast_private {scalar_t__ urb; scalar_t__ ai_cmd_running; } ;
struct comedi_device {struct usbduxfast_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_kill_urb (scalar_t__) ; 

__attribute__((used)) static int usbduxfast_ai_stop(struct comedi_device *dev, int do_unlink)
{
	struct usbduxfast_private *devpriv = dev->private;

	/* stop aquistion */
	devpriv->ai_cmd_running = 0;

	if (do_unlink && devpriv->urb) {
		/* kill the running transfer */
		usb_kill_urb(devpriv->urb);
	}

	return 0;
}