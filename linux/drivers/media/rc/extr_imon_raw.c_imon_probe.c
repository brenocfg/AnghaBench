#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int /*<<< orphan*/  dev; struct usb_host_interface* cur_altsetting; } ;
struct TYPE_4__ {int bNumEndpoints; } ;
struct usb_host_interface {TYPE_2__* endpoint; TYPE_1__ desc; } ;
struct usb_endpoint_descriptor {int /*<<< orphan*/  bInterval; int /*<<< orphan*/  bEndpointAddress; } ;
struct usb_device_id {int dummy; } ;
struct usb_device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/ * parent; } ;
struct rc_dev {char* device_name; struct imon* priv; int /*<<< orphan*/  rx_resolution; int /*<<< orphan*/  map_name; int /*<<< orphan*/  allowed_protocols; TYPE_3__ dev; int /*<<< orphan*/  input_id; int /*<<< orphan*/  input_phys; int /*<<< orphan*/  driver_name; } ;
struct imon {int /*<<< orphan*/  ir_urb; struct rc_dev* rcdev; int /*<<< orphan*/  phys; int /*<<< orphan*/  ir_buf; int /*<<< orphan*/ * dev; } ;
struct TYPE_5__ {struct usb_endpoint_descriptor desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_DURATION ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int /*<<< orphan*/  RC_DRIVER_IR_RAW ; 
 int /*<<< orphan*/  RC_MAP_IMON_RSC ; 
 int /*<<< orphan*/  RC_PROTO_BIT_ALL_IR_DECODER ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct imon* devm_kmalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct rc_dev* devm_rc_allocate_device (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int devm_rc_register_device (int /*<<< orphan*/ *,struct rc_dev*) ; 
 int /*<<< orphan*/  imon_ir_rx ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_endpoint_is_int_in (struct usb_endpoint_descriptor*) ; 
 int /*<<< orphan*/  usb_fill_int_urb (int /*<<< orphan*/ ,struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct imon*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_make_path (struct usb_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_rcvintpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct imon*) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_to_input_id (struct usb_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int imon_probe(struct usb_interface *intf,
		      const struct usb_device_id *id)
{
	struct usb_endpoint_descriptor *ir_ep = NULL;
	struct usb_host_interface *idesc;
	struct usb_device *udev;
	struct rc_dev *rcdev;
	struct imon *imon;
	int i, ret;

	udev = interface_to_usbdev(intf);
	idesc = intf->cur_altsetting;

	for (i = 0; i < idesc->desc.bNumEndpoints; i++) {
		struct usb_endpoint_descriptor *ep = &idesc->endpoint[i].desc;

		if (usb_endpoint_is_int_in(ep)) {
			ir_ep = ep;
			break;
		}
	}

	if (!ir_ep) {
		dev_err(&intf->dev, "IR endpoint missing");
		return -ENODEV;
	}

	imon = devm_kmalloc(&intf->dev, sizeof(*imon), GFP_KERNEL);
	if (!imon)
		return -ENOMEM;

	imon->ir_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!imon->ir_urb)
		return -ENOMEM;

	imon->dev = &intf->dev;
	usb_fill_int_urb(imon->ir_urb, udev,
			 usb_rcvintpipe(udev, ir_ep->bEndpointAddress),
			 &imon->ir_buf, sizeof(imon->ir_buf),
			 imon_ir_rx, imon, ir_ep->bInterval);

	rcdev = devm_rc_allocate_device(&intf->dev, RC_DRIVER_IR_RAW);
	if (!rcdev) {
		ret = -ENOMEM;
		goto free_urb;
	}

	usb_make_path(udev, imon->phys, sizeof(imon->phys));

	rcdev->device_name = "iMON Station";
	rcdev->driver_name = KBUILD_MODNAME;
	rcdev->input_phys = imon->phys;
	usb_to_input_id(udev, &rcdev->input_id);
	rcdev->dev.parent = &intf->dev;
	rcdev->allowed_protocols = RC_PROTO_BIT_ALL_IR_DECODER;
	rcdev->map_name = RC_MAP_IMON_RSC;
	rcdev->rx_resolution = BIT_DURATION;
	rcdev->priv = imon;

	ret = devm_rc_register_device(&intf->dev, rcdev);
	if (ret)
		goto free_urb;

	imon->rcdev = rcdev;

	ret = usb_submit_urb(imon->ir_urb, GFP_KERNEL);
	if (ret)
		goto free_urb;

	usb_set_intfdata(intf, imon);

	return 0;

free_urb:
	usb_free_urb(imon->ir_urb);
	return ret;
}