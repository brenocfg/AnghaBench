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
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {scalar_t__ code; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct ov5640_mode_info {int /*<<< orphan*/  vact; int /*<<< orphan*/  hact; } ;
struct ov5640_dev {int dummy; } ;
typedef  enum ov5640_frame_rate { ____Placeholder_ov5640_frame_rate } ov5640_frame_rate ;
struct TYPE_3__ {scalar_t__ code; int /*<<< orphan*/  colorspace; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_MAP_XFER_FUNC_DEFAULT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V4L2_MAP_YCBCR_ENC_DEFAULT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V4L2_QUANTIZATION_FULL_RANGE ; 
 struct ov5640_mode_info* ov5640_find_mode (struct ov5640_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* ov5640_formats ; 
 struct ov5640_dev* to_ov5640_dev (struct v4l2_subdev*) ; 

__attribute__((used)) static int ov5640_try_fmt_internal(struct v4l2_subdev *sd,
				   struct v4l2_mbus_framefmt *fmt,
				   enum ov5640_frame_rate fr,
				   const struct ov5640_mode_info **new_mode)
{
	struct ov5640_dev *sensor = to_ov5640_dev(sd);
	const struct ov5640_mode_info *mode;
	int i;

	mode = ov5640_find_mode(sensor, fr, fmt->width, fmt->height, true);
	if (!mode)
		return -EINVAL;
	fmt->width = mode->hact;
	fmt->height = mode->vact;

	if (new_mode)
		*new_mode = mode;

	for (i = 0; i < ARRAY_SIZE(ov5640_formats); i++)
		if (ov5640_formats[i].code == fmt->code)
			break;
	if (i >= ARRAY_SIZE(ov5640_formats))
		i = 0;

	fmt->code = ov5640_formats[i].code;
	fmt->colorspace = ov5640_formats[i].colorspace;
	fmt->ycbcr_enc = V4L2_MAP_YCBCR_ENC_DEFAULT(fmt->colorspace);
	fmt->quantization = V4L2_QUANTIZATION_FULL_RANGE;
	fmt->xfer_func = V4L2_MAP_XFER_FUNC_DEFAULT(fmt->colorspace);

	return 0;
}