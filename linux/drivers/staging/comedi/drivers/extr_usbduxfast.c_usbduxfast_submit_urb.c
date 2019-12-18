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
struct usbduxfast_private {int /*<<< orphan*/  urb; int /*<<< orphan*/  inbuf; } ;
struct usb_device {int dummy; } ;
struct comedi_device {int /*<<< orphan*/  class_dev; struct usbduxfast_private* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  BULKINEP ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  SIZEINBUF ; 
 struct usb_device* comedi_to_usb_dev (struct comedi_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (int /*<<< orphan*/ ,struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct comedi_device*) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbduxfast_ai_interrupt ; 

__attribute__((used)) static int usbduxfast_submit_urb(struct comedi_device *dev)
{
	struct usb_device *usb = comedi_to_usb_dev(dev);
	struct usbduxfast_private *devpriv = dev->private;
	int ret;

	usb_fill_bulk_urb(devpriv->urb, usb, usb_rcvbulkpipe(usb, BULKINEP),
			  devpriv->inbuf, SIZEINBUF,
			  usbduxfast_ai_interrupt, dev);

	ret = usb_submit_urb(devpriv->urb, GFP_ATOMIC);
	if (ret) {
		dev_err(dev->class_dev, "usb_submit_urb error %d\n", ret);
		return ret;
	}
	return 0;
}