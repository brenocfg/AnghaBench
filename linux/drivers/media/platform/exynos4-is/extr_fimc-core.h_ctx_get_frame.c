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
struct fimc_frame {int dummy; } ;
struct fimc_ctx {TYPE_1__* fimc_dev; struct fimc_frame d_frame; struct fimc_frame s_frame; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;
struct TYPE_2__ {int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct fimc_frame* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIMC_CTX_M2M ; 
 int V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE ; 
 int V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 int V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ; 
 scalar_t__ fimc_ctx_state_is_set (int /*<<< orphan*/ ,struct fimc_ctx*) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static inline struct fimc_frame *ctx_get_frame(struct fimc_ctx *ctx,
					       enum v4l2_buf_type type)
{
	struct fimc_frame *frame;

	if (type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ||
	    type == V4L2_BUF_TYPE_VIDEO_OUTPUT) {
		if (fimc_ctx_state_is_set(FIMC_CTX_M2M, ctx))
			frame = &ctx->s_frame;
		else
			return ERR_PTR(-EINVAL);
	} else if (type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE ||
		   type == V4L2_BUF_TYPE_VIDEO_CAPTURE) {
		frame = &ctx->d_frame;
	} else {
		v4l2_err(ctx->fimc_dev->v4l2_dev,
			"Wrong buffer/video queue type (%d)\n", type);
		return ERR_PTR(-EINVAL);
	}

	return frame;
}