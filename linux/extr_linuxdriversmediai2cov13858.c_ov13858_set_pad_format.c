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
struct v4l2_mbus_framefmt {scalar_t__ code; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct v4l2_subdev_format {scalar_t__ which; struct v4l2_mbus_framefmt format; int /*<<< orphan*/  pad; } ;
struct v4l2_subdev {int dummy; } ;
struct ov13858_mode {size_t link_freq_index; size_t vts_def; size_t height; size_t vts_min; size_t width; } ;
struct ov13858 {int /*<<< orphan*/  mutex; int /*<<< orphan*/  hblank; struct ov13858_mode const* cur_mode; int /*<<< orphan*/  vblank; int /*<<< orphan*/  pixel_rate; int /*<<< orphan*/  link_freq; } ;
typedef  size_t s64 ;
typedef  size_t s32 ;
struct TYPE_2__ {size_t pixels_per_line; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ MEDIA_BUS_FMT_SGRBG10_1X10 ; 
 size_t OV13858_VTS_MAX ; 
 scalar_t__ V4L2_SUBDEV_FORMAT_TRY ; 
 int /*<<< orphan*/  __v4l2_ctrl_modify_range (int /*<<< orphan*/ ,size_t,size_t,int,size_t) ; 
 int /*<<< orphan*/  __v4l2_ctrl_s_ctrl (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  __v4l2_ctrl_s_ctrl_int64 (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  height ; 
 TYPE_1__* link_freq_configs ; 
 size_t* link_freq_menu_items ; 
 size_t link_freq_to_pixel_rate (size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ov13858_update_pad_format (struct ov13858_mode const*,struct v4l2_subdev_format*) ; 
 int /*<<< orphan*/  supported_modes ; 
 struct ov13858* to_ov13858 (struct v4l2_subdev*) ; 
 struct ov13858_mode* v4l2_find_nearest_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct v4l2_mbus_framefmt* v4l2_subdev_get_try_format (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  width ; 

__attribute__((used)) static int
ov13858_set_pad_format(struct v4l2_subdev *sd,
		       struct v4l2_subdev_pad_config *cfg,
		       struct v4l2_subdev_format *fmt)
{
	struct ov13858 *ov13858 = to_ov13858(sd);
	const struct ov13858_mode *mode;
	struct v4l2_mbus_framefmt *framefmt;
	s32 vblank_def;
	s32 vblank_min;
	s64 h_blank;
	s64 pixel_rate;
	s64 link_freq;

	mutex_lock(&ov13858->mutex);

	/* Only one raw bayer(GRBG) order is supported */
	if (fmt->format.code != MEDIA_BUS_FMT_SGRBG10_1X10)
		fmt->format.code = MEDIA_BUS_FMT_SGRBG10_1X10;

	mode = v4l2_find_nearest_size(supported_modes,
				      ARRAY_SIZE(supported_modes),
				      width, height,
				      fmt->format.width, fmt->format.height);
	ov13858_update_pad_format(mode, fmt);
	if (fmt->which == V4L2_SUBDEV_FORMAT_TRY) {
		framefmt = v4l2_subdev_get_try_format(sd, cfg, fmt->pad);
		*framefmt = fmt->format;
	} else {
		ov13858->cur_mode = mode;
		__v4l2_ctrl_s_ctrl(ov13858->link_freq, mode->link_freq_index);
		link_freq = link_freq_menu_items[mode->link_freq_index];
		pixel_rate = link_freq_to_pixel_rate(link_freq);
		__v4l2_ctrl_s_ctrl_int64(ov13858->pixel_rate, pixel_rate);

		/* Update limits and set FPS to default */
		vblank_def = ov13858->cur_mode->vts_def -
			     ov13858->cur_mode->height;
		vblank_min = ov13858->cur_mode->vts_min -
			     ov13858->cur_mode->height;
		__v4l2_ctrl_modify_range(
			ov13858->vblank, vblank_min,
			OV13858_VTS_MAX - ov13858->cur_mode->height, 1,
			vblank_def);
		__v4l2_ctrl_s_ctrl(ov13858->vblank, vblank_def);
		h_blank =
			link_freq_configs[mode->link_freq_index].pixels_per_line
			 - ov13858->cur_mode->width;
		__v4l2_ctrl_modify_range(ov13858->hblank, h_blank,
					 h_blank, 1, h_blank);
	}

	mutex_unlock(&ov13858->mutex);

	return 0;
}