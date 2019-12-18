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
struct v4l2_rect {int dummy; } ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  field; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  code; void* height; void* width; } ;
struct resizer_ratio {int dummy; } ;
struct isp_res_device {int dummy; } ;
typedef  enum v4l2_subdev_format_whence { ____Placeholder_v4l2_subdev_format_whence } v4l2_subdev_format_whence ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_IN_HEIGHT ; 
 int /*<<< orphan*/  MEDIA_BUS_FMT_UYVY8_1X16 ; 
 int /*<<< orphan*/  MEDIA_BUS_FMT_YUYV8_1X16 ; 
 int /*<<< orphan*/  MIN_IN_HEIGHT ; 
 int /*<<< orphan*/  MIN_IN_WIDTH ; 
#define  RESZ_PAD_SINK 129 
#define  RESZ_PAD_SOURCE 128 
 int /*<<< orphan*/  V4L2_COLORSPACE_JPEG ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 struct v4l2_rect* __resizer_get_crop (struct isp_res_device*,struct v4l2_subdev_pad_config*,int) ; 
 struct v4l2_mbus_framefmt* __resizer_get_format (struct isp_res_device*,struct v4l2_subdev_pad_config*,int const,int) ; 
 void* clamp_t (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resizer_calc_ratios (struct isp_res_device*,struct v4l2_rect*,struct v4l2_mbus_framefmt*,struct resizer_ratio*) ; 
 int /*<<< orphan*/  resizer_max_in_width (struct isp_res_device*) ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static void resizer_try_format(struct isp_res_device *res,
			       struct v4l2_subdev_pad_config *cfg, unsigned int pad,
			       struct v4l2_mbus_framefmt *fmt,
			       enum v4l2_subdev_format_whence which)
{
	struct v4l2_mbus_framefmt *format;
	struct resizer_ratio ratio;
	struct v4l2_rect crop;

	switch (pad) {
	case RESZ_PAD_SINK:
		if (fmt->code != MEDIA_BUS_FMT_YUYV8_1X16 &&
		    fmt->code != MEDIA_BUS_FMT_UYVY8_1X16)
			fmt->code = MEDIA_BUS_FMT_YUYV8_1X16;

		fmt->width = clamp_t(u32, fmt->width, MIN_IN_WIDTH,
				     resizer_max_in_width(res));
		fmt->height = clamp_t(u32, fmt->height, MIN_IN_HEIGHT,
				      MAX_IN_HEIGHT);
		break;

	case RESZ_PAD_SOURCE:
		format = __resizer_get_format(res, cfg, RESZ_PAD_SINK, which);
		fmt->code = format->code;

		crop = *__resizer_get_crop(res, cfg, which);
		resizer_calc_ratios(res, &crop, fmt, &ratio);
		break;
	}

	fmt->colorspace = V4L2_COLORSPACE_JPEG;
	fmt->field = V4L2_FIELD_NONE;
}