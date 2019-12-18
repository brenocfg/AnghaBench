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
struct v4l2_subdev_frame_size_enum {scalar_t__ min_width; scalar_t__ max_width; scalar_t__ min_height; scalar_t__ max_height; int /*<<< orphan*/  code; int /*<<< orphan*/  which; int /*<<< orphan*/  pad; int /*<<< orphan*/  index; } ;
struct TYPE_4__ {scalar_t__ min_width; scalar_t__ max_width; scalar_t__ min_height; scalar_t__ max_height; int step_width; int step_height; } ;
struct TYPE_3__ {scalar_t__ width; scalar_t__ height; } ;
struct v4l2_frmsizeenum {TYPE_2__ stepwise; int /*<<< orphan*/  type; TYPE_1__ discrete; int /*<<< orphan*/  pixel_format; int /*<<< orphan*/  index; } ;
struct imx_media_pixfmt {int /*<<< orphan*/ * codes; } ;
struct file {int dummy; } ;
struct capture_priv {int /*<<< orphan*/  src_sd; int /*<<< orphan*/  src_sd_pad; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_SEL_ANY ; 
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_FRMSIZE_TYPE_CONTINUOUS ; 
 int /*<<< orphan*/  V4L2_FRMSIZE_TYPE_DISCRETE ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int /*<<< orphan*/  enum_frame_size ; 
 struct imx_media_pixfmt* imx_media_find_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pad ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v4l2_subdev_frame_size_enum*) ; 
 struct capture_priv* video_drvdata (struct file*) ; 

__attribute__((used)) static int capture_enum_framesizes(struct file *file, void *fh,
				   struct v4l2_frmsizeenum *fsize)
{
	struct capture_priv *priv = video_drvdata(file);
	const struct imx_media_pixfmt *cc;
	struct v4l2_subdev_frame_size_enum fse = {
		.index = fsize->index,
		.pad = priv->src_sd_pad,
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	};
	int ret;

	cc = imx_media_find_format(fsize->pixel_format, CS_SEL_ANY, true);
	if (!cc)
		return -EINVAL;

	fse.code = cc->codes[0];

	ret = v4l2_subdev_call(priv->src_sd, pad, enum_frame_size, NULL, &fse);
	if (ret)
		return ret;

	if (fse.min_width == fse.max_width &&
	    fse.min_height == fse.max_height) {
		fsize->type = V4L2_FRMSIZE_TYPE_DISCRETE;
		fsize->discrete.width = fse.min_width;
		fsize->discrete.height = fse.min_height;
	} else {
		fsize->type = V4L2_FRMSIZE_TYPE_CONTINUOUS;
		fsize->stepwise.min_width = fse.min_width;
		fsize->stepwise.max_width = fse.max_width;
		fsize->stepwise.min_height = fse.min_height;
		fsize->stepwise.max_height = fse.max_height;
		fsize->stepwise.step_width = 1;
		fsize->stepwise.step_height = 1;
	}

	return 0;
}