#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  release; } ;
struct camera_data {int /*<<< orphan*/  wq_stream; int /*<<< orphan*/  v4l2_lock; TYPE_1__ v4l2_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cpia2_camera_release ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct camera_data*) ; 
 struct camera_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ v4l2_device_register (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_err (TYPE_1__*,char*) ; 

struct camera_data *cpia2_init_camera_struct(struct usb_interface *intf)
{
	struct camera_data *cam;

	cam = kzalloc(sizeof(*cam), GFP_KERNEL);

	if (!cam) {
		ERR("couldn't kmalloc cpia2 struct\n");
		return NULL;
	}

	cam->v4l2_dev.release = cpia2_camera_release;
	if (v4l2_device_register(&intf->dev, &cam->v4l2_dev) < 0) {
		v4l2_err(&cam->v4l2_dev, "couldn't register v4l2_device\n");
		kfree(cam);
		return NULL;
	}

	mutex_init(&cam->v4l2_lock);
	init_waitqueue_head(&cam->wq_stream);

	return cam;
}