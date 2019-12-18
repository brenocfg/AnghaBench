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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  code; } ;
struct v4l2_subdev_format {scalar_t__ which; struct v4l2_mbus_framefmt format; int /*<<< orphan*/  pad; } ;
struct v4l2_subdev {int dummy; } ;
struct imx319_mode {scalar_t__ width; scalar_t__ llp; scalar_t__ fll_min; scalar_t__ fll_def; scalar_t__ height; } ;
struct imx319 {int link_def_freq; int /*<<< orphan*/  mutex; int /*<<< orphan*/  hblank; struct imx319_mode const* cur_mode; int /*<<< orphan*/  vblank; int /*<<< orphan*/  pixel_rate; } ;
typedef  scalar_t__ s64 ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ IMX319_FLL_MAX ; 
 scalar_t__ V4L2_SUBDEV_FORMAT_TRY ; 
 int /*<<< orphan*/  __v4l2_ctrl_modify_range (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,scalar_t__) ; 
 int /*<<< orphan*/  __v4l2_ctrl_s_ctrl (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  __v4l2_ctrl_s_ctrl_int64 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int /*<<< orphan*/  imx319_get_format_code (struct imx319*) ; 
 int /*<<< orphan*/  imx319_update_pad_format (struct imx319*,struct imx319_mode const*,struct v4l2_subdev_format*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  supported_modes ; 
 struct imx319* to_imx319 (struct v4l2_subdev*) ; 
 struct imx319_mode* v4l2_find_nearest_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct v4l2_mbus_framefmt* v4l2_subdev_get_try_format (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  width ; 

__attribute__((used)) static int
imx319_set_pad_format(struct v4l2_subdev *sd,
		      struct v4l2_subdev_pad_config *cfg,
		      struct v4l2_subdev_format *fmt)
{
	struct imx319 *imx319 = to_imx319(sd);
	const struct imx319_mode *mode;
	struct v4l2_mbus_framefmt *framefmt;
	s32 vblank_def;
	s32 vblank_min;
	s64 h_blank;
	u64 pixel_rate;
	u32 height;

	mutex_lock(&imx319->mutex);

	/*
	 * Only one bayer order is supported.
	 * It depends on the flip settings.
	 */
	fmt->format.code = imx319_get_format_code(imx319);

	mode = v4l2_find_nearest_size(supported_modes,
				      ARRAY_SIZE(supported_modes),
				      width, height,
				      fmt->format.width, fmt->format.height);
	imx319_update_pad_format(imx319, mode, fmt);
	if (fmt->which == V4L2_SUBDEV_FORMAT_TRY) {
		framefmt = v4l2_subdev_get_try_format(sd, cfg, fmt->pad);
		*framefmt = fmt->format;
	} else {
		imx319->cur_mode = mode;
		pixel_rate = imx319->link_def_freq * 2 * 4;
		do_div(pixel_rate, 10);
		__v4l2_ctrl_s_ctrl_int64(imx319->pixel_rate, pixel_rate);
		/* Update limits and set FPS to default */
		height = imx319->cur_mode->height;
		vblank_def = imx319->cur_mode->fll_def - height;
		vblank_min = imx319->cur_mode->fll_min - height;
		height = IMX319_FLL_MAX - height;
		__v4l2_ctrl_modify_range(imx319->vblank, vblank_min, height, 1,
					 vblank_def);
		__v4l2_ctrl_s_ctrl(imx319->vblank, vblank_def);
		h_blank = mode->llp - imx319->cur_mode->width;
		/*
		 * Currently hblank is not changeable.
		 * So FPS control is done only by vblank.
		 */
		__v4l2_ctrl_modify_range(imx319->hblank, h_blank,
					 h_blank, 1, h_blank);
	}

	mutex_unlock(&imx319->mutex);

	return 0;
}