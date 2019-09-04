#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  field; int /*<<< orphan*/  code; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct v4l2_subdev_format {scalar_t__ pad; struct v4l2_mbus_framefmt format; } ;
struct v4l2_subdev {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct mt9t112_priv {TYPE_2__* format; TYPE_1__ frame; } ;
struct i2c_client {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  code; int /*<<< orphan*/  colorspace; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 struct mt9t112_priv* to_mt9t112 (struct i2c_client*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int mt9t112_get_fmt(struct v4l2_subdev *sd,
			   struct v4l2_subdev_pad_config *cfg,
			   struct v4l2_subdev_format *format)
{
	struct v4l2_mbus_framefmt *mf = &format->format;
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct mt9t112_priv *priv = to_mt9t112(client);

	if (format->pad)
		return -EINVAL;

	mf->width	= priv->frame.width;
	mf->height	= priv->frame.height;
	mf->colorspace	= priv->format->colorspace;
	mf->code	= priv->format->code;
	mf->field	= V4L2_FIELD_NONE;

	return 0;
}