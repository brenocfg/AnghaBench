#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct v4l2_subdev {scalar_t__ grp_id; int /*<<< orphan*/  ctrl_handler; } ;
struct media_pad {TYPE_4__* entity; } ;
struct media_entity {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  entity; } ;
struct fimc_vid_cap {scalar_t__ input; TYPE_3__* ctx; TYPE_1__ subdev; scalar_t__ inh_sensor_ctrls; scalar_t__ user_subdev_api; } ;
struct fimc_dev {struct fimc_vid_cap vid_cap; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
struct TYPE_6__ {int /*<<< orphan*/  handler; } ;
struct TYPE_7__ {TYPE_2__ ctrls; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int MEDIA_LNK_FL_ENABLED ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 
 struct v4l2_subdev* fimc_find_remote_sensor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_media_entity_v4l2_subdev (TYPE_4__*) ; 
 struct v4l2_subdev* media_entity_to_v4l2_subdev (struct media_entity*) ; 
 int v4l2_ctrl_add_handler (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct fimc_dev* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int fimc_link_setup(struct media_entity *entity,
			   const struct media_pad *local,
			   const struct media_pad *remote, u32 flags)
{
	struct v4l2_subdev *sd = media_entity_to_v4l2_subdev(entity);
	struct fimc_dev *fimc = v4l2_get_subdevdata(sd);
	struct fimc_vid_cap *vc = &fimc->vid_cap;
	struct v4l2_subdev *sensor;

	if (!is_media_entity_v4l2_subdev(remote->entity))
		return -EINVAL;

	if (WARN_ON(fimc == NULL))
		return 0;

	dbg("%s --> %s, flags: 0x%x. input: 0x%x",
	    local->entity->name, remote->entity->name, flags,
	    fimc->vid_cap.input);

	if (!(flags & MEDIA_LNK_FL_ENABLED)) {
		fimc->vid_cap.input = 0;
		return 0;
	}

	if (vc->input != 0)
		return -EBUSY;

	vc->input = sd->grp_id;

	if (vc->user_subdev_api || vc->inh_sensor_ctrls)
		return 0;

	/* Inherit V4L2 controls from the image sensor subdev. */
	sensor = fimc_find_remote_sensor(&vc->subdev.entity);
	if (sensor == NULL)
		return 0;

	return v4l2_ctrl_add_handler(&vc->ctx->ctrls.handler,
				     sensor->ctrl_handler, NULL, true);
}