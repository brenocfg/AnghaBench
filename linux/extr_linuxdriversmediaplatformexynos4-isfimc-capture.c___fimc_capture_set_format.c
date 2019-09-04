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
struct v4l2_pix_format_mplane {int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_2__* plane_fmt; } ;
struct TYPE_3__ {struct v4l2_pix_format_mplane pix_mp; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct fimc_vid_cap {int /*<<< orphan*/  user_subdev_api; int /*<<< orphan*/  vbq; struct fimc_ctx* ctx; } ;
struct fimc_frame {struct fimc_fmt* fmt; int /*<<< orphan*/ * payload; int /*<<< orphan*/ * bytesperline; } ;
struct fimc_fmt {int memplanes; int /*<<< orphan*/  color; } ;
struct fimc_dev {struct fimc_vid_cap vid_cap; } ;
struct fimc_ctx {int state; struct fimc_frame s_frame; struct fimc_frame d_frame; } ;
struct TYPE_4__ {int /*<<< orphan*/  sizeimage; int /*<<< orphan*/  bytesperline; } ;

/* Variables and functions */
 int EBUSY ; 
 int FIMC_COMPOSE ; 
 int __video_try_or_set_format (struct fimc_dev*,struct v4l2_format*,int,struct fimc_fmt**,struct fimc_fmt**) ; 
 int /*<<< orphan*/  fimc_alpha_ctrl_update (struct fimc_ctx*) ; 
 int /*<<< orphan*/  fimc_capture_mark_jpeg_xfer (struct fimc_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_frame_bounds (struct fimc_frame*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_frame_crop (struct fimc_frame*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vb2_is_busy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __fimc_capture_set_format(struct fimc_dev *fimc,
				     struct v4l2_format *f)
{
	struct fimc_vid_cap *vc = &fimc->vid_cap;
	struct fimc_ctx *ctx = vc->ctx;
	struct v4l2_pix_format_mplane *pix = &f->fmt.pix_mp;
	struct fimc_frame *ff = &ctx->d_frame;
	struct fimc_fmt *inp_fmt = NULL;
	int ret, i;

	if (vb2_is_busy(&fimc->vid_cap.vbq))
		return -EBUSY;

	ret = __video_try_or_set_format(fimc, f, false, &inp_fmt, &ff->fmt);
	if (ret < 0)
		return ret;

	/* Update RGB Alpha control state and value range */
	fimc_alpha_ctrl_update(ctx);

	for (i = 0; i < ff->fmt->memplanes; i++) {
		ff->bytesperline[i] = pix->plane_fmt[i].bytesperline;
		ff->payload[i] = pix->plane_fmt[i].sizeimage;
	}

	set_frame_bounds(ff, pix->width, pix->height);
	/* Reset the composition rectangle if not yet configured */
	if (!(ctx->state & FIMC_COMPOSE))
		set_frame_crop(ff, 0, 0, pix->width, pix->height);

	fimc_capture_mark_jpeg_xfer(ctx, ff->fmt->color);

	/* Reset cropping and set format at the camera interface input */
	if (!vc->user_subdev_api) {
		ctx->s_frame.fmt = inp_fmt;
		set_frame_bounds(&ctx->s_frame, pix->width, pix->height);
		set_frame_crop(&ctx->s_frame, 0, 0, pix->width, pix->height);
	}

	return ret;
}