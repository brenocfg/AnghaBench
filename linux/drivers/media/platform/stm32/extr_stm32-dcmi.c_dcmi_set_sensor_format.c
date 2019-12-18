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
struct v4l2_subdev_format {int /*<<< orphan*/  format; int /*<<< orphan*/  which; } ;
struct v4l2_pix_format {int /*<<< orphan*/  pixelformat; } ;
struct TYPE_2__ {int /*<<< orphan*/  source; } ;
struct stm32_dcmi {int num_of_sd_formats; TYPE_1__ entity; struct dcmi_format** sd_formats; } ;
struct dcmi_format {int /*<<< orphan*/  mbus_code; int /*<<< orphan*/  fourcc; } ;

/* Variables and functions */
 int ENODATA ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_TRY ; 
 struct dcmi_format* find_format_by_fourcc (struct stm32_dcmi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pad ; 
 int /*<<< orphan*/  set_fmt ; 
 int /*<<< orphan*/  v4l2_fill_mbus_format (int /*<<< orphan*/ *,struct v4l2_pix_format*,int /*<<< orphan*/ ) ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_subdev_pad_config*,struct v4l2_subdev_format*) ; 

__attribute__((used)) static int dcmi_set_sensor_format(struct stm32_dcmi *dcmi,
				  struct v4l2_pix_format *pix)
{
	const struct dcmi_format *sd_fmt;
	struct v4l2_subdev_format format = {
		.which = V4L2_SUBDEV_FORMAT_TRY,
	};
	struct v4l2_subdev_pad_config pad_cfg;
	int ret;

	sd_fmt = find_format_by_fourcc(dcmi, pix->pixelformat);
	if (!sd_fmt) {
		if (!dcmi->num_of_sd_formats)
			return -ENODATA;

		sd_fmt = dcmi->sd_formats[dcmi->num_of_sd_formats - 1];
		pix->pixelformat = sd_fmt->fourcc;
	}

	v4l2_fill_mbus_format(&format.format, pix, sd_fmt->mbus_code);
	ret = v4l2_subdev_call(dcmi->entity.source, pad, set_fmt,
			       &pad_cfg, &format);
	if (ret < 0)
		return ret;

	return 0;
}