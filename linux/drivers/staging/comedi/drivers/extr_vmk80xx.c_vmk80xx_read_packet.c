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
struct vmk80xx_private {scalar_t__ model; int /*<<< orphan*/  usb_rx_buf; struct usb_endpoint_descriptor* ep_rx; } ;
struct usb_endpoint_descriptor {int /*<<< orphan*/  bEndpointAddress; } ;
struct usb_device {int dummy; } ;
struct comedi_device {struct vmk80xx_private* private; } ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ VMK8061_MODEL ; 
 struct usb_device* comedi_to_usb_dev (struct comedi_device*) ; 
 int /*<<< orphan*/  usb_endpoint_maxp (struct usb_endpoint_descriptor*) ; 
 int usb_interrupt_msg (struct usb_device*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 unsigned int usb_rcvintpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmk80xx_do_bulk_msg (struct comedi_device*) ; 

__attribute__((used)) static int vmk80xx_read_packet(struct comedi_device *dev)
{
	struct vmk80xx_private *devpriv = dev->private;
	struct usb_device *usb = comedi_to_usb_dev(dev);
	struct usb_endpoint_descriptor *ep;
	unsigned int pipe;

	if (devpriv->model == VMK8061_MODEL) {
		vmk80xx_do_bulk_msg(dev);
		return 0;
	}

	ep = devpriv->ep_rx;
	pipe = usb_rcvintpipe(usb, ep->bEndpointAddress);
	return usb_interrupt_msg(usb, pipe, devpriv->usb_rx_buf,
				 usb_endpoint_maxp(ep), NULL,
				 HZ * 10);
}