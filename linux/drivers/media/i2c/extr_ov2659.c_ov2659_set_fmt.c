#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_mbus_framefmt {scalar_t__ code; int /*<<< orphan*/  field; int /*<<< orphan*/  colorspace; } ;
struct v4l2_subdev_format {scalar_t__ which; struct v4l2_mbus_framefmt format; int /*<<< orphan*/  pad; } ;
struct v4l2_subdev {int dummy; } ;
struct ov2659_framesize {int dummy; } ;
struct ov2659 {int /*<<< orphan*/  lock; int /*<<< orphan*/  link_frequency; TYPE_1__* pdata; struct v4l2_mbus_framefmt format; int /*<<< orphan*/  format_ctrl_regs; struct ov2659_framesize const* frame_size; scalar_t__ streaming; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
typedef  int s64 ;
struct TYPE_5__ {scalar_t__ code; int /*<<< orphan*/  format_ctrl_regs; } ;
struct TYPE_4__ {int link_frequency; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int EBUSY ; 
 scalar_t__ MEDIA_BUS_FMT_SBGGR8_1X8 ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_SRGB ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 scalar_t__ V4L2_SUBDEV_FORMAT_TRY ; 
 int /*<<< orphan*/  __ov2659_try_frame_size (struct v4l2_mbus_framefmt*,struct ov2659_framesize const**) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__* ov2659_formats ; 
 struct ov2659* to_ov2659 (struct v4l2_subdev*) ; 
 int v4l2_ctrl_s_ctrl_int64 (int /*<<< orphan*/ ,int) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 
 struct v4l2_mbus_framefmt* v4l2_subdev_get_try_format (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ov2659_set_fmt(struct v4l2_subdev *sd,
			  struct v4l2_subdev_pad_config *cfg,
			  struct v4l2_subdev_format *fmt)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	int index = ARRAY_SIZE(ov2659_formats);
	struct v4l2_mbus_framefmt *mf = &fmt->format;
	const struct ov2659_framesize *size = NULL;
	struct ov2659 *ov2659 = to_ov2659(sd);
	int ret = 0;

	dev_dbg(&client->dev, "ov2659_set_fmt\n");

	__ov2659_try_frame_size(mf, &size);

	while (--index >= 0)
		if (ov2659_formats[index].code == mf->code)
			break;

	if (index < 0) {
		index = 0;
		mf->code = ov2659_formats[index].code;
	}

	mf->colorspace = V4L2_COLORSPACE_SRGB;
	mf->field = V4L2_FIELD_NONE;

	mutex_lock(&ov2659->lock);

	if (fmt->which == V4L2_SUBDEV_FORMAT_TRY) {
#ifdef CONFIG_VIDEO_V4L2_SUBDEV_API
		mf = v4l2_subdev_get_try_format(sd, cfg, fmt->pad);
		*mf = fmt->format;
#endif
	} else {
		s64 val;

		if (ov2659->streaming) {
			mutex_unlock(&ov2659->lock);
			return -EBUSY;
		}

		ov2659->frame_size = size;
		ov2659->format = fmt->format;
		ov2659->format_ctrl_regs =
			ov2659_formats[index].format_ctrl_regs;

		if (ov2659->format.code != MEDIA_BUS_FMT_SBGGR8_1X8)
			val = ov2659->pdata->link_frequency / 2;
		else
			val = ov2659->pdata->link_frequency;

		ret = v4l2_ctrl_s_ctrl_int64(ov2659->link_frequency, val);
		if (ret < 0)
			dev_warn(&client->dev,
				 "failed to set link_frequency rate (%d)\n",
				 ret);
	}

	mutex_unlock(&ov2659->lock);
	return ret;
}