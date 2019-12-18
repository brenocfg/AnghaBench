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
struct v4l2_subdev_frame_size_enum {scalar_t__ code; scalar_t__ pad; int min_width; int max_width; int min_height; int max_height; scalar_t__ index; int /*<<< orphan*/  which; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {scalar_t__ code; int width; int height; } ;

/* Variables and functions */
 int EINVAL ; 
 int SRU_MAX_SIZE ; 
 void* SRU_MIN_SIZE ; 
 scalar_t__ SRU_PAD_SINK ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct vsp1_sru* to_sru (struct v4l2_subdev*) ; 
 struct v4l2_subdev_pad_config* vsp1_entity_get_pad_config (TYPE_1__*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ) ; 
 struct v4l2_mbus_framefmt* vsp1_entity_get_pad_format (TYPE_1__*,struct v4l2_subdev_pad_config*,scalar_t__) ; 

__attribute__((used)) static int sru_enum_frame_size(struct v4l2_subdev *subdev,
			       struct v4l2_subdev_pad_config *cfg,
			       struct v4l2_subdev_frame_size_enum *fse)
{
	struct vsp1_sru *sru = to_sru(subdev);
	struct v4l2_subdev_pad_config *config;
	struct v4l2_mbus_framefmt *format;
	int ret = 0;

	config = vsp1_entity_get_pad_config(&sru->entity, cfg, fse->which);
	if (!config)
		return -EINVAL;

	format = vsp1_entity_get_pad_format(&sru->entity, config, SRU_PAD_SINK);

	mutex_lock(&sru->entity.lock);

	if (fse->index || fse->code != format->code) {
		ret = -EINVAL;
		goto done;
	}

	if (fse->pad == SRU_PAD_SINK) {
		fse->min_width = SRU_MIN_SIZE;
		fse->max_width = SRU_MAX_SIZE;
		fse->min_height = SRU_MIN_SIZE;
		fse->max_height = SRU_MAX_SIZE;
	} else {
		fse->min_width = format->width;
		fse->min_height = format->height;
		if (format->width <= SRU_MAX_SIZE / 2 &&
		    format->height <= SRU_MAX_SIZE / 2) {
			fse->max_width = format->width * 2;
			fse->max_height = format->height * 2;
		} else {
			fse->max_width = format->width;
			fse->max_height = format->height;
		}
	}

done:
	mutex_unlock(&sru->entity.lock);
	return ret;
}