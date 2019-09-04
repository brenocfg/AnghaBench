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
struct amradio_device {int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  lock; int /*<<< orphan*/  vdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  amradio_set_mute (struct amradio_device*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct amradio_device* to_amradio_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void usb_amradio_disconnect(struct usb_interface *intf)
{
	struct amradio_device *radio = to_amradio_dev(usb_get_intfdata(intf));

	mutex_lock(&radio->lock);
	video_unregister_device(&radio->vdev);
	amradio_set_mute(radio, true);
	usb_set_intfdata(intf, NULL);
	v4l2_device_disconnect(&radio->v4l2_dev);
	mutex_unlock(&radio->lock);
	v4l2_device_put(&radio->v4l2_dev);
}