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
struct usb_interface {struct usb_host_interface* cur_altsetting; } ;
struct usb_host_interface {int dummy; } ;
struct urb {int dummy; } ;
struct imon_context {scalar_t__ display_type; int dev_present_intf1; int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; int /*<<< orphan*/  usbdev_intf1; int /*<<< orphan*/ * touch; struct urb* rx_urb_intf1; TYPE_1__* rx_endpoint_intf1; int /*<<< orphan*/  usb_rx_buf; int /*<<< orphan*/  ttimer; } ;
struct TYPE_2__ {int /*<<< orphan*/  bInterval; int /*<<< orphan*/  bEndpointAddress; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IMON_DISPLAY_TYPE_VGA ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  imon_find_endpoints (struct imon_context*,struct usb_host_interface*) ; 
 int /*<<< orphan*/ * imon_init_touch (struct imon_context*) ; 
 int /*<<< orphan*/  imon_touch_display_timeout ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct urb* usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_fill_int_urb (struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct imon_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 
 int /*<<< orphan*/  usb_get_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_put_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvintpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rx_callback_intf1 ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct imon_context *imon_init_intf1(struct usb_interface *intf,
					    struct imon_context *ictx)
{
	struct urb *rx_urb;
	struct usb_host_interface *iface_desc;
	int ret = -ENOMEM;

	rx_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!rx_urb)
		goto rx_urb_alloc_failed;

	mutex_lock(&ictx->lock);

	if (ictx->display_type == IMON_DISPLAY_TYPE_VGA) {
		timer_setup(&ictx->ttimer, imon_touch_display_timeout, 0);
	}

	ictx->usbdev_intf1 = usb_get_dev(interface_to_usbdev(intf));
	ictx->rx_urb_intf1 = rx_urb;

	ret = -ENODEV;
	iface_desc = intf->cur_altsetting;
	if (!imon_find_endpoints(ictx, iface_desc))
		goto find_endpoint_failed;

	if (ictx->display_type == IMON_DISPLAY_TYPE_VGA) {
		ictx->touch = imon_init_touch(ictx);
		if (!ictx->touch)
			goto touch_setup_failed;
	} else
		ictx->touch = NULL;

	usb_fill_int_urb(ictx->rx_urb_intf1, ictx->usbdev_intf1,
		usb_rcvintpipe(ictx->usbdev_intf1,
			ictx->rx_endpoint_intf1->bEndpointAddress),
		ictx->usb_rx_buf, sizeof(ictx->usb_rx_buf),
		usb_rx_callback_intf1, ictx,
		ictx->rx_endpoint_intf1->bInterval);

	ret = usb_submit_urb(ictx->rx_urb_intf1, GFP_KERNEL);

	if (ret) {
		pr_err("usb_submit_urb failed for intf1 (%d)\n", ret);
		goto urb_submit_failed;
	}

	ictx->dev_present_intf1 = true;

	mutex_unlock(&ictx->lock);
	return ictx;

urb_submit_failed:
	if (ictx->touch)
		input_unregister_device(ictx->touch);
touch_setup_failed:
find_endpoint_failed:
	usb_put_dev(ictx->usbdev_intf1);
	mutex_unlock(&ictx->lock);
	usb_free_urb(rx_urb);
rx_urb_alloc_failed:
	dev_err(ictx->dev, "unable to initialize intf1, err %d\n", ret);

	return NULL;
}