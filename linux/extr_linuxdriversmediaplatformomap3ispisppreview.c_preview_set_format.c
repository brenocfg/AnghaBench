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
struct v4l2_mbus_framefmt {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct v4l2_subdev_format {int /*<<< orphan*/  which; struct v4l2_mbus_framefmt format; int /*<<< orphan*/  pad; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_rect {int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ top; scalar_t__ left; } ;
struct isp_prev_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PREV_PAD_SINK ; 
 int /*<<< orphan*/  PREV_PAD_SOURCE ; 
 struct v4l2_rect* __preview_get_crop (struct isp_prev_device*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ) ; 
 struct v4l2_mbus_framefmt* __preview_get_format (struct isp_prev_device*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  preview_try_crop (struct isp_prev_device*,struct v4l2_mbus_framefmt*,struct v4l2_rect*) ; 
 int /*<<< orphan*/  preview_try_format (struct isp_prev_device*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ,struct v4l2_mbus_framefmt*,int /*<<< orphan*/ ) ; 
 struct isp_prev_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int preview_set_format(struct v4l2_subdev *sd, struct v4l2_subdev_pad_config *cfg,
			      struct v4l2_subdev_format *fmt)
{
	struct isp_prev_device *prev = v4l2_get_subdevdata(sd);
	struct v4l2_mbus_framefmt *format;
	struct v4l2_rect *crop;

	format = __preview_get_format(prev, cfg, fmt->pad, fmt->which);
	if (format == NULL)
		return -EINVAL;

	preview_try_format(prev, cfg, fmt->pad, &fmt->format, fmt->which);
	*format = fmt->format;

	/* Propagate the format from sink to source */
	if (fmt->pad == PREV_PAD_SINK) {
		/* Reset the crop rectangle. */
		crop = __preview_get_crop(prev, cfg, fmt->which);
		crop->left = 0;
		crop->top = 0;
		crop->width = fmt->format.width;
		crop->height = fmt->format.height;

		preview_try_crop(prev, &fmt->format, crop);

		/* Update the source format. */
		format = __preview_get_format(prev, cfg, PREV_PAD_SOURCE,
					      fmt->which);
		preview_try_format(prev, cfg, PREV_PAD_SOURCE, format,
				   fmt->which);
	}

	return 0;
}