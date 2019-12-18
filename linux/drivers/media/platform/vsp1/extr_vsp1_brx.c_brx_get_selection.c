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
struct TYPE_3__ {scalar_t__ source_pad; int /*<<< orphan*/  lock; } ;
struct vsp1_brx {TYPE_1__ entity; } ;
struct TYPE_4__ {void* height; void* width; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct v4l2_subdev_selection {scalar_t__ pad; int target; TYPE_2__ r; int /*<<< orphan*/  which; } ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 void* BRX_MAX_SIZE ; 
 int EINVAL ; 
#define  V4L2_SEL_TGT_COMPOSE 129 
#define  V4L2_SEL_TGT_COMPOSE_BOUNDS 128 
 TYPE_2__* brx_get_compose (struct vsp1_brx*,struct v4l2_subdev_pad_config*,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct vsp1_brx* to_brx (struct v4l2_subdev*) ; 
 struct v4l2_subdev_pad_config* vsp1_entity_get_pad_config (TYPE_1__*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int brx_get_selection(struct v4l2_subdev *subdev,
			     struct v4l2_subdev_pad_config *cfg,
			     struct v4l2_subdev_selection *sel)
{
	struct vsp1_brx *brx = to_brx(subdev);
	struct v4l2_subdev_pad_config *config;

	if (sel->pad == brx->entity.source_pad)
		return -EINVAL;

	switch (sel->target) {
	case V4L2_SEL_TGT_COMPOSE_BOUNDS:
		sel->r.left = 0;
		sel->r.top = 0;
		sel->r.width = BRX_MAX_SIZE;
		sel->r.height = BRX_MAX_SIZE;
		return 0;

	case V4L2_SEL_TGT_COMPOSE:
		config = vsp1_entity_get_pad_config(&brx->entity, cfg,
						    sel->which);
		if (!config)
			return -EINVAL;

		mutex_lock(&brx->entity.lock);
		sel->r = *brx_get_compose(brx, config, sel->pad);
		mutex_unlock(&brx->entity.lock);
		return 0;

	default:
		return -EINVAL;
	}
}