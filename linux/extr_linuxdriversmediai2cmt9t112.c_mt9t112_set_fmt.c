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
struct v4l2_mbus_framefmt {scalar_t__ code; int /*<<< orphan*/  field; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  colorspace; } ;
struct v4l2_subdev_pad_config {struct v4l2_mbus_framefmt try_fmt; } ;
struct v4l2_subdev_format {scalar_t__ which; scalar_t__ pad; struct v4l2_mbus_framefmt format; } ;
struct v4l2_subdev {int dummy; } ;
struct mt9t112_priv {int num_formats; } ;
struct i2c_client {int dummy; } ;
struct TYPE_2__ {scalar_t__ code; int /*<<< orphan*/  colorspace; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MAX_HEIGHT ; 
 int /*<<< orphan*/  MAX_WIDTH ; 
 scalar_t__ MEDIA_BUS_FMT_UYVY8_2X8 ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_JPEG ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 scalar_t__ V4L2_SUBDEV_FORMAT_ACTIVE ; 
 TYPE_1__* mt9t112_cfmts ; 
 int mt9t112_s_fmt (struct v4l2_subdev*,struct v4l2_mbus_framefmt*) ; 
 struct mt9t112_priv* to_mt9t112 (struct i2c_client*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l_bound_align_image (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt9t112_set_fmt(struct v4l2_subdev *sd,
			   struct v4l2_subdev_pad_config *cfg,
			   struct v4l2_subdev_format *format)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct v4l2_mbus_framefmt *mf = &format->format;
	struct mt9t112_priv *priv = to_mt9t112(client);
	int i;

	if (format->pad)
		return -EINVAL;

	for (i = 0; i < priv->num_formats; i++)
		if (mt9t112_cfmts[i].code == mf->code)
			break;

	if (i == priv->num_formats) {
		mf->code = MEDIA_BUS_FMT_UYVY8_2X8;
		mf->colorspace = V4L2_COLORSPACE_JPEG;
	} else {
		mf->colorspace = mt9t112_cfmts[i].colorspace;
	}

	v4l_bound_align_image(&mf->width, 0, MAX_WIDTH, 0,
			      &mf->height, 0, MAX_HEIGHT, 0, 0);

	mf->field = V4L2_FIELD_NONE;

	if (format->which == V4L2_SUBDEV_FORMAT_ACTIVE)
		return mt9t112_s_fmt(sd, mf);
	cfg->try_fmt = *mf;

	return 0;
}