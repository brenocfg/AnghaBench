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
struct v4l2_mbus_framefmt {int code; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct v4l2_subdev_pad_config {struct v4l2_mbus_framefmt try_fmt; } ;
struct v4l2_subdev_format {scalar_t__ which; scalar_t__ pad; struct v4l2_mbus_framefmt format; } ;
struct v4l2_subdev {int dummy; } ;
struct ov6650 {int /*<<< orphan*/  rect; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  H_CIF ; 
#define  MEDIA_BUS_FMT_SBGGR8_1X8 134 
#define  MEDIA_BUS_FMT_UYVY8_2X8 133 
#define  MEDIA_BUS_FMT_VYUY8_2X8 132 
#define  MEDIA_BUS_FMT_Y10_1X10 131 
#define  MEDIA_BUS_FMT_Y8_1X8 130 
#define  MEDIA_BUS_FMT_YUYV8_2X8 129 
#define  MEDIA_BUS_FMT_YVYU8_2X8 128 
 int /*<<< orphan*/  V4L2_COLORSPACE_JPEG ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SRGB ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 scalar_t__ V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int /*<<< orphan*/  W_CIF ; 
 scalar_t__ is_unscaled_ok (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ov6650_s_fmt (struct v4l2_subdev*,struct v4l2_mbus_framefmt*) ; 
 struct ov6650* to_ov6650 (struct i2c_client*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l_bound_align_image (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ov6650_set_fmt(struct v4l2_subdev *sd,
		struct v4l2_subdev_pad_config *cfg,
		struct v4l2_subdev_format *format)
{
	struct v4l2_mbus_framefmt *mf = &format->format;
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct ov6650 *priv = to_ov6650(client);

	if (format->pad)
		return -EINVAL;

	if (is_unscaled_ok(mf->width, mf->height, &priv->rect))
		v4l_bound_align_image(&mf->width, 2, W_CIF, 1,
				&mf->height, 2, H_CIF, 1, 0);

	mf->field = V4L2_FIELD_NONE;

	switch (mf->code) {
	case MEDIA_BUS_FMT_Y10_1X10:
		mf->code = MEDIA_BUS_FMT_Y8_1X8;
		/* fall through */
	case MEDIA_BUS_FMT_Y8_1X8:
	case MEDIA_BUS_FMT_YVYU8_2X8:
	case MEDIA_BUS_FMT_YUYV8_2X8:
	case MEDIA_BUS_FMT_VYUY8_2X8:
	case MEDIA_BUS_FMT_UYVY8_2X8:
		mf->colorspace = V4L2_COLORSPACE_JPEG;
		break;
	default:
		mf->code = MEDIA_BUS_FMT_SBGGR8_1X8;
		/* fall through */
	case MEDIA_BUS_FMT_SBGGR8_1X8:
		mf->colorspace = V4L2_COLORSPACE_SRGB;
		break;
	}

	if (format->which == V4L2_SUBDEV_FORMAT_ACTIVE)
		return ov6650_s_fmt(sd, mf);
	cfg->try_fmt = *mf;

	return 0;
}