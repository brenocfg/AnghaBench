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
struct v4l2_subdev_frame_interval_enum {int /*<<< orphan*/  interval; int /*<<< orphan*/  code; int /*<<< orphan*/  which; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  index; } ;
struct v4l2_frmivalenum {int /*<<< orphan*/  discrete; int /*<<< orphan*/  type; int /*<<< orphan*/  pixel_format; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  index; } ;
struct file {int dummy; } ;
struct cal_fmt {int /*<<< orphan*/  code; } ;
struct cal_ctx {int /*<<< orphan*/  sensor; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_FRMIVAL_TYPE_DISCRETE ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int /*<<< orphan*/  enum_frame_interval ; 
 struct cal_fmt* find_format_by_pix (struct cal_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pad ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct v4l2_subdev_frame_interval_enum*) ; 
 struct cal_ctx* video_drvdata (struct file*) ; 

__attribute__((used)) static int cal_enum_frameintervals(struct file *file, void *priv,
				   struct v4l2_frmivalenum *fival)
{
	struct cal_ctx *ctx = video_drvdata(file);
	const struct cal_fmt *fmt;
	struct v4l2_subdev_frame_interval_enum fie = {
		.index = fival->index,
		.width = fival->width,
		.height = fival->height,
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	};
	int ret;

	fmt = find_format_by_pix(ctx, fival->pixel_format);
	if (!fmt)
		return -EINVAL;

	fie.code = fmt->code;
	ret = v4l2_subdev_call(ctx->sensor, pad, enum_frame_interval,
			       NULL, &fie);
	if (ret)
		return ret;
	fival->type = V4L2_FRMIVAL_TYPE_DISCRETE;
	fival->discrete = fie.interval;

	return 0;
}