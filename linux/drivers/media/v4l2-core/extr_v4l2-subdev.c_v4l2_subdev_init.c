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
struct TYPE_2__ {char* name; int /*<<< orphan*/  function; int /*<<< orphan*/  obj_type; } ;
struct v4l2_subdev {char* name; TYPE_1__ entity; int /*<<< orphan*/ * host_priv; int /*<<< orphan*/ * dev_priv; scalar_t__ grp_id; scalar_t__ flags; int /*<<< orphan*/ * v4l2_dev; struct v4l2_subdev_ops const* ops; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MEDIA_ENTITY_TYPE_V4L2_SUBDEV ; 
 int /*<<< orphan*/  MEDIA_ENT_F_V4L2_SUBDEV_UNKNOWN ; 

void v4l2_subdev_init(struct v4l2_subdev *sd, const struct v4l2_subdev_ops *ops)
{
	INIT_LIST_HEAD(&sd->list);
	BUG_ON(!ops);
	sd->ops = ops;
	sd->v4l2_dev = NULL;
	sd->flags = 0;
	sd->name[0] = '\0';
	sd->grp_id = 0;
	sd->dev_priv = NULL;
	sd->host_priv = NULL;
#if defined(CONFIG_MEDIA_CONTROLLER)
	sd->entity.name = sd->name;
	sd->entity.obj_type = MEDIA_ENTITY_TYPE_V4L2_SUBDEV;
	sd->entity.function = MEDIA_ENT_F_V4L2_SUBDEV_UNKNOWN;
#endif
}