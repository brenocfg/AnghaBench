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
struct usb_interface {int dummy; } ;
struct camera_data {int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  wq_stream; TYPE_1__* curbuff; scalar_t__ buffers; int /*<<< orphan*/  v4l2_lock; } ;
struct TYPE_2__ {scalar_t__ length; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int /*<<< orphan*/  FRAME_READY ; 
 int /*<<< orphan*/  LOG (char*) ; 
 int /*<<< orphan*/  cpia2_unregister_camera (struct camera_data*) ; 
 int /*<<< orphan*/  cpia2_usb_stream_stop (struct camera_data*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct camera_data* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cpia2_usb_disconnect(struct usb_interface *intf)
{
	struct camera_data *cam = usb_get_intfdata(intf);
	usb_set_intfdata(intf, NULL);

	DBG("Stopping stream\n");
	cpia2_usb_stream_stop(cam);

	mutex_lock(&cam->v4l2_lock);
	DBG("Unregistering camera\n");
	cpia2_unregister_camera(cam);
	v4l2_device_disconnect(&cam->v4l2_dev);
	mutex_unlock(&cam->v4l2_lock);

	if(cam->buffers) {
		DBG("Wakeup waiting processes\n");
		cam->curbuff->status = FRAME_READY;
		cam->curbuff->length = 0;
		wake_up_interruptible(&cam->wq_stream);
	}

	v4l2_device_put(&cam->v4l2_dev);

	LOG("CPiA2 camera disconnected.\n");
}