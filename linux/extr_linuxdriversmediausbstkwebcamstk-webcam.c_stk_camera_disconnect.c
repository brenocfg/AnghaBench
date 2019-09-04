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
struct usb_interface {int dummy; } ;
struct stk_camera {int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  hdl; int /*<<< orphan*/  vdev; int /*<<< orphan*/  wait_frame; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct stk_camera*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unset_present (struct stk_camera*) ; 
 struct stk_camera* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_device_node_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stk_camera_disconnect(struct usb_interface *interface)
{
	struct stk_camera *dev = usb_get_intfdata(interface);

	usb_set_intfdata(interface, NULL);
	unset_present(dev);

	wake_up_interruptible(&dev->wait_frame);

	pr_info("Syntek USB2.0 Camera release resources device %s\n",
		video_device_node_name(&dev->vdev));

	video_unregister_device(&dev->vdev);
	v4l2_ctrl_handler_free(&dev->hdl);
	v4l2_device_unregister(&dev->v4l2_dev);
	kfree(dev);
}