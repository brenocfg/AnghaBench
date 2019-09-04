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
struct v4l2_fmtdesc {size_t index; int /*<<< orphan*/  type; int /*<<< orphan*/  pixelformat; } ;
struct file {int dummy; } ;
struct cal_fmt {int /*<<< orphan*/  fourcc; } ;
struct cal_ctx {size_t num_active_fmt; struct cal_fmt** active_fmt; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 struct cal_ctx* video_drvdata (struct file*) ; 

__attribute__((used)) static int cal_enum_fmt_vid_cap(struct file *file, void  *priv,
				struct v4l2_fmtdesc *f)
{
	struct cal_ctx *ctx = video_drvdata(file);
	const struct cal_fmt *fmt = NULL;

	if (f->index >= ctx->num_active_fmt)
		return -EINVAL;

	fmt = ctx->active_fmt[f->index];

	f->pixelformat = fmt->fourcc;
	f->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	return 0;
}