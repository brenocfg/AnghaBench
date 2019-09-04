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
struct v4l2_subdev_fh {int /*<<< orphan*/  pad; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {int width; int height; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; int /*<<< orphan*/  code; } ;
struct TYPE_2__ {int /*<<< orphan*/  mbus_code; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIO2_PAD_SINK ; 
 int /*<<< orphan*/  CIO2_PAD_SOURCE ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_RAW ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  V4L2_QUANTIZATION_DEFAULT ; 
 int /*<<< orphan*/  V4L2_XFER_FUNC_DEFAULT ; 
 int /*<<< orphan*/  V4L2_YCBCR_ENC_DEFAULT ; 
 TYPE_1__* formats ; 
 struct v4l2_mbus_framefmt* v4l2_subdev_get_try_format (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cio2_subdev_open(struct v4l2_subdev *sd, struct v4l2_subdev_fh *fh)
{
	struct v4l2_mbus_framefmt *format;
	const struct v4l2_mbus_framefmt fmt_default = {
		.width = 1936,
		.height = 1096,
		.code = formats[0].mbus_code,
		.field = V4L2_FIELD_NONE,
		.colorspace = V4L2_COLORSPACE_RAW,
		.ycbcr_enc = V4L2_YCBCR_ENC_DEFAULT,
		.quantization = V4L2_QUANTIZATION_DEFAULT,
		.xfer_func = V4L2_XFER_FUNC_DEFAULT,
	};

	/* Initialize try_fmt */
	format = v4l2_subdev_get_try_format(sd, fh->pad, CIO2_PAD_SINK);
	*format = fmt_default;

	/* same as sink */
	format = v4l2_subdev_get_try_format(sd, fh->pad, CIO2_PAD_SOURCE);
	*format = fmt_default;

	return 0;
}