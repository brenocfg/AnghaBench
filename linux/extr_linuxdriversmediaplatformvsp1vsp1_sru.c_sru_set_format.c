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
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct vsp1_sru {TYPE_1__ entity; } ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_mbus_framefmt {int dummy; } ;
struct v4l2_subdev_format {struct v4l2_mbus_framefmt format; int /*<<< orphan*/  pad; int /*<<< orphan*/  which; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SRU_PAD_SINK ; 
 int /*<<< orphan*/  SRU_PAD_SOURCE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sru_try_format (struct vsp1_sru*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ,struct v4l2_mbus_framefmt*) ; 
 struct vsp1_sru* to_sru (struct v4l2_subdev*) ; 
 struct v4l2_subdev_pad_config* vsp1_entity_get_pad_config (TYPE_1__*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ) ; 
 struct v4l2_mbus_framefmt* vsp1_entity_get_pad_format (TYPE_1__*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sru_set_format(struct v4l2_subdev *subdev,
			  struct v4l2_subdev_pad_config *cfg,
			  struct v4l2_subdev_format *fmt)
{
	struct vsp1_sru *sru = to_sru(subdev);
	struct v4l2_subdev_pad_config *config;
	struct v4l2_mbus_framefmt *format;
	int ret = 0;

	mutex_lock(&sru->entity.lock);

	config = vsp1_entity_get_pad_config(&sru->entity, cfg, fmt->which);
	if (!config) {
		ret = -EINVAL;
		goto done;
	}

	sru_try_format(sru, config, fmt->pad, &fmt->format);

	format = vsp1_entity_get_pad_format(&sru->entity, config, fmt->pad);
	*format = fmt->format;

	if (fmt->pad == SRU_PAD_SINK) {
		/* Propagate the format to the source pad. */
		format = vsp1_entity_get_pad_format(&sru->entity, config,
						    SRU_PAD_SOURCE);
		*format = fmt->format;

		sru_try_format(sru, config, SRU_PAD_SOURCE, format);
	}

done:
	mutex_unlock(&sru->entity.lock);
	return ret;
}