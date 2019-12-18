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
struct usbduxfast_private {int /*<<< orphan*/  mut; int /*<<< orphan*/  duxbuf; scalar_t__ urb; int /*<<< orphan*/  inbuf; } ;
struct usb_interface {int dummy; } ;
struct comedi_device {struct usbduxfast_private* private; } ;

/* Variables and functions */
 struct usb_interface* comedi_to_usb_interface (struct comedi_device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_free_urb (scalar_t__) ; 
 int /*<<< orphan*/  usb_kill_urb (scalar_t__) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void usbduxfast_detach(struct comedi_device *dev)
{
	struct usb_interface *intf = comedi_to_usb_interface(dev);
	struct usbduxfast_private *devpriv = dev->private;

	if (!devpriv)
		return;

	mutex_lock(&devpriv->mut);

	usb_set_intfdata(intf, NULL);

	if (devpriv->urb) {
		/* waits until a running transfer is over */
		usb_kill_urb(devpriv->urb);

		kfree(devpriv->inbuf);
		usb_free_urb(devpriv->urb);
	}

	kfree(devpriv->duxbuf);

	mutex_unlock(&devpriv->mut);

	mutex_destroy(&devpriv->mut);
}