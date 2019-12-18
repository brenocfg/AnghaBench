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
struct usb_interface {int /*<<< orphan*/  dev; struct usb_host_interface* cur_altsetting; } ;
struct usb_host_interface {int dummy; } ;
struct usb_endpoint_descriptor {int /*<<< orphan*/  bInterval; int /*<<< orphan*/  bEndpointAddress; } ;
struct usb_device_id {int dummy; } ;
struct TYPE_2__ {scalar_t__ bDeviceProtocol; } ;
struct usb_device {int /*<<< orphan*/  dev; scalar_t__ parent; TYPE_1__ descriptor; } ;
struct lvs_rh {int /*<<< orphan*/  urb; int /*<<< orphan*/ * buffer; int /*<<< orphan*/  rh_work; int /*<<< orphan*/  descriptor; struct usb_interface* intf; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_CTRL_GET_TIMEOUT ; 
 int USB_DIR_IN ; 
 int USB_DT_HUB_NONVAR_SIZE ; 
 int USB_DT_SS_HUB ; 
 int /*<<< orphan*/  USB_DT_SS_HUB_SIZE ; 
 scalar_t__ USB_HUB_PR_SS ; 
 int /*<<< orphan*/  USB_REQ_GET_DESCRIPTOR ; 
 int USB_RT_HUB ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct lvs_rh* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  lvs_rh_irq ; 
 int /*<<< orphan*/  lvs_rh_work ; 
 int /*<<< orphan*/  usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_int_urb (int /*<<< orphan*/ ,struct usb_device*,unsigned int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct lvs_rh*,int /*<<< orphan*/ ) ; 
 int usb_find_int_in_endpoint (struct usb_host_interface*,struct usb_endpoint_descriptor**) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 int usb_maxpacket (struct usb_device*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_pipeout (unsigned int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 unsigned int usb_rcvintpipe (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct lvs_rh*) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lvs_rh_probe(struct usb_interface *intf,
		const struct usb_device_id *id)
{
	struct usb_device *hdev;
	struct usb_host_interface *desc;
	struct usb_endpoint_descriptor *endpoint;
	struct lvs_rh *lvs;
	unsigned int pipe;
	int ret, maxp;

	hdev = interface_to_usbdev(intf);
	desc = intf->cur_altsetting;

	ret = usb_find_int_in_endpoint(desc, &endpoint);
	if (ret)
		return ret;

	/* valid only for SS root hub */
	if (hdev->descriptor.bDeviceProtocol != USB_HUB_PR_SS || hdev->parent) {
		dev_err(&intf->dev, "Bind LVS driver with SS root Hub only\n");
		return -EINVAL;
	}

	lvs = devm_kzalloc(&intf->dev, sizeof(*lvs), GFP_KERNEL);
	if (!lvs)
		return -ENOMEM;

	lvs->intf = intf;
	usb_set_intfdata(intf, lvs);

	/* how many number of ports this root hub has */
	ret = usb_control_msg(hdev, usb_rcvctrlpipe(hdev, 0),
			USB_REQ_GET_DESCRIPTOR, USB_DIR_IN | USB_RT_HUB,
			USB_DT_SS_HUB << 8, 0, &lvs->descriptor,
			USB_DT_SS_HUB_SIZE, USB_CTRL_GET_TIMEOUT);
	if (ret < (USB_DT_HUB_NONVAR_SIZE + 2)) {
		dev_err(&hdev->dev, "wrong root hub descriptor read %d\n", ret);
		return ret;
	}

	/* submit urb to poll interrupt endpoint */
	lvs->urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!lvs->urb)
		return -ENOMEM;

	INIT_WORK(&lvs->rh_work, lvs_rh_work);

	pipe = usb_rcvintpipe(hdev, endpoint->bEndpointAddress);
	maxp = usb_maxpacket(hdev, pipe, usb_pipeout(pipe));
	usb_fill_int_urb(lvs->urb, hdev, pipe, &lvs->buffer[0], maxp,
			lvs_rh_irq, lvs, endpoint->bInterval);

	ret = usb_submit_urb(lvs->urb, GFP_KERNEL);
	if (ret < 0) {
		dev_err(&intf->dev, "couldn't submit lvs urb %d\n", ret);
		goto free_urb;
	}

	return ret;

free_urb:
	usb_free_urb(lvs->urb);
	return ret;
}