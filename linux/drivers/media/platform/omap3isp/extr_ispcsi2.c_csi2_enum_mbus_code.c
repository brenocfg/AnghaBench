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
struct v4l2_subdev_mbus_code_enum {scalar_t__ pad; size_t index; int /*<<< orphan*/  code; int /*<<< orphan*/  which; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  code; } ;
struct isp_format_info {int /*<<< orphan*/  uncompressed; } ;
struct isp_csi2_device {int dummy; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ CSI2_PAD_SINK ; 
 int EINVAL ; 
 struct v4l2_mbus_framefmt* __csi2_get_format (struct isp_csi2_device*,struct v4l2_subdev_pad_config*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * csi2_input_fmts ; 
 struct isp_format_info* omap3isp_video_format_info (int /*<<< orphan*/ ) ; 
 struct isp_csi2_device* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int csi2_enum_mbus_code(struct v4l2_subdev *sd,
			       struct v4l2_subdev_pad_config *cfg,
			       struct v4l2_subdev_mbus_code_enum *code)
{
	struct isp_csi2_device *csi2 = v4l2_get_subdevdata(sd);
	struct v4l2_mbus_framefmt *format;
	const struct isp_format_info *info;

	if (code->pad == CSI2_PAD_SINK) {
		if (code->index >= ARRAY_SIZE(csi2_input_fmts))
			return -EINVAL;

		code->code = csi2_input_fmts[code->index];
	} else {
		format = __csi2_get_format(csi2, cfg, CSI2_PAD_SINK,
					   code->which);
		switch (code->index) {
		case 0:
			/* Passthrough sink pad code */
			code->code = format->code;
			break;
		case 1:
			/* Uncompressed code */
			info = omap3isp_video_format_info(format->code);
			if (info->uncompressed == format->code)
				return -EINVAL;

			code->code = info->uncompressed;
			break;
		default:
			return -EINVAL;
		}
	}

	return 0;
}