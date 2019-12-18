#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct uvc_device {int quirks; struct usb_host_endpoint* int_ep; TYPE_1__* intf; } ;
struct TYPE_4__ {int bNumEndpoints; } ;
struct usb_host_interface {unsigned char* extra; int extralen; struct usb_host_endpoint* endpoint; TYPE_2__ desc; } ;
struct usb_endpoint_descriptor {scalar_t__ bInterval; int /*<<< orphan*/  bEndpointAddress; int /*<<< orphan*/  wMaxPacketSize; } ;
struct usb_host_endpoint {struct usb_endpoint_descriptor desc; } ;
struct TYPE_3__ {struct usb_host_interface* cur_altsetting; } ;

/* Variables and functions */
 unsigned char USB_DT_CS_INTERFACE ; 
 int UVC_QUIRK_BUILTIN_ISIGHT ; 
 int /*<<< orphan*/  UVC_TRACE_DESCR ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ usb_endpoint_is_int_in (struct usb_endpoint_descriptor*) ; 
 int uvc_parse_standard_control (struct uvc_device*,unsigned char*,int) ; 
 scalar_t__ uvc_parse_vendor_control (struct uvc_device*,unsigned char*,int) ; 
 int /*<<< orphan*/  uvc_trace (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uvc_parse_control(struct uvc_device *dev)
{
	struct usb_host_interface *alts = dev->intf->cur_altsetting;
	unsigned char *buffer = alts->extra;
	int buflen = alts->extralen;
	int ret;

	/* Parse the default alternate setting only, as the UVC specification
	 * defines a single alternate setting, the default alternate setting
	 * zero.
	 */

	while (buflen > 2) {
		if (uvc_parse_vendor_control(dev, buffer, buflen) ||
		    buffer[1] != USB_DT_CS_INTERFACE)
			goto next_descriptor;

		if ((ret = uvc_parse_standard_control(dev, buffer, buflen)) < 0)
			return ret;

next_descriptor:
		buflen -= buffer[0];
		buffer += buffer[0];
	}

	/* Check if the optional status endpoint is present. Built-in iSight
	 * webcams have an interrupt endpoint but spit proprietary data that
	 * don't conform to the UVC status endpoint messages. Don't try to
	 * handle the interrupt endpoint for those cameras.
	 */
	if (alts->desc.bNumEndpoints == 1 &&
	    !(dev->quirks & UVC_QUIRK_BUILTIN_ISIGHT)) {
		struct usb_host_endpoint *ep = &alts->endpoint[0];
		struct usb_endpoint_descriptor *desc = &ep->desc;

		if (usb_endpoint_is_int_in(desc) &&
		    le16_to_cpu(desc->wMaxPacketSize) >= 8 &&
		    desc->bInterval != 0) {
			uvc_trace(UVC_TRACE_DESCR, "Found a Status endpoint "
				"(addr %02x).\n", desc->bEndpointAddress);
			dev->int_ep = ep;
		}
	}

	return 0;
}