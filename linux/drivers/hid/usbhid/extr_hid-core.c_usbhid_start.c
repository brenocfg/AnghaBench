#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct usbhid_device {unsigned int bufsize; TYPE_4__* urbctrl; TYPE_4__* urbout; TYPE_4__* urbin; TYPE_7__* intf; int /*<<< orphan*/  iofl; int /*<<< orphan*/  ctrlbuf_dma; int /*<<< orphan*/  ctrlbuf; scalar_t__ cr; int /*<<< orphan*/  outbuf_dma; int /*<<< orphan*/  outbuf; int /*<<< orphan*/  inbuf_dma; int /*<<< orphan*/  inbuf; } ;
struct usb_interface {struct usb_host_interface* cur_altsetting; } ;
struct TYPE_12__ {unsigned int bNumEndpoints; scalar_t__ bInterfaceSubClass; scalar_t__ bInterfaceProtocol; } ;
struct usb_host_interface {TYPE_3__ desc; TYPE_1__* endpoint; } ;
struct usb_endpoint_descriptor {int bInterval; int /*<<< orphan*/  bEndpointAddress; } ;
struct usb_device {scalar_t__ speed; int /*<<< orphan*/  dev; } ;
struct TYPE_15__ {int /*<<< orphan*/  parent; } ;
struct hid_device {int quirks; TYPE_9__ dev; TYPE_2__* collection; int /*<<< orphan*/  name; struct usbhid_device* driver_data; } ;
struct TYPE_14__ {int needs_remote_wakeup; } ;
struct TYPE_13__ {int /*<<< orphan*/  transfer_flags; int /*<<< orphan*/  transfer_dma; } ;
struct TYPE_11__ {int usage; } ;
struct TYPE_10__ {struct usb_endpoint_descriptor desc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HID_DISCONNECTED ; 
 int /*<<< orphan*/  HID_FEATURE_REPORT ; 
#define  HID_GD_JOYSTICK 130 
#define  HID_GD_KEYBOARD 129 
#define  HID_GD_MOUSE 128 
 int /*<<< orphan*/  HID_INPUT_REPORT ; 
 int /*<<< orphan*/  HID_IN_POLLING ; 
 unsigned int HID_MAX_BUFFER_SIZE ; 
 unsigned int HID_MIN_BUFFER_SIZE ; 
 int /*<<< orphan*/  HID_OUTPUT_REPORT ; 
 int HID_QUIRK_ALWAYS_POLL ; 
 int HID_QUIRK_FULLSPEED_INTERVAL ; 
 int /*<<< orphan*/  HID_STARTED ; 
 int /*<<< orphan*/  URB_NO_TRANSFER_DMA_MAP ; 
 scalar_t__ USB_INTERFACE_PROTOCOL_KEYBOARD ; 
 scalar_t__ USB_INTERFACE_SUBCLASS_BOOT ; 
 scalar_t__ USB_SPEED_HIGH ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (TYPE_9__*,char*,int) ; 
 int /*<<< orphan*/  device_set_wakeup_enable (int /*<<< orphan*/ *,int) ; 
 int fls (int) ; 
 scalar_t__ hid_alloc_buffers (struct usb_device*,struct hid_device*) ; 
 int /*<<< orphan*/  hid_ctrl ; 
 int /*<<< orphan*/  hid_find_max_report (struct hid_device*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  hid_free_buffers (struct usb_device*,struct hid_device*) ; 
 int /*<<< orphan*/  hid_irq_in ; 
 int /*<<< orphan*/  hid_irq_out ; 
 int hid_jspoll_interval ; 
 int hid_kbpoll_interval ; 
 int hid_mousepoll_interval ; 
 int hid_start_in (struct hid_device*) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct usb_interface* to_usb_interface (int /*<<< orphan*/ ) ; 
 void* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_autopm_get_interface (TYPE_7__*) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (TYPE_7__*) ; 
 scalar_t__ usb_endpoint_dir_in (struct usb_endpoint_descriptor*) ; 
 int /*<<< orphan*/  usb_endpoint_xfer_int (struct usb_endpoint_descriptor*) ; 
 int /*<<< orphan*/  usb_fill_control_urb (TYPE_4__*,struct usb_device*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct hid_device*) ; 
 int /*<<< orphan*/  usb_fill_int_urb (TYPE_4__*,struct usb_device*,int,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,struct hid_device*,int) ; 
 int /*<<< orphan*/  usb_free_urb (TYPE_4__*) ; 
 int usb_rcvintpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int usb_sndintpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbhid_set_leds (struct hid_device*) ; 

__attribute__((used)) static int usbhid_start(struct hid_device *hid)
{
	struct usb_interface *intf = to_usb_interface(hid->dev.parent);
	struct usb_host_interface *interface = intf->cur_altsetting;
	struct usb_device *dev = interface_to_usbdev(intf);
	struct usbhid_device *usbhid = hid->driver_data;
	unsigned int n, insize = 0;
	int ret;

	clear_bit(HID_DISCONNECTED, &usbhid->iofl);

	usbhid->bufsize = HID_MIN_BUFFER_SIZE;
	hid_find_max_report(hid, HID_INPUT_REPORT, &usbhid->bufsize);
	hid_find_max_report(hid, HID_OUTPUT_REPORT, &usbhid->bufsize);
	hid_find_max_report(hid, HID_FEATURE_REPORT, &usbhid->bufsize);

	if (usbhid->bufsize > HID_MAX_BUFFER_SIZE)
		usbhid->bufsize = HID_MAX_BUFFER_SIZE;

	hid_find_max_report(hid, HID_INPUT_REPORT, &insize);

	if (insize > HID_MAX_BUFFER_SIZE)
		insize = HID_MAX_BUFFER_SIZE;

	if (hid_alloc_buffers(dev, hid)) {
		ret = -ENOMEM;
		goto fail;
	}

	for (n = 0; n < interface->desc.bNumEndpoints; n++) {
		struct usb_endpoint_descriptor *endpoint;
		int pipe;
		int interval;

		endpoint = &interface->endpoint[n].desc;
		if (!usb_endpoint_xfer_int(endpoint))
			continue;

		interval = endpoint->bInterval;

		/* Some vendors give fullspeed interval on highspeed devides */
		if (hid->quirks & HID_QUIRK_FULLSPEED_INTERVAL &&
		    dev->speed == USB_SPEED_HIGH) {
			interval = fls(endpoint->bInterval*8);
			pr_info("%s: Fixing fullspeed to highspeed interval: %d -> %d\n",
				hid->name, endpoint->bInterval, interval);
		}

		/* Change the polling interval of mice, joysticks
		 * and keyboards.
		 */
		switch (hid->collection->usage) {
		case HID_GD_MOUSE:
			if (hid_mousepoll_interval > 0)
				interval = hid_mousepoll_interval;
			break;
		case HID_GD_JOYSTICK:
			if (hid_jspoll_interval > 0)
				interval = hid_jspoll_interval;
			break;
		case HID_GD_KEYBOARD:
			if (hid_kbpoll_interval > 0)
				interval = hid_kbpoll_interval;
			break;
		}

		ret = -ENOMEM;
		if (usb_endpoint_dir_in(endpoint)) {
			if (usbhid->urbin)
				continue;
			if (!(usbhid->urbin = usb_alloc_urb(0, GFP_KERNEL)))
				goto fail;
			pipe = usb_rcvintpipe(dev, endpoint->bEndpointAddress);
			usb_fill_int_urb(usbhid->urbin, dev, pipe, usbhid->inbuf, insize,
					 hid_irq_in, hid, interval);
			usbhid->urbin->transfer_dma = usbhid->inbuf_dma;
			usbhid->urbin->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
		} else {
			if (usbhid->urbout)
				continue;
			if (!(usbhid->urbout = usb_alloc_urb(0, GFP_KERNEL)))
				goto fail;
			pipe = usb_sndintpipe(dev, endpoint->bEndpointAddress);
			usb_fill_int_urb(usbhid->urbout, dev, pipe, usbhid->outbuf, 0,
					 hid_irq_out, hid, interval);
			usbhid->urbout->transfer_dma = usbhid->outbuf_dma;
			usbhid->urbout->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;
		}
	}

	usbhid->urbctrl = usb_alloc_urb(0, GFP_KERNEL);
	if (!usbhid->urbctrl) {
		ret = -ENOMEM;
		goto fail;
	}

	usb_fill_control_urb(usbhid->urbctrl, dev, 0, (void *) usbhid->cr,
			     usbhid->ctrlbuf, 1, hid_ctrl, hid);
	usbhid->urbctrl->transfer_dma = usbhid->ctrlbuf_dma;
	usbhid->urbctrl->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

	set_bit(HID_STARTED, &usbhid->iofl);

	if (hid->quirks & HID_QUIRK_ALWAYS_POLL) {
		ret = usb_autopm_get_interface(usbhid->intf);
		if (ret)
			goto fail;
		set_bit(HID_IN_POLLING, &usbhid->iofl);
		usbhid->intf->needs_remote_wakeup = 1;
		ret = hid_start_in(hid);
		if (ret) {
			dev_err(&hid->dev,
				"failed to start in urb: %d\n", ret);
		}
		usb_autopm_put_interface(usbhid->intf);
	}

	/* Some keyboards don't work until their LEDs have been set.
	 * Since BIOSes do set the LEDs, it must be safe for any device
	 * that supports the keyboard boot protocol.
	 * In addition, enable remote wakeup by default for all keyboard
	 * devices supporting the boot protocol.
	 */
	if (interface->desc.bInterfaceSubClass == USB_INTERFACE_SUBCLASS_BOOT &&
			interface->desc.bInterfaceProtocol ==
				USB_INTERFACE_PROTOCOL_KEYBOARD) {
		usbhid_set_leds(hid);
		device_set_wakeup_enable(&dev->dev, 1);
	}
	return 0;

fail:
	usb_free_urb(usbhid->urbin);
	usb_free_urb(usbhid->urbout);
	usb_free_urb(usbhid->urbctrl);
	usbhid->urbin = NULL;
	usbhid->urbout = NULL;
	usbhid->urbctrl = NULL;
	hid_free_buffers(dev, hid);
	return ret;
}