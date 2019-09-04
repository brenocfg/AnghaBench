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
struct v4l2_mbus_framefmt {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  field; int /*<<< orphan*/  quantization; int /*<<< orphan*/  xfer_func; int /*<<< orphan*/  ycbcr_enc; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  code; } ;
struct v4l2_subdev_format {scalar_t__ pad; struct v4l2_mbus_framefmt format; } ;
struct v4l2_subdev {int dummy; } ;
struct rj54n1 {int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_1__* fmt; } ;
struct i2c_client {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  colorspace; int /*<<< orphan*/  code; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_FIELD_NONE ; 
 int /*<<< orphan*/  V4L2_QUANTIZATION_DEFAULT ; 
 int /*<<< orphan*/  V4L2_XFER_FUNC_SRGB ; 
 int /*<<< orphan*/  V4L2_YCBCR_ENC_601 ; 
 struct rj54n1* to_rj54n1 (struct i2c_client*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int rj54n1_get_fmt(struct v4l2_subdev *sd,
		struct v4l2_subdev_pad_config *cfg,
		struct v4l2_subdev_format *format)
{
	struct v4l2_mbus_framefmt *mf = &format->format;
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct rj54n1 *rj54n1 = to_rj54n1(client);

	if (format->pad)
		return -EINVAL;

	mf->code	= rj54n1->fmt->code;
	mf->colorspace	= rj54n1->fmt->colorspace;
	mf->ycbcr_enc	= V4L2_YCBCR_ENC_601;
	mf->xfer_func	= V4L2_XFER_FUNC_SRGB;
	mf->quantization = V4L2_QUANTIZATION_DEFAULT;
	mf->field	= V4L2_FIELD_NONE;
	mf->width	= rj54n1->width;
	mf->height	= rj54n1->height;

	return 0;
}