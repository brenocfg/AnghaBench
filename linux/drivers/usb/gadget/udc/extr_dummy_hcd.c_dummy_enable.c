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
struct usb_ep {unsigned int maxpacket; int /*<<< orphan*/  name; int /*<<< orphan*/  comp_desc; } ;
struct usb_endpoint_descriptor {scalar_t__ bDescriptorType; int bEndpointAddress; } ;
struct dummy_hcd {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct dummy_ep {int stream_en; scalar_t__ wedged; scalar_t__ halted; struct usb_endpoint_descriptor const* desc; TYPE_1__ ep; } ;
struct TYPE_4__ {int /*<<< orphan*/  speed; } ;
struct dummy {TYPE_2__ gadget; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int EINVAL ; 
 int ESHUTDOWN ; 
 int USB_DIR_IN ; 
 scalar_t__ USB_DT_ENDPOINT ; 
#define  USB_ENDPOINT_XFER_BULK 133 
#define  USB_ENDPOINT_XFER_INT 132 
#define  USB_ENDPOINT_XFER_ISOC 131 
#define  USB_SPEED_FULL 130 
#define  USB_SPEED_HIGH 129 
#define  USB_SPEED_SUPER 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,unsigned int,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ep0name ; 
 struct dummy* ep_to_dummy (struct dummy_ep*) ; 
 struct dummy_hcd* gadget_to_dummy_hcd (TYPE_2__*) ; 
 int /*<<< orphan*/  is_enabled (struct dummy_hcd*) ; 
 int /*<<< orphan*/  strstr (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  udc_dev (struct dummy*) ; 
 unsigned int usb_endpoint_maxp (struct usb_endpoint_descriptor const*) ; 
 int usb_endpoint_type (struct usb_endpoint_descriptor const*) ; 
 int /*<<< orphan*/  usb_endpoint_xfer_bulk (struct usb_endpoint_descriptor const*) ; 
 struct dummy_ep* usb_ep_to_dummy_ep (struct usb_ep*) ; 
 int /*<<< orphan*/  usb_ep_type_string (int) ; 
 scalar_t__ usb_ss_max_streams (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dummy_enable(struct usb_ep *_ep,
		const struct usb_endpoint_descriptor *desc)
{
	struct dummy		*dum;
	struct dummy_hcd	*dum_hcd;
	struct dummy_ep		*ep;
	unsigned		max;
	int			retval;

	ep = usb_ep_to_dummy_ep(_ep);
	if (!_ep || !desc || ep->desc || _ep->name == ep0name
			|| desc->bDescriptorType != USB_DT_ENDPOINT)
		return -EINVAL;
	dum = ep_to_dummy(ep);
	if (!dum->driver)
		return -ESHUTDOWN;

	dum_hcd = gadget_to_dummy_hcd(&dum->gadget);
	if (!is_enabled(dum_hcd))
		return -ESHUTDOWN;

	/*
	 * For HS/FS devices only bits 0..10 of the wMaxPacketSize represent the
	 * maximum packet size.
	 * For SS devices the wMaxPacketSize is limited by 1024.
	 */
	max = usb_endpoint_maxp(desc);

	/* drivers must not request bad settings, since lower levels
	 * (hardware or its drivers) may not check.  some endpoints
	 * can't do iso, many have maxpacket limitations, etc.
	 *
	 * since this "hardware" driver is here to help debugging, we
	 * have some extra sanity checks.  (there could be more though,
	 * especially for "ep9out" style fixed function ones.)
	 */
	retval = -EINVAL;
	switch (usb_endpoint_type(desc)) {
	case USB_ENDPOINT_XFER_BULK:
		if (strstr(ep->ep.name, "-iso")
				|| strstr(ep->ep.name, "-int")) {
			goto done;
		}
		switch (dum->gadget.speed) {
		case USB_SPEED_SUPER:
			if (max == 1024)
				break;
			goto done;
		case USB_SPEED_HIGH:
			if (max == 512)
				break;
			goto done;
		case USB_SPEED_FULL:
			if (max == 8 || max == 16 || max == 32 || max == 64)
				/* we'll fake any legal size */
				break;
			/* save a return statement */
		default:
			goto done;
		}
		break;
	case USB_ENDPOINT_XFER_INT:
		if (strstr(ep->ep.name, "-iso")) /* bulk is ok */
			goto done;
		/* real hardware might not handle all packet sizes */
		switch (dum->gadget.speed) {
		case USB_SPEED_SUPER:
		case USB_SPEED_HIGH:
			if (max <= 1024)
				break;
			/* save a return statement */
			/* fall through */
		case USB_SPEED_FULL:
			if (max <= 64)
				break;
			/* save a return statement */
			/* fall through */
		default:
			if (max <= 8)
				break;
			goto done;
		}
		break;
	case USB_ENDPOINT_XFER_ISOC:
		if (strstr(ep->ep.name, "-bulk")
				|| strstr(ep->ep.name, "-int"))
			goto done;
		/* real hardware might not handle all packet sizes */
		switch (dum->gadget.speed) {
		case USB_SPEED_SUPER:
		case USB_SPEED_HIGH:
			if (max <= 1024)
				break;
			/* save a return statement */
			/* fall through */
		case USB_SPEED_FULL:
			if (max <= 1023)
				break;
			/* save a return statement */
		default:
			goto done;
		}
		break;
	default:
		/* few chips support control except on ep0 */
		goto done;
	}

	_ep->maxpacket = max;
	if (usb_ss_max_streams(_ep->comp_desc)) {
		if (!usb_endpoint_xfer_bulk(desc)) {
			dev_err(udc_dev(dum), "Can't enable stream support on "
					"non-bulk ep %s\n", _ep->name);
			return -EINVAL;
		}
		ep->stream_en = 1;
	}
	ep->desc = desc;

	dev_dbg(udc_dev(dum), "enabled %s (ep%d%s-%s) maxpacket %d stream %s\n",
		_ep->name,
		desc->bEndpointAddress & 0x0f,
		(desc->bEndpointAddress & USB_DIR_IN) ? "in" : "out",
		usb_ep_type_string(usb_endpoint_type(desc)),
		max, ep->stream_en ? "enabled" : "disabled");

	/* at this point real hardware should be NAKing transfers
	 * to that endpoint, until a buffer is queued to it.
	 */
	ep->halted = ep->wedged = 0;
	retval = 0;
done:
	return retval;
}