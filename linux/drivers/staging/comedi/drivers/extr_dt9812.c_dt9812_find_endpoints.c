#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {struct usb_host_interface* cur_altsetting; } ;
struct TYPE_5__ {int bNumEndpoints; } ;
struct usb_host_interface {TYPE_2__* endpoint; TYPE_1__ desc; } ;
struct usb_endpoint_descriptor {int bEndpointAddress; } ;
struct TYPE_8__ {int addr; void* size; } ;
struct TYPE_7__ {int addr; void* size; } ;
struct dt9812_private {TYPE_4__ cmd_rd; TYPE_3__ cmd_wr; } ;
struct comedi_device {int /*<<< orphan*/  class_dev; struct dt9812_private* private; } ;
struct TYPE_6__ {struct usb_endpoint_descriptor desc; } ;

/* Variables and functions */
 int ENODEV ; 
 int USB_DIR_IN ; 
 int USB_DIR_OUT ; 
 struct usb_interface* comedi_to_usb_interface (struct comedi_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 void* usb_endpoint_maxp (struct usb_endpoint_descriptor*) ; 

__attribute__((used)) static int dt9812_find_endpoints(struct comedi_device *dev)
{
	struct usb_interface *intf = comedi_to_usb_interface(dev);
	struct usb_host_interface *host = intf->cur_altsetting;
	struct dt9812_private *devpriv = dev->private;
	struct usb_endpoint_descriptor *ep;
	int i;

	if (host->desc.bNumEndpoints != 5) {
		dev_err(dev->class_dev, "Wrong number of endpoints\n");
		return -ENODEV;
	}

	for (i = 0; i < host->desc.bNumEndpoints; ++i) {
		int dir = -1;

		ep = &host->endpoint[i].desc;
		switch (i) {
		case 0:
			/* unused message pipe */
			dir = USB_DIR_IN;
			break;
		case 1:
			dir = USB_DIR_OUT;
			devpriv->cmd_wr.addr = ep->bEndpointAddress;
			devpriv->cmd_wr.size = usb_endpoint_maxp(ep);
			break;
		case 2:
			dir = USB_DIR_IN;
			devpriv->cmd_rd.addr = ep->bEndpointAddress;
			devpriv->cmd_rd.size = usb_endpoint_maxp(ep);
			break;
		case 3:
			/* unused write stream */
			dir = USB_DIR_OUT;
			break;
		case 4:
			/* unused read stream */
			dir = USB_DIR_IN;
			break;
		}
		if ((ep->bEndpointAddress & USB_DIR_IN) != dir) {
			dev_err(dev->class_dev,
				"Endpoint has wrong direction\n");
			return -ENODEV;
		}
	}
	return 0;
}