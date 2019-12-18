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
struct v4l2_async_notifier {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ctrl_handler; } ;
struct mcam_camera {int /*<<< orphan*/  ctrl_handler; TYPE_1__ v4l2_dev; } ;

/* Variables and functions */
 struct mcam_camera* notifier_to_mcam (struct v4l2_async_notifier*) ; 
 int v4l2_ctrl_handler_init (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mccic_notify_complete(struct v4l2_async_notifier *notifier)
{
	struct mcam_camera *cam = notifier_to_mcam(notifier);
	int ret;

	/*
	 * Get the v4l2 setup done.
	 */
	ret = v4l2_ctrl_handler_init(&cam->ctrl_handler, 10);
	if (!ret)
		cam->v4l2_dev.ctrl_handler = &cam->ctrl_handler;

	return ret;
}