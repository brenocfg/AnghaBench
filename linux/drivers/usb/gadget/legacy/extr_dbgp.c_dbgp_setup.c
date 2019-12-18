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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct usb_request {int length; int zero; int /*<<< orphan*/  complete; int /*<<< orphan*/  buf; } ;
struct usb_gadget {TYPE_2__* ep0; } ;
struct usb_ctrlrequest {scalar_t__ bRequest; int /*<<< orphan*/  wLength; int /*<<< orphan*/  wValue; } ;
struct TYPE_8__ {TYPE_1__* gadget; int /*<<< orphan*/  serial; struct usb_request* req; } ;
struct TYPE_7__ {int /*<<< orphan*/  bMaxPacketSize0; } ;
struct TYPE_6__ {int /*<<< orphan*/  maxpacket; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int USB_DEVICE_DEBUG_MODE ; 
#define  USB_DT_DEBUG 129 
#define  USB_DT_DEVICE 128 
 scalar_t__ USB_REQ_GET_DESCRIPTOR ; 
 scalar_t__ USB_REQ_SET_FEATURE ; 
 int /*<<< orphan*/  dbg_desc ; 
 TYPE_4__ dbgp ; 
 int dbgp_configure_endpoints (struct usb_gadget*) ; 
 int dbgp_enable_ep () ; 
 int /*<<< orphan*/  dbgp_setup_complete ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 TYPE_3__ device_desc ; 
 int gserial_connect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  tty_line ; 
 int usb_ep_queue (TYPE_2__*,struct usb_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dbgp_setup(struct usb_gadget *gadget,
		      const struct usb_ctrlrequest *ctrl)
{
	struct usb_request *req = dbgp.req;
	u8 request = ctrl->bRequest;
	u16 value = le16_to_cpu(ctrl->wValue);
	u16 length = le16_to_cpu(ctrl->wLength);
	int err = -EOPNOTSUPP;
	void *data = NULL;
	u16 len = 0;

	if (request == USB_REQ_GET_DESCRIPTOR) {
		switch (value>>8) {
		case USB_DT_DEVICE:
			dev_dbg(&dbgp.gadget->dev, "setup: desc device\n");
			len = sizeof device_desc;
			data = &device_desc;
			device_desc.bMaxPacketSize0 = gadget->ep0->maxpacket;
			break;
		case USB_DT_DEBUG:
			dev_dbg(&dbgp.gadget->dev, "setup: desc debug\n");
			len = sizeof dbg_desc;
			data = &dbg_desc;
			break;
		default:
			goto fail;
		}
		err = 0;
	} else if (request == USB_REQ_SET_FEATURE &&
		   value == USB_DEVICE_DEBUG_MODE) {
		dev_dbg(&dbgp.gadget->dev, "setup: feat debug\n");
#ifdef CONFIG_USB_G_DBGP_PRINTK
		err = dbgp_enable_ep();
#else
		err = dbgp_configure_endpoints(gadget);
		if (err < 0) {
			goto fail;
		}
		err = gserial_connect(dbgp.serial, tty_line);
#endif
		if (err < 0)
			goto fail;
	} else
		goto fail;

	req->length = min(length, len);
	req->zero = len < req->length;
	if (data && req->length)
		memcpy(req->buf, data, req->length);

	req->complete = dbgp_setup_complete;
	return usb_ep_queue(gadget->ep0, req, GFP_ATOMIC);

fail:
	dev_dbg(&dbgp.gadget->dev,
		"setup: failure req %x v %x\n", request, value);
	return err;
}