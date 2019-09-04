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
struct v4l2_mbus_framefmt {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct v4l2_subdev_format {int /*<<< orphan*/  which; struct v4l2_mbus_framefmt format; int /*<<< orphan*/  pad; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_rect {int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ top; scalar_t__ left; } ;
struct TYPE_2__ {int /*<<< orphan*/  active; int /*<<< orphan*/  request; } ;
struct isp_res_device {int /*<<< orphan*/  ratio; TYPE_1__ crop; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RESZ_PAD_SINK ; 
 int /*<<< orphan*/  RESZ_PAD_SOURCE ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 struct v4l2_rect* __resizer_get_crop (struct isp_res_device*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ) ; 
 struct v4l2_mbus_framefmt* __resizer_get_format (struct isp_res_device*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resizer_calc_ratios (struct isp_res_device*,int /*<<< orphan*/ *,struct v4l2_mbus_framefmt*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resizer_try_format (struct isp_res_device*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ,struct v4l2_mbus_framefmt*,int /*<<< orphan*/ ) ; 
 struct isp_res_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int resizer_set_format(struct v4l2_subdev *sd, struct v4l2_subdev_pad_config *cfg,
			      struct v4l2_subdev_format *fmt)
{
	struct isp_res_device *res = v4l2_get_subdevdata(sd);
	struct v4l2_mbus_framefmt *format;
	struct v4l2_rect *crop;

	format = __resizer_get_format(res, cfg, fmt->pad, fmt->which);
	if (format == NULL)
		return -EINVAL;

	resizer_try_format(res, cfg, fmt->pad, &fmt->format, fmt->which);
	*format = fmt->format;

	if (fmt->pad == RESZ_PAD_SINK) {
		/* reset crop rectangle */
		crop = __resizer_get_crop(res, cfg, fmt->which);
		crop->left = 0;
		crop->top = 0;
		crop->width = fmt->format.width;
		crop->height = fmt->format.height;

		/* Propagate the format from sink to source */
		format = __resizer_get_format(res, cfg, RESZ_PAD_SOURCE,
					      fmt->which);
		*format = fmt->format;
		resizer_try_format(res, cfg, RESZ_PAD_SOURCE, format,
				   fmt->which);
	}

	if (fmt->which == V4L2_SUBDEV_FORMAT_ACTIVE) {
		/* Compute and store the active crop rectangle and resizer
		 * ratios. format already points to the source pad active
		 * format.
		 */
		res->crop.active = res->crop.request;
		resizer_calc_ratios(res, &res->crop.active, format,
				       &res->ratio);
	}

	return 0;
}