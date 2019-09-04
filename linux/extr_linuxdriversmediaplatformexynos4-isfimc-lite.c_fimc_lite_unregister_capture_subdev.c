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
struct v4l2_subdev {int /*<<< orphan*/  entity; } ;
struct fimc_lite {int /*<<< orphan*/  ctrl_handler; struct v4l2_subdev subdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister_subdev (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_set_subdevdata (struct v4l2_subdev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fimc_lite_unregister_capture_subdev(struct fimc_lite *fimc)
{
	struct v4l2_subdev *sd = &fimc->subdev;

	v4l2_device_unregister_subdev(sd);
	media_entity_cleanup(&sd->entity);
	v4l2_ctrl_handler_free(&fimc->ctrl_handler);
	v4l2_set_subdevdata(sd, NULL);
}