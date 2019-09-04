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
struct cx231xx {scalar_t__ users; int /*<<< orphan*/  lock; int /*<<< orphan*/  wait_stream; int /*<<< orphan*/  wait_frame; scalar_t__ USE_ISO; int /*<<< orphan*/  vdev; int /*<<< orphan*/  dev; int /*<<< orphan*/  open; int /*<<< orphan*/  state; int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_DISCONNECTED ; 
 int /*<<< orphan*/  cx231xx_close_extension (struct cx231xx*) ; 
 int /*<<< orphan*/  cx231xx_ir_exit (struct cx231xx*) ; 
 int /*<<< orphan*/  cx231xx_release_resources (struct cx231xx*) ; 
 int /*<<< orphan*/  cx231xx_uninit_bulk (struct cx231xx*) ; 
 int /*<<< orphan*/  cx231xx_uninit_isoc (struct cx231xx*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_request_modules (struct cx231xx*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct cx231xx* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_device_node_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cx231xx_usb_disconnect(struct usb_interface *interface)
{
	struct cx231xx *dev;

	dev = usb_get_intfdata(interface);
	usb_set_intfdata(interface, NULL);

	if (!dev)
		return;

	if (!dev->udev)
		return;

	dev->state |= DEV_DISCONNECTED;

	flush_request_modules(dev);

	/* wait until all current v4l2 io is finished then deallocate
	   resources */
	mutex_lock(&dev->lock);

	wake_up_interruptible_all(&dev->open);

	if (dev->users) {
		dev_warn(dev->dev,
			 "device %s is open! Deregistration and memory deallocation are deferred on close.\n",
			 video_device_node_name(&dev->vdev));

		/* Even having users, it is safe to remove the RC i2c driver */
		cx231xx_ir_exit(dev);

		if (dev->USE_ISO)
			cx231xx_uninit_isoc(dev);
		else
			cx231xx_uninit_bulk(dev);
		wake_up_interruptible(&dev->wait_frame);
		wake_up_interruptible(&dev->wait_stream);
	} else {
	}

	cx231xx_close_extension(dev);

	mutex_unlock(&dev->lock);

	if (!dev->users)
		cx231xx_release_resources(dev);
}