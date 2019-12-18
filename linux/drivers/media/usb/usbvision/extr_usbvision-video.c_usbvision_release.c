#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct usb_usbvision {int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  hdl; int /*<<< orphan*/  ctrl_urb; struct usb_usbvision* alt_max_pkt_size; int /*<<< orphan*/  vdev; scalar_t__ initialized; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_PROBE ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (struct usb_usbvision*) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbvision_remove_sysfs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbvision_unregister_video (struct usb_usbvision*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void usbvision_release(struct usb_usbvision *usbvision)
{
	PDEBUG(DBG_PROBE, "");

	usbvision->initialized = 0;

	usbvision_remove_sysfs(&usbvision->vdev);
	usbvision_unregister_video(usbvision);
	kfree(usbvision->alt_max_pkt_size);

	usb_free_urb(usbvision->ctrl_urb);

	v4l2_ctrl_handler_free(&usbvision->hdl);
	v4l2_device_unregister(&usbvision->v4l2_dev);
	kfree(usbvision);

	PDEBUG(DBG_PROBE, "success");
}