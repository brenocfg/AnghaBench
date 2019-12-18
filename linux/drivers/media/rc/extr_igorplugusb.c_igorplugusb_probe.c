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
typedef  int /*<<< orphan*/  uint8_t ;
struct usb_interface {int /*<<< orphan*/  dev; struct usb_host_interface* cur_altsetting; } ;
struct TYPE_5__ {int bNumEndpoints; } ;
struct usb_host_interface {TYPE_2__* endpoint; TYPE_1__ desc; } ;
struct usb_endpoint_descriptor {int dummy; } ;
struct usb_device_id {int dummy; } ;
struct usb_device {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/ * parent; } ;
struct rc_dev {int allowed_protocols; int rx_resolution; int /*<<< orphan*/  timeout; int /*<<< orphan*/  map_name; int /*<<< orphan*/  driver_name; struct igorplugusb* priv; TYPE_4__ dev; int /*<<< orphan*/  input_id; int /*<<< orphan*/  input_phys; int /*<<< orphan*/  device_name; } ;
struct TYPE_7__ {int bRequestType; int /*<<< orphan*/  wLength; int /*<<< orphan*/  bRequest; } ;
struct igorplugusb {int /*<<< orphan*/  timer; int /*<<< orphan*/  urb; struct rc_dev* rc; int /*<<< orphan*/  phys; int /*<<< orphan*/  buf_in; TYPE_3__ request; int /*<<< orphan*/ * dev; } ;
struct TYPE_6__ {struct usb_endpoint_descriptor desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_DESC ; 
 int /*<<< orphan*/  DRIVER_NAME ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GET_INFRACODE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MS_TO_NS (int) ; 
 int /*<<< orphan*/  RC_DRIVER_IR_RAW ; 
 int /*<<< orphan*/  RC_MAP_HAUPPAUGE ; 
 int RC_PROTO_BIT_ALL_IR_DECODER ; 
 int RC_PROTO_BIT_NEC ; 
 int RC_PROTO_BIT_NEC32 ; 
 int RC_PROTO_BIT_NECX ; 
 int RC_PROTO_BIT_RC6_6A_20 ; 
 int RC_PROTO_BIT_RC6_6A_24 ; 
 int RC_PROTO_BIT_RC6_6A_32 ; 
 int RC_PROTO_BIT_RC6_MCE ; 
 int RC_PROTO_BIT_SANYO ; 
 int RC_PROTO_BIT_SONY20 ; 
 int /*<<< orphan*/  SET_INFRABUFFER_EMPTY ; 
 int USB_DIR_IN ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct igorplugusb* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igorplugusb_callback ; 
 int /*<<< orphan*/  igorplugusb_cmd (struct igorplugusb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igorplugusb_timer ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 struct rc_dev* rc_allocate_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rc_free_device (struct rc_dev*) ; 
 int rc_register_device (struct rc_dev*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_endpoint_dir_in (struct usb_endpoint_descriptor*) ; 
 int /*<<< orphan*/  usb_endpoint_xfer_control (struct usb_endpoint_descriptor*) ; 
 int /*<<< orphan*/  usb_fill_control_urb (int /*<<< orphan*/ ,struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct igorplugusb*) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_make_path (struct usb_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct igorplugusb*) ; 
 int /*<<< orphan*/  usb_to_input_id (struct usb_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int igorplugusb_probe(struct usb_interface *intf,
					const struct usb_device_id *id)
{
	struct usb_device *udev;
	struct usb_host_interface *idesc;
	struct usb_endpoint_descriptor *ep;
	struct igorplugusb *ir;
	struct rc_dev *rc;
	int ret = -ENOMEM;

	udev = interface_to_usbdev(intf);
	idesc = intf->cur_altsetting;

	if (idesc->desc.bNumEndpoints != 1) {
		dev_err(&intf->dev, "incorrect number of endpoints");
		return -ENODEV;
	}

	ep = &idesc->endpoint[0].desc;
	if (!usb_endpoint_dir_in(ep) || !usb_endpoint_xfer_control(ep)) {
		dev_err(&intf->dev, "endpoint incorrect");
		return -ENODEV;
	}

	ir = devm_kzalloc(&intf->dev, sizeof(*ir), GFP_KERNEL);
	if (!ir)
		return -ENOMEM;

	ir->dev = &intf->dev;

	timer_setup(&ir->timer, igorplugusb_timer, 0);

	ir->request.bRequest = GET_INFRACODE;
	ir->request.bRequestType = USB_TYPE_VENDOR | USB_DIR_IN;
	ir->request.wLength = cpu_to_le16(sizeof(ir->buf_in));

	ir->urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!ir->urb)
		goto fail;

	usb_fill_control_urb(ir->urb, udev,
		usb_rcvctrlpipe(udev, 0), (uint8_t *)&ir->request,
		ir->buf_in, sizeof(ir->buf_in), igorplugusb_callback, ir);

	usb_make_path(udev, ir->phys, sizeof(ir->phys));

	rc = rc_allocate_device(RC_DRIVER_IR_RAW);
	if (!rc)
		goto fail;

	rc->device_name = DRIVER_DESC;
	rc->input_phys = ir->phys;
	usb_to_input_id(udev, &rc->input_id);
	rc->dev.parent = &intf->dev;
	/*
	 * This device can only store 36 pulses + spaces, which is not enough
	 * for the NEC protocol and many others.
	 */
	rc->allowed_protocols = RC_PROTO_BIT_ALL_IR_DECODER &
		~(RC_PROTO_BIT_NEC | RC_PROTO_BIT_NECX | RC_PROTO_BIT_NEC32 |
		  RC_PROTO_BIT_RC6_6A_20 | RC_PROTO_BIT_RC6_6A_24 |
		  RC_PROTO_BIT_RC6_6A_32 | RC_PROTO_BIT_RC6_MCE |
		  RC_PROTO_BIT_SONY20 | RC_PROTO_BIT_SANYO);

	rc->priv = ir;
	rc->driver_name = DRIVER_NAME;
	rc->map_name = RC_MAP_HAUPPAUGE;
	rc->timeout = MS_TO_NS(100);
	rc->rx_resolution = 85333;

	ir->rc = rc;
	ret = rc_register_device(rc);
	if (ret) {
		dev_err(&intf->dev, "failed to register rc device: %d", ret);
		goto fail;
	}

	usb_set_intfdata(intf, ir);

	igorplugusb_cmd(ir, SET_INFRABUFFER_EMPTY);

	return 0;
fail:
	rc_free_device(ir->rc);
	usb_free_urb(ir->urb);
	del_timer(&ir->timer);

	return ret;
}