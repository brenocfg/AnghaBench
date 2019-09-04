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
struct TYPE_4__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct v4l2_crop {scalar_t__ type; TYPE_2__ c; } ;
struct fimc_frame {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  offs_v; int /*<<< orphan*/  offs_h; } ;
struct TYPE_3__ {int /*<<< orphan*/  vfd; } ;
struct fimc_dev {TYPE_1__ m2m; } ;
struct fimc_ctx {int /*<<< orphan*/  rotation; struct fimc_frame s_frame; struct fimc_frame d_frame; struct fimc_dev* fimc_dev; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FIMC_PARAMS ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ; 
 struct fimc_ctx* fh_to_ctx (void*) ; 
 int fimc_check_scaler_ratio (struct fimc_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fimc_ctx_state_set (int /*<<< orphan*/ ,struct fimc_ctx*) ; 
 int fimc_m2m_try_crop (struct fimc_ctx*,struct v4l2_crop*) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int fimc_m2m_s_crop(struct file *file, void *fh, const struct v4l2_crop *crop)
{
	struct fimc_ctx *ctx = fh_to_ctx(fh);
	struct fimc_dev *fimc = ctx->fimc_dev;
	struct v4l2_crop cr = *crop;
	struct fimc_frame *f;
	int ret;

	ret = fimc_m2m_try_crop(ctx, &cr);
	if (ret)
		return ret;

	f = (cr.type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) ?
		&ctx->s_frame : &ctx->d_frame;

	/* Check to see if scaling ratio is within supported range */
	if (cr.type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) {
		ret = fimc_check_scaler_ratio(ctx, cr.c.width,
				cr.c.height, ctx->d_frame.width,
				ctx->d_frame.height, ctx->rotation);
	} else {
		ret = fimc_check_scaler_ratio(ctx, ctx->s_frame.width,
				ctx->s_frame.height, cr.c.width,
				cr.c.height, ctx->rotation);
	}
	if (ret) {
		v4l2_err(&fimc->m2m.vfd, "Out of scaler range\n");
		return -EINVAL;
	}

	f->offs_h = cr.c.left;
	f->offs_v = cr.c.top;
	f->width  = cr.c.width;
	f->height = cr.c.height;

	fimc_ctx_state_set(FIMC_PARAMS, ctx);

	return 0;
}