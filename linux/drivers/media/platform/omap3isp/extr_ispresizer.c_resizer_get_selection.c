#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* height; void* width; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct v4l2_subdev_selection {scalar_t__ pad; int target; TYPE_1__ r; int /*<<< orphan*/  which; } ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {int dummy; } ;
struct resizer_ratio {int dummy; } ;
struct isp_res_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 void* INT_MAX ; 
 scalar_t__ RESZ_PAD_SINK ; 
 scalar_t__ RESZ_PAD_SOURCE ; 
#define  V4L2_SEL_TGT_CROP 129 
#define  V4L2_SEL_TGT_CROP_BOUNDS 128 
 TYPE_1__* __resizer_get_crop (struct isp_res_device*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ) ; 
 struct v4l2_mbus_framefmt* __resizer_get_format (struct isp_res_device*,struct v4l2_subdev_pad_config*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resizer_calc_ratios (struct isp_res_device*,TYPE_1__*,struct v4l2_mbus_framefmt*,struct resizer_ratio*) ; 
 int /*<<< orphan*/  resizer_try_crop (struct v4l2_mbus_framefmt*,struct v4l2_mbus_framefmt*,TYPE_1__*) ; 
 struct isp_res_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int resizer_get_selection(struct v4l2_subdev *sd,
				 struct v4l2_subdev_pad_config *cfg,
				 struct v4l2_subdev_selection *sel)
{
	struct isp_res_device *res = v4l2_get_subdevdata(sd);
	struct v4l2_mbus_framefmt *format_source;
	struct v4l2_mbus_framefmt *format_sink;
	struct resizer_ratio ratio;

	if (sel->pad != RESZ_PAD_SINK)
		return -EINVAL;

	format_sink = __resizer_get_format(res, cfg, RESZ_PAD_SINK,
					   sel->which);
	format_source = __resizer_get_format(res, cfg, RESZ_PAD_SOURCE,
					     sel->which);

	switch (sel->target) {
	case V4L2_SEL_TGT_CROP_BOUNDS:
		sel->r.left = 0;
		sel->r.top = 0;
		sel->r.width = INT_MAX;
		sel->r.height = INT_MAX;

		resizer_try_crop(format_sink, format_source, &sel->r);
		resizer_calc_ratios(res, &sel->r, format_source, &ratio);
		break;

	case V4L2_SEL_TGT_CROP:
		sel->r = *__resizer_get_crop(res, cfg, sel->which);
		resizer_calc_ratios(res, &sel->r, format_source, &ratio);
		break;

	default:
		return -EINVAL;
	}

	return 0;
}