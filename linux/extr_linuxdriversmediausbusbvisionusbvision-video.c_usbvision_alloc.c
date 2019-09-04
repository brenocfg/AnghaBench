#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * ctrl_handler; } ;
struct usb_usbvision {TYPE_1__ v4l2_dev; int /*<<< orphan*/  hdl; int /*<<< orphan*/  ctrl_urb; int /*<<< orphan*/  v4l2_lock; struct usb_device* dev; } ;
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  USBVISION_URB_FRAMES ; 
 int /*<<< orphan*/  kfree (struct usb_usbvision*) ; 
 struct usb_usbvision* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_alloc_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 scalar_t__ v4l2_ctrl_handler_init (int /*<<< orphan*/ *,int) ; 
 scalar_t__ v4l2_device_register (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_device_unregister (TYPE_1__*) ; 

__attribute__((used)) static struct usb_usbvision *usbvision_alloc(struct usb_device *dev,
					     struct usb_interface *intf)
{
	struct usb_usbvision *usbvision;

	usbvision = kzalloc(sizeof(*usbvision), GFP_KERNEL);
	if (!usbvision)
		return NULL;

	usbvision->dev = dev;
	if (v4l2_device_register(&intf->dev, &usbvision->v4l2_dev))
		goto err_free;

	if (v4l2_ctrl_handler_init(&usbvision->hdl, 4))
		goto err_unreg;
	usbvision->v4l2_dev.ctrl_handler = &usbvision->hdl;
	mutex_init(&usbvision->v4l2_lock);

	/* prepare control urb for control messages during interrupts */
	usbvision->ctrl_urb = usb_alloc_urb(USBVISION_URB_FRAMES, GFP_KERNEL);
	if (!usbvision->ctrl_urb)
		goto err_unreg;

	return usbvision;

err_unreg:
	v4l2_ctrl_handler_free(&usbvision->hdl);
	v4l2_device_unregister(&usbvision->v4l2_dev);
err_free:
	kfree(usbvision);
	return NULL;
}