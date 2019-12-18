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
struct v4l2_subdev_pad_config {int dummy; } ;
struct TYPE_2__ {int width; int height; int /*<<< orphan*/  field; int /*<<< orphan*/  code; } ;
struct v4l2_subdev_format {scalar_t__ pad; int /*<<< orphan*/  which; TYPE_1__ format; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_rect {int width; int height; scalar_t__ top; scalar_t__ left; } ;
struct smiapp_subdev {scalar_t__ source_pad; size_t sink_pad; struct v4l2_rect sink_fmt; } ;
struct smiapp_sensor {int /*<<< orphan*/  mutex; int /*<<< orphan*/ * limits; } ;

/* Variables and functions */
 size_t SMIAPP_LIMIT_MAX_X_OUTPUT_SIZE ; 
 size_t SMIAPP_LIMIT_MAX_Y_OUTPUT_SIZE ; 
 size_t SMIAPP_LIMIT_MIN_X_OUTPUT_SIZE ; 
 size_t SMIAPP_LIMIT_MIN_Y_OUTPUT_SIZE ; 
 int SMIAPP_PADS ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  V4L2_SEL_TGT_CROP ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int /*<<< orphan*/  __smiapp_get_mbus_code (struct v4l2_subdev*,scalar_t__) ; 
 void* clamp (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smiapp_get_crop_compose (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,struct v4l2_rect**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smiapp_propagate (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int smiapp_set_format_source (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,struct v4l2_subdev_format*) ; 
 struct smiapp_sensor* to_smiapp_sensor (struct v4l2_subdev*) ; 
 struct smiapp_subdev* to_smiapp_subdev (struct v4l2_subdev*) ; 

__attribute__((used)) static int smiapp_set_format(struct v4l2_subdev *subdev,
			     struct v4l2_subdev_pad_config *cfg,
			     struct v4l2_subdev_format *fmt)
{
	struct smiapp_sensor *sensor = to_smiapp_sensor(subdev);
	struct smiapp_subdev *ssd = to_smiapp_subdev(subdev);
	struct v4l2_rect *crops[SMIAPP_PADS];

	mutex_lock(&sensor->mutex);

	if (fmt->pad == ssd->source_pad) {
		int rval;

		rval = smiapp_set_format_source(subdev, cfg, fmt);

		mutex_unlock(&sensor->mutex);

		return rval;
	}

	/* Sink pad. Width and height are changeable here. */
	fmt->format.code = __smiapp_get_mbus_code(subdev, fmt->pad);
	fmt->format.width &= ~1;
	fmt->format.height &= ~1;
	fmt->format.field = V4L2_FIELD_NONE;

	fmt->format.width =
		clamp(fmt->format.width,
		      sensor->limits[SMIAPP_LIMIT_MIN_X_OUTPUT_SIZE],
		      sensor->limits[SMIAPP_LIMIT_MAX_X_OUTPUT_SIZE]);
	fmt->format.height =
		clamp(fmt->format.height,
		      sensor->limits[SMIAPP_LIMIT_MIN_Y_OUTPUT_SIZE],
		      sensor->limits[SMIAPP_LIMIT_MAX_Y_OUTPUT_SIZE]);

	smiapp_get_crop_compose(subdev, cfg, crops, NULL, fmt->which);

	crops[ssd->sink_pad]->left = 0;
	crops[ssd->sink_pad]->top = 0;
	crops[ssd->sink_pad]->width = fmt->format.width;
	crops[ssd->sink_pad]->height = fmt->format.height;
	if (fmt->which == V4L2_SUBDEV_FORMAT_ACTIVE)
		ssd->sink_fmt = *crops[ssd->sink_pad];
	smiapp_propagate(subdev, cfg, fmt->which,
			 V4L2_SEL_TGT_CROP);

	mutex_unlock(&sensor->mutex);

	return 0;
}