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
struct stk1160 {int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  vb_queue_lock; int /*<<< orphan*/  v4l_lock; int /*<<< orphan*/ * udev; int /*<<< orphan*/  vdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stk1160_clear_queue (struct stk1160*) ; 
 int /*<<< orphan*/  stk1160_uninit_isoc (struct stk1160*) ; 
 struct stk1160* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stk1160_disconnect(struct usb_interface *interface)
{
	struct stk1160 *dev;

	dev = usb_get_intfdata(interface);
	usb_set_intfdata(interface, NULL);

	/*
	 * Wait until all current v4l2 operation are finished
	 * then deallocate resources
	 */
	mutex_lock(&dev->vb_queue_lock);
	mutex_lock(&dev->v4l_lock);

	/* Here is the only place where isoc get released */
	stk1160_uninit_isoc(dev);

	stk1160_clear_queue(dev);

	video_unregister_device(&dev->vdev);
	v4l2_device_disconnect(&dev->v4l2_dev);

	/* This way current users can detect device is gone */
	dev->udev = NULL;

	mutex_unlock(&dev->v4l_lock);
	mutex_unlock(&dev->vb_queue_lock);

	/*
	 * This calls stk1160_release if it's the last reference.
	 * Otherwise, release is postponed until there are no users left.
	 */
	v4l2_device_put(&dev->v4l2_dev);
}