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
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  field; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  code; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct ov2640_win_size {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEDIA_BUS_FMT_UYVY8_2X8 ; 
 int /*<<< orphan*/  SVGA_HEIGHT ; 
 int /*<<< orphan*/  SVGA_WIDTH ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SRGB ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  V4L2_QUANTIZATION_DEFAULT ; 
 int /*<<< orphan*/  V4L2_XFER_FUNC_DEFAULT ; 
 int /*<<< orphan*/  V4L2_YCBCR_ENC_DEFAULT ; 
 struct ov2640_win_size* ov2640_select_win (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct v4l2_mbus_framefmt* v4l2_subdev_get_try_format (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ov2640_init_cfg(struct v4l2_subdev *sd,
			   struct v4l2_subdev_pad_config *cfg)
{
#ifdef CONFIG_VIDEO_V4L2_SUBDEV_API
	struct v4l2_mbus_framefmt *try_fmt =
		v4l2_subdev_get_try_format(sd, cfg, 0);
	const struct ov2640_win_size *win =
		ov2640_select_win(SVGA_WIDTH, SVGA_HEIGHT);

	try_fmt->width = win->width;
	try_fmt->height = win->height;
	try_fmt->code = MEDIA_BUS_FMT_UYVY8_2X8;
	try_fmt->colorspace = V4L2_COLORSPACE_SRGB;
	try_fmt->field = V4L2_FIELD_NONE;
	try_fmt->ycbcr_enc = V4L2_YCBCR_ENC_DEFAULT;
	try_fmt->quantization = V4L2_QUANTIZATION_DEFAULT;
	try_fmt->xfer_func = V4L2_XFER_FUNC_DEFAULT;
#endif
	return 0;
}