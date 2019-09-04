#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_7__ {int /*<<< orphan*/ * ops; int /*<<< orphan*/  function; } ;
struct v4l2_subdev {TYPE_2__ entity; int /*<<< orphan*/  name; int /*<<< orphan*/  flags; } ;
struct vsp1_entity {scalar_t__ type; scalar_t__ index; unsigned int source_pad; struct v4l2_subdev subdev; int /*<<< orphan*/ * config; TYPE_3__* pads; int /*<<< orphan*/ * sources; struct vsp1_device* vsp1; int /*<<< orphan*/  lock; TYPE_1__* route; } ;
struct vsp1_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  media_ops; } ;
struct v4l2_subdev_ops {int dummy; } ;
struct TYPE_8__ {void* flags; } ;
struct TYPE_6__ {scalar_t__ type; scalar_t__ index; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* MEDIA_PAD_FL_SINK ; 
 void* MEDIA_PAD_FL_SOURCE ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FL_HAS_DEVNODE ; 
 char* dev_name (int /*<<< orphan*/ ) ; 
 void* devm_kcalloc (int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ) ; 
 unsigned int max (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  media_entity_cleanup (TYPE_2__*) ; 
 int media_entity_pads_init (TYPE_2__*,unsigned int,TYPE_3__*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,char const*) ; 
 int /*<<< orphan*/ * v4l2_subdev_alloc_pad_config (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_subdev_init (struct v4l2_subdev*,struct v4l2_subdev_ops const*) ; 
 int /*<<< orphan*/  vsp1_entity_init_cfg (struct v4l2_subdev*,int /*<<< orphan*/ *) ; 
 TYPE_1__* vsp1_routes ; 

int vsp1_entity_init(struct vsp1_device *vsp1, struct vsp1_entity *entity,
		     const char *name, unsigned int num_pads,
		     const struct v4l2_subdev_ops *ops, u32 function)
{
	struct v4l2_subdev *subdev;
	unsigned int i;
	int ret;

	for (i = 0; i < ARRAY_SIZE(vsp1_routes); ++i) {
		if (vsp1_routes[i].type == entity->type &&
		    vsp1_routes[i].index == entity->index) {
			entity->route = &vsp1_routes[i];
			break;
		}
	}

	if (i == ARRAY_SIZE(vsp1_routes))
		return -EINVAL;

	mutex_init(&entity->lock);

	entity->vsp1 = vsp1;
	entity->source_pad = num_pads - 1;

	/* Allocate and initialize pads. */
	entity->pads = devm_kcalloc(vsp1->dev,
				    num_pads, sizeof(*entity->pads),
				    GFP_KERNEL);
	if (entity->pads == NULL)
		return -ENOMEM;

	for (i = 0; i < num_pads - 1; ++i)
		entity->pads[i].flags = MEDIA_PAD_FL_SINK;

	entity->sources = devm_kcalloc(vsp1->dev, max(num_pads - 1, 1U),
				       sizeof(*entity->sources), GFP_KERNEL);
	if (entity->sources == NULL)
		return -ENOMEM;

	/* Single-pad entities only have a sink. */
	entity->pads[num_pads - 1].flags = num_pads > 1 ? MEDIA_PAD_FL_SOURCE
					 : MEDIA_PAD_FL_SINK;

	/* Initialize the media entity. */
	ret = media_entity_pads_init(&entity->subdev.entity, num_pads,
				     entity->pads);
	if (ret < 0)
		return ret;

	/* Initialize the V4L2 subdev. */
	subdev = &entity->subdev;
	v4l2_subdev_init(subdev, ops);

	subdev->entity.function = function;
	subdev->entity.ops = &vsp1->media_ops;
	subdev->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;

	snprintf(subdev->name, sizeof(subdev->name), "%s %s",
		 dev_name(vsp1->dev), name);

	vsp1_entity_init_cfg(subdev, NULL);

	/*
	 * Allocate the pad configuration to store formats and selection
	 * rectangles.
	 */
	entity->config = v4l2_subdev_alloc_pad_config(&entity->subdev);
	if (entity->config == NULL) {
		media_entity_cleanup(&entity->subdev.entity);
		return -ENOMEM;
	}

	return 0;
}