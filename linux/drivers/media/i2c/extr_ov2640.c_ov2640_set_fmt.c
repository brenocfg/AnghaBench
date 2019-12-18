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
struct v4l2_mbus_framefmt {int code; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  quantization; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  field; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct v4l2_subdev_pad_config {struct v4l2_mbus_framefmt try_fmt; } ;
struct v4l2_subdev_format {scalar_t__ which; scalar_t__ pad; struct v4l2_mbus_framefmt format; } ;
struct v4l2_subdev {int dummy; } ;
struct ov2640_win_size {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct ov2640_priv {int cfmt_code; int /*<<< orphan*/  lock; struct ov2640_win_size const* win; scalar_t__ streaming; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
#define  MEDIA_BUS_FMT_RGB565_2X8_BE 133 
#define  MEDIA_BUS_FMT_RGB565_2X8_LE 132 
#define  MEDIA_BUS_FMT_UYVY8_2X8 131 
#define  MEDIA_BUS_FMT_VYUY8_2X8 130 
#define  MEDIA_BUS_FMT_YUYV8_2X8 129 
#define  MEDIA_BUS_FMT_YVYU8_2X8 128 
 int /*<<< orphan*/  V4L2_COLORSPACE_SRGB ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  V4L2_QUANTIZATION_DEFAULT ; 
 scalar_t__ V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int /*<<< orphan*/  V4L2_XFER_FUNC_DEFAULT ; 
 int /*<<< orphan*/  V4L2_YCBCR_ENC_DEFAULT ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ov2640_win_size* ov2640_select_win (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ov2640_priv* to_ov2640 (struct i2c_client*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int ov2640_set_fmt(struct v4l2_subdev *sd,
		struct v4l2_subdev_pad_config *cfg,
		struct v4l2_subdev_format *format)
{
	struct v4l2_mbus_framefmt *mf = &format->format;
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct ov2640_priv *priv = to_ov2640(client);
	const struct ov2640_win_size *win;
	int ret = 0;

	if (format->pad)
		return -EINVAL;

	mutex_lock(&priv->lock);

	/* select suitable win */
	win = ov2640_select_win(mf->width, mf->height);
	mf->width	= win->width;
	mf->height	= win->height;

	mf->field	= V4L2_FIELD_NONE;
	mf->colorspace	= V4L2_COLORSPACE_SRGB;
	mf->ycbcr_enc	= V4L2_YCBCR_ENC_DEFAULT;
	mf->quantization = V4L2_QUANTIZATION_DEFAULT;
	mf->xfer_func	= V4L2_XFER_FUNC_DEFAULT;

	switch (mf->code) {
	case MEDIA_BUS_FMT_RGB565_2X8_BE:
	case MEDIA_BUS_FMT_RGB565_2X8_LE:
	case MEDIA_BUS_FMT_YUYV8_2X8:
	case MEDIA_BUS_FMT_UYVY8_2X8:
	case MEDIA_BUS_FMT_YVYU8_2X8:
	case MEDIA_BUS_FMT_VYUY8_2X8:
		break;
	default:
		mf->code = MEDIA_BUS_FMT_UYVY8_2X8;
		break;
	}

	if (format->which == V4L2_SUBDEV_FORMAT_ACTIVE) {
		struct ov2640_priv *priv = to_ov2640(client);

		if (priv->streaming) {
			ret = -EBUSY;
			goto out;
		}
		/* select win */
		priv->win = win;
		/* select format */
		priv->cfmt_code = mf->code;
	} else {
		cfg->try_fmt = *mf;
	}
out:
	mutex_unlock(&priv->lock);

	return ret;
}