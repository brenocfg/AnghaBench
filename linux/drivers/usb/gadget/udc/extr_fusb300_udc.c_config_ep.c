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
struct usb_endpoint_descriptor {int bmAttributes; int bEndpointAddress; scalar_t__ bInterval; } ;
struct fusb300_ep_info {int type; int dir_in; int epnum; scalar_t__ bw_num; scalar_t__ interval; int /*<<< orphan*/  maxpacket; scalar_t__ addrofs; } ;
struct TYPE_2__ {struct usb_endpoint_descriptor const* desc; } ;
struct fusb300_ep {TYPE_1__ ep; struct fusb300* fusb300; } ;
struct fusb300 {struct fusb300_ep** ep; } ;

/* Variables and functions */
 int USB_ENDPOINT_DIR_MASK ; 
 int USB_ENDPOINT_NUMBER_MASK ; 
 int USB_ENDPOINT_XFERTYPE_MASK ; 
 int USB_ENDPOINT_XFER_INT ; 
 int USB_ENDPOINT_XFER_ISOC ; 
 int /*<<< orphan*/  ep_fifo_setting (struct fusb300*,struct fusb300_ep_info) ; 
 int /*<<< orphan*/  fusb300_ep_setting (struct fusb300_ep*,struct fusb300_ep_info) ; 
 int /*<<< orphan*/  set_ep_reg (struct fusb300*,struct fusb300_ep_info) ; 
 int /*<<< orphan*/  usb_endpoint_maxp (struct usb_endpoint_descriptor const*) ; 
 scalar_t__ usb_endpoint_maxp_mult (struct usb_endpoint_descriptor const*) ; 

__attribute__((used)) static int config_ep(struct fusb300_ep *ep,
		     const struct usb_endpoint_descriptor *desc)
{
	struct fusb300 *fusb300 = ep->fusb300;
	struct fusb300_ep_info info;

	ep->ep.desc = desc;

	info.interval = 0;
	info.addrofs = 0;
	info.bw_num = 0;

	info.type = desc->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK;
	info.dir_in = (desc->bEndpointAddress & USB_ENDPOINT_DIR_MASK) ? 1 : 0;
	info.maxpacket = usb_endpoint_maxp(desc);
	info.epnum = desc->bEndpointAddress & USB_ENDPOINT_NUMBER_MASK;

	if ((info.type == USB_ENDPOINT_XFER_INT) ||
	   (info.type == USB_ENDPOINT_XFER_ISOC)) {
		info.interval = desc->bInterval;
		if (info.type == USB_ENDPOINT_XFER_ISOC)
			info.bw_num = usb_endpoint_maxp_mult(desc);
	}

	ep_fifo_setting(fusb300, info);

	set_ep_reg(fusb300, info);

	fusb300_ep_setting(ep, info);

	fusb300->ep[info.epnum] = ep;

	return 0;
}