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
struct v4l2_subdev_ops {int dummy; } ;
struct media_entity {int /*<<< orphan*/ * ops; } ;
struct v4l2_subdev {int flags; int /*<<< orphan*/  grp_id; int /*<<< orphan*/  name; struct media_entity entity; } ;
struct TYPE_2__ {int flags; } ;
struct ispstat {TYPE_1__ pad; struct v4l2_subdev subdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int MEDIA_PAD_FL_MUST_CONNECT ; 
 int MEDIA_PAD_FL_SINK ; 
 int V4L2_SUBDEV_FL_HAS_DEVNODE ; 
 int V4L2_SUBDEV_FL_HAS_EVENTS ; 
 int /*<<< orphan*/  V4L2_SUBDEV_NAME_SIZE ; 
 int media_entity_pads_init (struct media_entity*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  v4l2_set_subdevdata (struct v4l2_subdev*,struct ispstat*) ; 
 int /*<<< orphan*/  v4l2_subdev_init (struct v4l2_subdev*,struct v4l2_subdev_ops const*) ; 

__attribute__((used)) static int isp_stat_init_entities(struct ispstat *stat, const char *name,
				  const struct v4l2_subdev_ops *sd_ops)
{
	struct v4l2_subdev *subdev = &stat->subdev;
	struct media_entity *me = &subdev->entity;

	v4l2_subdev_init(subdev, sd_ops);
	snprintf(subdev->name, V4L2_SUBDEV_NAME_SIZE, "OMAP3 ISP %s", name);
	subdev->grp_id = BIT(16);	/* group ID for isp subdevs */
	subdev->flags |= V4L2_SUBDEV_FL_HAS_EVENTS | V4L2_SUBDEV_FL_HAS_DEVNODE;
	v4l2_set_subdevdata(subdev, stat);

	stat->pad.flags = MEDIA_PAD_FL_SINK | MEDIA_PAD_FL_MUST_CONNECT;
	me->ops = NULL;

	return media_entity_pads_init(me, 1, &stat->pad);
}