#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct device {int dummy; } ;
struct usb_interface {struct device dev; struct usb_host_interface* cur_altsetting; } ;
struct TYPE_8__ {int bNumEndpoints; } ;
struct usb_host_interface {TYPE_2__* endpoint; TYPE_1__ desc; } ;
struct usb_endpoint_descriptor {int bEndpointAddress; int bmAttributes; int /*<<< orphan*/  wMaxPacketSize; } ;
struct usb_device_id {int dummy; } ;
struct usb_device {int dummy; } ;
struct TYPE_13__ {char* name; char* default_trigger; int /*<<< orphan*/  brightness_set; } ;
struct TYPE_11__ {int bRequestType; void* wLength; int /*<<< orphan*/  bRequest; } ;
struct TYPE_10__ {int bRequestType; void* wLength; int /*<<< orphan*/  bRequest; } ;
struct redrat3_dev {int carrier; struct usb_device* udev; TYPE_6__ led; int /*<<< orphan*/  rc; int /*<<< orphan*/  flash_in_buf; TYPE_4__ flash_control; void* flash_urb; int /*<<< orphan*/  learn_buf; TYPE_3__ learn_control; void* learn_urb; int /*<<< orphan*/  flash; TYPE_5__* wide_urb; int /*<<< orphan*/  dma_in; int /*<<< orphan*/  bulk_in_buf; TYPE_5__* narrow_urb; struct usb_endpoint_descriptor* ep_out; struct usb_endpoint_descriptor* ep_narrow; struct device* dev; } ;
struct TYPE_12__ {int /*<<< orphan*/  transfer_flags; int /*<<< orphan*/  transfer_dma; } ;
struct TYPE_9__ {struct usb_endpoint_descriptor desc; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RR3_BLINK_LED ; 
 int /*<<< orphan*/  RR3_MODSIG_CAPTURE ; 
 scalar_t__ RR3_NARROW_IN_EP_ADDR ; 
 scalar_t__ RR3_WIDE_IN_EP_ADDR ; 
 int /*<<< orphan*/  URB_NO_TRANSFER_DMA_MAP ; 
 int USB_DIR_IN ; 
 int USB_DIR_OUT ; 
 int USB_ENDPOINT_DIR_MASK ; 
 int USB_ENDPOINT_XFERTYPE_MASK ; 
 int USB_ENDPOINT_XFER_BULK ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 struct redrat3_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int led_classdev_register (struct device*,TYPE_6__*) ; 
 int /*<<< orphan*/  led_classdev_unregister (TYPE_6__*) ; 
 int /*<<< orphan*/  redrat3_brightness_set ; 
 int /*<<< orphan*/  redrat3_delete (struct redrat3_dev*,struct usb_device*) ; 
 int redrat3_enable_detector (struct redrat3_dev*) ; 
 int /*<<< orphan*/  redrat3_get_firmware_rev (struct redrat3_dev*) ; 
 int /*<<< orphan*/  redrat3_handle_async ; 
 int /*<<< orphan*/  redrat3_init_rc_dev (struct redrat3_dev*) ; 
 int /*<<< orphan*/  redrat3_learn_complete ; 
 int /*<<< orphan*/  redrat3_led_complete ; 
 int /*<<< orphan*/  redrat3_reset (struct redrat3_dev*) ; 
 int /*<<< orphan*/  usb_alloc_coherent (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (TYPE_5__*,struct usb_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct redrat3_dev*) ; 
 int /*<<< orphan*/  usb_fill_control_urb (void*,struct usb_device*,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct redrat3_dev*) ; 
 int usb_rcvbulkpipe (struct usb_device*,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct redrat3_dev*) ; 

__attribute__((used)) static int redrat3_dev_probe(struct usb_interface *intf,
			     const struct usb_device_id *id)
{
	struct usb_device *udev = interface_to_usbdev(intf);
	struct device *dev = &intf->dev;
	struct usb_host_interface *uhi;
	struct redrat3_dev *rr3;
	struct usb_endpoint_descriptor *ep;
	struct usb_endpoint_descriptor *ep_narrow = NULL;
	struct usb_endpoint_descriptor *ep_wide = NULL;
	struct usb_endpoint_descriptor *ep_out = NULL;
	u8 addr, attrs;
	int pipe, i;
	int retval = -ENOMEM;

	uhi = intf->cur_altsetting;

	/* find our bulk-in and bulk-out endpoints */
	for (i = 0; i < uhi->desc.bNumEndpoints; ++i) {
		ep = &uhi->endpoint[i].desc;
		addr = ep->bEndpointAddress;
		attrs = ep->bmAttributes;

		if (((addr & USB_ENDPOINT_DIR_MASK) == USB_DIR_IN) &&
		    ((attrs & USB_ENDPOINT_XFERTYPE_MASK) ==
		     USB_ENDPOINT_XFER_BULK)) {
			dev_dbg(dev, "found bulk-in endpoint at 0x%02x\n",
				ep->bEndpointAddress);
			/* data comes in on 0x82, 0x81 is for learning */
			if (ep->bEndpointAddress == RR3_NARROW_IN_EP_ADDR)
				ep_narrow = ep;
			if (ep->bEndpointAddress == RR3_WIDE_IN_EP_ADDR)
				ep_wide = ep;
		}

		if ((ep_out == NULL) &&
		    ((addr & USB_ENDPOINT_DIR_MASK) == USB_DIR_OUT) &&
		    ((attrs & USB_ENDPOINT_XFERTYPE_MASK) ==
		     USB_ENDPOINT_XFER_BULK)) {
			dev_dbg(dev, "found bulk-out endpoint at 0x%02x\n",
				ep->bEndpointAddress);
			ep_out = ep;
		}
	}

	if (!ep_narrow || !ep_out || !ep_wide) {
		dev_err(dev, "Couldn't find all endpoints\n");
		retval = -ENODEV;
		goto no_endpoints;
	}

	/* allocate memory for our device state and initialize it */
	rr3 = kzalloc(sizeof(*rr3), GFP_KERNEL);
	if (!rr3)
		goto no_endpoints;

	rr3->dev = &intf->dev;
	rr3->ep_narrow = ep_narrow;
	rr3->ep_out = ep_out;
	rr3->udev = udev;

	/* set up bulk-in endpoint */
	rr3->narrow_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!rr3->narrow_urb)
		goto redrat_free;

	rr3->wide_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!rr3->wide_urb)
		goto redrat_free;

	rr3->bulk_in_buf = usb_alloc_coherent(udev,
		le16_to_cpu(ep_narrow->wMaxPacketSize),
		GFP_KERNEL, &rr3->dma_in);
	if (!rr3->bulk_in_buf)
		goto redrat_free;

	pipe = usb_rcvbulkpipe(udev, ep_narrow->bEndpointAddress);
	usb_fill_bulk_urb(rr3->narrow_urb, udev, pipe, rr3->bulk_in_buf,
		le16_to_cpu(ep_narrow->wMaxPacketSize),
		redrat3_handle_async, rr3);
	rr3->narrow_urb->transfer_dma = rr3->dma_in;
	rr3->narrow_urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	pipe = usb_rcvbulkpipe(udev, ep_wide->bEndpointAddress);
	usb_fill_bulk_urb(rr3->wide_urb, udev, pipe, rr3->bulk_in_buf,
		le16_to_cpu(ep_narrow->wMaxPacketSize),
		redrat3_handle_async, rr3);
	rr3->wide_urb->transfer_dma = rr3->dma_in;
	rr3->wide_urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	redrat3_reset(rr3);
	redrat3_get_firmware_rev(rr3);

	/* default.. will get overridden by any sends with a freq defined */
	rr3->carrier = 38000;

	atomic_set(&rr3->flash, 0);
	rr3->flash_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!rr3->flash_urb)
		goto redrat_free;

	/* learn urb */
	rr3->learn_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!rr3->learn_urb)
		goto redrat_free;

	/* setup packet is 'c0 b2 0000 0000 0001' */
	rr3->learn_control.bRequestType = 0xc0;
	rr3->learn_control.bRequest = RR3_MODSIG_CAPTURE;
	rr3->learn_control.wLength = cpu_to_le16(1);

	usb_fill_control_urb(rr3->learn_urb, udev, usb_rcvctrlpipe(udev, 0),
			(unsigned char *)&rr3->learn_control,
			&rr3->learn_buf, sizeof(rr3->learn_buf),
			redrat3_learn_complete, rr3);

	/* setup packet is 'c0 b9 0000 0000 0001' */
	rr3->flash_control.bRequestType = 0xc0;
	rr3->flash_control.bRequest = RR3_BLINK_LED;
	rr3->flash_control.wLength = cpu_to_le16(1);

	usb_fill_control_urb(rr3->flash_urb, udev, usb_rcvctrlpipe(udev, 0),
			(unsigned char *)&rr3->flash_control,
			&rr3->flash_in_buf, sizeof(rr3->flash_in_buf),
			redrat3_led_complete, rr3);

	/* led control */
	rr3->led.name = "redrat3:red:feedback";
	rr3->led.default_trigger = "rc-feedback";
	rr3->led.brightness_set = redrat3_brightness_set;
	retval = led_classdev_register(&intf->dev, &rr3->led);
	if (retval)
		goto redrat_free;

	rr3->rc = redrat3_init_rc_dev(rr3);
	if (!rr3->rc) {
		retval = -ENOMEM;
		goto led_free;
	}

	/* might be all we need to do? */
	retval = redrat3_enable_detector(rr3);
	if (retval < 0)
		goto led_free;

	/* we can register the device now, as it is ready */
	usb_set_intfdata(intf, rr3);

	return 0;

led_free:
	led_classdev_unregister(&rr3->led);
redrat_free:
	redrat3_delete(rr3, rr3->udev);

no_endpoints:
	return retval;
}