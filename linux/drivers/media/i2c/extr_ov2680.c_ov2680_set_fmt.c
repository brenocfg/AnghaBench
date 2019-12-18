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
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  colorspace; int /*<<< orphan*/  code; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct v4l2_subdev_format {scalar_t__ pad; scalar_t__ which; struct v4l2_mbus_framefmt format; } ;
struct v4l2_subdev {int dummy; } ;
struct ov2680_mode_info {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct ov2680_dev {int mode_pending_changes; int /*<<< orphan*/  lock; struct v4l2_mbus_framefmt fmt; struct ov2680_mode_info const* current_mode; scalar_t__ is_streaming; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ V4L2_SUBDEV_FORMAT_TRY ; 
 int /*<<< orphan*/  height ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ov2680_mode_data ; 
 struct ov2680_dev* to_ov2680_dev (struct v4l2_subdev*) ; 
 struct ov2680_mode_info* v4l2_find_nearest_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct v4l2_mbus_framefmt* v4l2_subdev_get_try_format (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  width ; 

__attribute__((used)) static int ov2680_set_fmt(struct v4l2_subdev *sd,
			  struct v4l2_subdev_pad_config *cfg,
			  struct v4l2_subdev_format *format)
{
	struct ov2680_dev *sensor = to_ov2680_dev(sd);
	struct v4l2_mbus_framefmt *fmt = &format->format;
#ifdef CONFIG_VIDEO_V4L2_SUBDEV_API
	struct v4l2_mbus_framefmt *try_fmt;
#endif
	const struct ov2680_mode_info *mode;
	int ret = 0;

	if (format->pad != 0)
		return -EINVAL;

	mutex_lock(&sensor->lock);

	if (sensor->is_streaming) {
		ret = -EBUSY;
		goto unlock;
	}

	mode = v4l2_find_nearest_size(ov2680_mode_data,
				      ARRAY_SIZE(ov2680_mode_data), width,
				      height, fmt->width, fmt->height);
	if (!mode) {
		ret = -EINVAL;
		goto unlock;
	}

	if (format->which == V4L2_SUBDEV_FORMAT_TRY) {
#ifdef CONFIG_VIDEO_V4L2_SUBDEV_API
		try_fmt = v4l2_subdev_get_try_format(sd, cfg, 0);
		format->format = *try_fmt;
#endif
		goto unlock;
	}

	fmt->width = mode->width;
	fmt->height = mode->height;
	fmt->code = sensor->fmt.code;
	fmt->colorspace = sensor->fmt.colorspace;

	sensor->current_mode = mode;
	sensor->fmt = format->format;
	sensor->mode_pending_changes = true;

unlock:
	mutex_unlock(&sensor->lock);

	return ret;
}