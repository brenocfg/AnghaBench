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
struct TYPE_3__ {scalar_t__ source_pad; int /*<<< orphan*/  lock; } ;
struct vsp1_brx {TYPE_1__ entity; } ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  code; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct v4l2_subdev_format {unsigned int pad; struct v4l2_mbus_framefmt format; int /*<<< orphan*/  which; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_rect {int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ top; scalar_t__ left; } ;

/* Variables and functions */
 scalar_t__ BRX_PAD_SINK (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 struct v4l2_rect* brx_get_compose (struct vsp1_brx*,struct v4l2_subdev_pad_config*,scalar_t__) ; 
 int /*<<< orphan*/  brx_try_format (struct vsp1_brx*,struct v4l2_subdev_pad_config*,unsigned int,struct v4l2_mbus_framefmt*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct vsp1_brx* to_brx (struct v4l2_subdev*) ; 
 struct v4l2_subdev_pad_config* vsp1_entity_get_pad_config (TYPE_1__*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ) ; 
 struct v4l2_mbus_framefmt* vsp1_entity_get_pad_format (TYPE_1__*,struct v4l2_subdev_pad_config*,unsigned int) ; 

__attribute__((used)) static int brx_set_format(struct v4l2_subdev *subdev,
			  struct v4l2_subdev_pad_config *cfg,
			  struct v4l2_subdev_format *fmt)
{
	struct vsp1_brx *brx = to_brx(subdev);
	struct v4l2_subdev_pad_config *config;
	struct v4l2_mbus_framefmt *format;
	int ret = 0;

	mutex_lock(&brx->entity.lock);

	config = vsp1_entity_get_pad_config(&brx->entity, cfg, fmt->which);
	if (!config) {
		ret = -EINVAL;
		goto done;
	}

	brx_try_format(brx, config, fmt->pad, &fmt->format);

	format = vsp1_entity_get_pad_format(&brx->entity, config, fmt->pad);
	*format = fmt->format;

	/* Reset the compose rectangle. */
	if (fmt->pad != brx->entity.source_pad) {
		struct v4l2_rect *compose;

		compose = brx_get_compose(brx, config, fmt->pad);
		compose->left = 0;
		compose->top = 0;
		compose->width = format->width;
		compose->height = format->height;
	}

	/* Propagate the format code to all pads. */
	if (fmt->pad == BRX_PAD_SINK(0)) {
		unsigned int i;

		for (i = 0; i <= brx->entity.source_pad; ++i) {
			format = vsp1_entity_get_pad_format(&brx->entity,
							    config, i);
			format->code = fmt->format.code;
		}
	}

done:
	mutex_unlock(&brx->entity.lock);
	return ret;
}