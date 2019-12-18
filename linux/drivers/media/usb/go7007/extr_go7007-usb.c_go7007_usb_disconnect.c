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
struct go7007 {int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  serialize_lock; int /*<<< orphan*/  vdev; int /*<<< orphan*/  status; scalar_t__ audio_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATUS_SHUTDOWN ; 
 int /*<<< orphan*/  go7007_snd_remove (struct go7007*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct go7007* to_go7007 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  v4l2_device_disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void go7007_usb_disconnect(struct usb_interface *intf)
{
	struct go7007 *go = to_go7007(usb_get_intfdata(intf));

	mutex_lock(&go->queue_lock);
	mutex_lock(&go->serialize_lock);

	if (go->audio_enabled)
		go7007_snd_remove(go);

	go->status = STATUS_SHUTDOWN;
	v4l2_device_disconnect(&go->v4l2_dev);
	video_unregister_device(&go->vdev);
	mutex_unlock(&go->serialize_lock);
	mutex_unlock(&go->queue_lock);

	v4l2_device_put(&go->v4l2_dev);
}