#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  stream_mode; } ;
struct TYPE_3__ {TYPE_2__ camera_state; } ;
struct camera_data {int /*<<< orphan*/  v4l2_lock; TYPE_1__ params; scalar_t__ streaming; int /*<<< orphan*/  hdl; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpia2_usb_stream_start (struct camera_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct camera_data* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_setup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cpia2_usb_resume(struct usb_interface *intf)
{
	struct camera_data *cam = usb_get_intfdata(intf);

	mutex_lock(&cam->v4l2_lock);
	v4l2_ctrl_handler_setup(&cam->hdl);
	if (cam->streaming) {
		cam->streaming = 0;
		cpia2_usb_stream_start(cam,
				cam->params.camera_state.stream_mode);
	}
	mutex_unlock(&cam->v4l2_lock);

	dev_info(&intf->dev, "coming out of suspend..\n");
	return 0;
}