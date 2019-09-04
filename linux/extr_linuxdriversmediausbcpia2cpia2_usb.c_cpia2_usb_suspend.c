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
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct camera_data {int streaming; int /*<<< orphan*/  v4l2_lock; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpia2_usb_stream_stop (struct camera_data*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct camera_data* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static int cpia2_usb_suspend(struct usb_interface *intf, pm_message_t message)
{
	struct camera_data *cam = usb_get_intfdata(intf);

	mutex_lock(&cam->v4l2_lock);
	if (cam->streaming) {
		cpia2_usb_stream_stop(cam);
		cam->streaming = 1;
	}
	mutex_unlock(&cam->v4l2_lock);

	dev_info(&intf->dev, "going into suspend..\n");
	return 0;
}