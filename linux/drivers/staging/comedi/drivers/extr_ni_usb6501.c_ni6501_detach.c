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
struct usb_interface {int dummy; } ;
struct ni6501_private {int /*<<< orphan*/  usb_tx_buf; int /*<<< orphan*/  usb_rx_buf; int /*<<< orphan*/  mut; } ;
struct comedi_device {struct ni6501_private* private; } ;

/* Variables and functions */
 struct usb_interface* comedi_to_usb_interface (struct comedi_device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ni6501_detach(struct comedi_device *dev)
{
	struct usb_interface *intf = comedi_to_usb_interface(dev);
	struct ni6501_private *devpriv = dev->private;

	if (!devpriv)
		return;

	mutex_destroy(&devpriv->mut);

	usb_set_intfdata(intf, NULL);

	kfree(devpriv->usb_rx_buf);
	kfree(devpriv->usb_tx_buf);
}