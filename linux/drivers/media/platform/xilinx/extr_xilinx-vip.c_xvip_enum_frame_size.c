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
struct v4l2_subdev_frame_size_enum {scalar_t__ which; scalar_t__ pad; scalar_t__ code; int /*<<< orphan*/  max_height; int /*<<< orphan*/  min_height; int /*<<< orphan*/  max_width; int /*<<< orphan*/  min_width; scalar_t__ index; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {scalar_t__ code; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int /*<<< orphan*/  XVIP_MAX_HEIGHT ; 
 int /*<<< orphan*/  XVIP_MAX_WIDTH ; 
 int /*<<< orphan*/  XVIP_MIN_HEIGHT ; 
 int /*<<< orphan*/  XVIP_MIN_WIDTH ; 
 scalar_t__ XVIP_PAD_SINK ; 
 struct v4l2_mbus_framefmt* v4l2_subdev_get_try_format (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,scalar_t__) ; 

int xvip_enum_frame_size(struct v4l2_subdev *subdev,
			 struct v4l2_subdev_pad_config *cfg,
			 struct v4l2_subdev_frame_size_enum *fse)
{
	struct v4l2_mbus_framefmt *format;

	/* Enumerating frame sizes based on the active configuration isn't
	 * supported yet.
	 */
	if (fse->which == V4L2_SUBDEV_FORMAT_ACTIVE)
		return -EINVAL;

	format = v4l2_subdev_get_try_format(subdev, cfg, fse->pad);

	if (fse->index || fse->code != format->code)
		return -EINVAL;

	if (fse->pad == XVIP_PAD_SINK) {
		fse->min_width = XVIP_MIN_WIDTH;
		fse->max_width = XVIP_MAX_WIDTH;
		fse->min_height = XVIP_MIN_HEIGHT;
		fse->max_height = XVIP_MAX_HEIGHT;
	} else {
		/* The size on the source pad is fixed and always identical to
		 * the size on the sink pad.
		 */
		fse->min_width = format->width;
		fse->max_width = format->width;
		fse->min_height = format->height;
		fse->max_height = format->height;
	}

	return 0;
}