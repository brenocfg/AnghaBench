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
struct file {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  m2m_ctx; } ;
struct bdisp_ctx {TYPE_2__ fh; TYPE_1__* bdisp_dev; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDISP_DST_FMT ; 
 int /*<<< orphan*/  BDISP_SRC_FMT ; 
 int EINVAL ; 
 int V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 int /*<<< orphan*/  bdisp_ctx_state_is_set (int /*<<< orphan*/ ,struct bdisp_ctx*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct bdisp_ctx* fh_to_ctx (void*) ; 
 int v4l2_m2m_streamon (struct file*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bdisp_streamon(struct file *file, void *fh, enum v4l2_buf_type type)
{
	struct bdisp_ctx *ctx = fh_to_ctx(fh);

	if ((type == V4L2_BUF_TYPE_VIDEO_OUTPUT) &&
	    !bdisp_ctx_state_is_set(BDISP_SRC_FMT, ctx)) {
		dev_err(ctx->bdisp_dev->dev, "src not defined\n");
		return -EINVAL;
	}

	if ((type == V4L2_BUF_TYPE_VIDEO_CAPTURE) &&
	    !bdisp_ctx_state_is_set(BDISP_DST_FMT, ctx)) {
		dev_err(ctx->bdisp_dev->dev, "dst not defined\n");
		return -EINVAL;
	}

	return v4l2_m2m_streamon(file, ctx->fh.m2m_ctx, type);
}