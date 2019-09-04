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
struct v4l2_mbus_framefmt {scalar_t__ code; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct v4l2_subdev_pad_config {struct v4l2_mbus_framefmt try_fmt; } ;
struct v4l2_subdev_format {scalar_t__ which; scalar_t__ pad; struct v4l2_mbus_framefmt format; } ;
struct v4l2_subdev {int dummy; } ;
struct mt9v022_datafmt {scalar_t__ code; int /*<<< orphan*/  colorspace; } ;
struct mt9v022 {struct mt9v022_datafmt* fmt; int /*<<< orphan*/  num_fmts; int /*<<< orphan*/  fmts; scalar_t__ y_skip_top; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MEDIA_BUS_FMT_SBGGR10_1X10 ; 
 scalar_t__ MEDIA_BUS_FMT_SBGGR8_1X8 ; 
 scalar_t__ MT9V022_MAX_HEIGHT ; 
 int /*<<< orphan*/  MT9V022_MAX_WIDTH ; 
 scalar_t__ MT9V022_MIN_HEIGHT ; 
 int /*<<< orphan*/  MT9V022_MIN_WIDTH ; 
 scalar_t__ V4L2_SUBDEV_FORMAT_ACTIVE ; 
 struct mt9v022_datafmt* mt9v022_find_datafmt (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mt9v022_s_fmt (struct v4l2_subdev*,struct mt9v022_datafmt const*,struct v4l2_mbus_framefmt*) ; 
 struct mt9v022* to_mt9v022 (struct i2c_client*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l_bound_align_image (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt9v022_set_fmt(struct v4l2_subdev *sd,
		struct v4l2_subdev_pad_config *cfg,
		struct v4l2_subdev_format *format)
{
	struct v4l2_mbus_framefmt *mf = &format->format;
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct mt9v022 *mt9v022 = to_mt9v022(client);
	const struct mt9v022_datafmt *fmt;
	int align = mf->code == MEDIA_BUS_FMT_SBGGR8_1X8 ||
		mf->code == MEDIA_BUS_FMT_SBGGR10_1X10;

	if (format->pad)
		return -EINVAL;

	v4l_bound_align_image(&mf->width, MT9V022_MIN_WIDTH,
		MT9V022_MAX_WIDTH, align,
		&mf->height, MT9V022_MIN_HEIGHT + mt9v022->y_skip_top,
		MT9V022_MAX_HEIGHT + mt9v022->y_skip_top, align, 0);

	fmt = mt9v022_find_datafmt(mf->code, mt9v022->fmts,
				   mt9v022->num_fmts);
	if (!fmt) {
		fmt = mt9v022->fmt;
		mf->code = fmt->code;
	}

	mf->colorspace	= fmt->colorspace;

	if (format->which == V4L2_SUBDEV_FORMAT_ACTIVE)
		return mt9v022_s_fmt(sd, fmt, mf);
	cfg->try_fmt = *mf;
	return 0;
}