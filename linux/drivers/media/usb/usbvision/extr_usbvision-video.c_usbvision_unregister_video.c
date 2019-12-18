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
struct usb_usbvision {int /*<<< orphan*/  vdev; int /*<<< orphan*/  rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_PROBE ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_device_node_name (int /*<<< orphan*/ *) ; 
 scalar_t__ video_is_registered (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void usbvision_unregister_video(struct usb_usbvision *usbvision)
{
	/* Radio Device: */
	if (video_is_registered(&usbvision->rdev)) {
		PDEBUG(DBG_PROBE, "unregister %s [v4l2]",
		       video_device_node_name(&usbvision->rdev));
		video_unregister_device(&usbvision->rdev);
	}

	/* Video Device: */
	if (video_is_registered(&usbvision->vdev)) {
		PDEBUG(DBG_PROBE, "unregister %s [v4l2]",
		       video_device_node_name(&usbvision->vdev));
		video_unregister_device(&usbvision->vdev);
	}
}