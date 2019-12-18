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
struct v4l2_subdev {int /*<<< orphan*/  entity; int /*<<< orphan*/  ctrl_handler; int /*<<< orphan*/  fwnode; } ;
struct v4l2_flash {struct v4l2_subdev sd; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct v4l2_flash*) ; 
 int /*<<< orphan*/  fwnode_handle_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_async_unregister_subdev (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ ) ; 

void v4l2_flash_release(struct v4l2_flash *v4l2_flash)
{
	struct v4l2_subdev *sd;

	if (IS_ERR_OR_NULL(v4l2_flash))
		return;

	sd = &v4l2_flash->sd;

	v4l2_async_unregister_subdev(sd);

	fwnode_handle_put(sd->fwnode);

	v4l2_ctrl_handler_free(sd->ctrl_handler);
	media_entity_cleanup(&sd->entity);
}