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
typedef  int u8 ;
struct usb_gadget {int dummy; } ;
struct usb_ep {int maxpacket_limit; } ;
struct usb_endpoint_descriptor {int bmAttributes; int /*<<< orphan*/  wMaxPacketSize; } ;

/* Variables and functions */
 int USB_ENDPOINT_XFERTYPE_MASK ; 
 int USB_ENDPOINT_XFER_BULK ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 struct usb_ep* usb_ep_autoconfig_ss (struct usb_gadget*,struct usb_endpoint_descriptor*,int /*<<< orphan*/ *) ; 

struct usb_ep *usb_ep_autoconfig(
	struct usb_gadget		*gadget,
	struct usb_endpoint_descriptor	*desc
)
{
	struct usb_ep	*ep;
	u8		type;

	ep = usb_ep_autoconfig_ss(gadget, desc, NULL);
	if (!ep)
		return NULL;

	type = desc->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK;

	/* report (variable) full speed bulk maxpacket */
	if (type == USB_ENDPOINT_XFER_BULK) {
		int size = ep->maxpacket_limit;

		/* min() doesn't work on bitfields with gcc-3.5 */
		if (size > 64)
			size = 64;
		desc->wMaxPacketSize = cpu_to_le16(size);
	}

	return ep;
}