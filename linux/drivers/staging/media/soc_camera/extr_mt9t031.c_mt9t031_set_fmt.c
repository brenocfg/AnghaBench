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
typedef  int /*<<< orphan*/  u16 ;
struct v4l2_mbus_framefmt {void* colorspace; void* code; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct v4l2_subdev_pad_config {struct v4l2_mbus_framefmt try_fmt; } ;
struct v4l2_subdev_format {scalar_t__ which; scalar_t__ pad; struct v4l2_mbus_framefmt format; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_rect {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct mt9t031 {struct v4l2_rect rect; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 void* MEDIA_BUS_FMT_SBGGR10_1X10 ; 
 int /*<<< orphan*/  MT9T031_MAX_HEIGHT ; 
 int /*<<< orphan*/  MT9T031_MAX_WIDTH ; 
 int /*<<< orphan*/  MT9T031_MIN_HEIGHT ; 
 int /*<<< orphan*/  MT9T031_MIN_WIDTH ; 
 void* V4L2_COLORSPACE_SRGB ; 
 scalar_t__ V4L2_SUBDEV_FORMAT_TRY ; 
 int mt9t031_set_params (struct i2c_client*,struct v4l2_rect*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt9t031_skip (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mt9t031* to_mt9t031 (struct i2c_client*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l_bound_align_image (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt9t031_set_fmt(struct v4l2_subdev *sd,
		struct v4l2_subdev_pad_config *cfg,
		struct v4l2_subdev_format *format)
{
	struct v4l2_mbus_framefmt *mf = &format->format;
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct mt9t031 *mt9t031 = to_mt9t031(client);
	u16 xskip, yskip;
	struct v4l2_rect rect = mt9t031->rect;

	if (format->pad)
		return -EINVAL;

	mf->code	= MEDIA_BUS_FMT_SBGGR10_1X10;
	mf->colorspace	= V4L2_COLORSPACE_SRGB;
	v4l_bound_align_image(
			&mf->width, MT9T031_MIN_WIDTH, MT9T031_MAX_WIDTH, 1,
			&mf->height, MT9T031_MIN_HEIGHT, MT9T031_MAX_HEIGHT, 1, 0);

	if (format->which == V4L2_SUBDEV_FORMAT_TRY) {
		cfg->try_fmt = *mf;
		return 0;
	}

	/*
	 * Width and height are within limits.
	 * S_FMT: use binning and skipping for scaling
	 */
	xskip = mt9t031_skip(&rect.width, mf->width, MT9T031_MAX_WIDTH);
	yskip = mt9t031_skip(&rect.height, mf->height, MT9T031_MAX_HEIGHT);

	mf->code	= MEDIA_BUS_FMT_SBGGR10_1X10;
	mf->colorspace	= V4L2_COLORSPACE_SRGB;

	/* mt9t031_set_params() doesn't change width and height */
	return mt9t031_set_params(client, &rect, xskip, yskip);
}