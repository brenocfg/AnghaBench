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
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  field; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  code; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_2__ {int /*<<< orphan*/  colorspace; int /*<<< orphan*/  code; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT9M111_MAX_HEIGHT ; 
 int /*<<< orphan*/  MT9M111_MAX_WIDTH ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  V4L2_QUANTIZATION_DEFAULT ; 
 int /*<<< orphan*/  V4L2_XFER_FUNC_DEFAULT ; 
 int /*<<< orphan*/  V4L2_YCBCR_ENC_DEFAULT ; 
 TYPE_1__* mt9m111_colour_fmts ; 
 struct v4l2_mbus_framefmt* v4l2_subdev_get_try_format (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt9m111_init_cfg(struct v4l2_subdev *sd,
			    struct v4l2_subdev_pad_config *cfg)
{
#ifdef CONFIG_VIDEO_V4L2_SUBDEV_API
	struct v4l2_mbus_framefmt *format =
		v4l2_subdev_get_try_format(sd, cfg, 0);

	format->width	= MT9M111_MAX_WIDTH;
	format->height	= MT9M111_MAX_HEIGHT;
	format->code	= mt9m111_colour_fmts[0].code;
	format->colorspace	= mt9m111_colour_fmts[0].colorspace;
	format->field	= V4L2_FIELD_NONE;
	format->ycbcr_enc	= V4L2_YCBCR_ENC_DEFAULT;
	format->quantization	= V4L2_QUANTIZATION_DEFAULT;
	format->xfer_func	= V4L2_XFER_FUNC_DEFAULT;
#endif
	return 0;
}