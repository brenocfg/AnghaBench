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
struct v4l2_requestbuffers {scalar_t__ count; } ;
struct s5p_mfc_dev {scalar_t__ dst_bufs_cnt; scalar_t__ capture_state; scalar_t__ total_dpb_count; int /*<<< orphan*/  mfc_ops; int /*<<< orphan*/  vq_dst; } ;
struct s5p_mfc_ctx {scalar_t__ dst_bufs_cnt; scalar_t__ capture_state; scalar_t__ total_dpb_count; int /*<<< orphan*/  mfc_ops; int /*<<< orphan*/  vq_dst; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ QUEUE_BUFS_MMAPED ; 
 scalar_t__ QUEUE_BUFS_REQUESTED ; 
 scalar_t__ QUEUE_FREE ; 
 int /*<<< orphan*/  S5P_MFC_R2H_CMD_INIT_BUFFERS_RET ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  alloc_codec_buffers ; 
 int /*<<< orphan*/  mfc_debug (int,char*,...) ; 
 int /*<<< orphan*/  mfc_err (char*) ; 
 int /*<<< orphan*/  release_codec_buffers ; 
 int /*<<< orphan*/  s5p_mfc_clock_off () ; 
 int /*<<< orphan*/  s5p_mfc_clock_on () ; 
 scalar_t__ s5p_mfc_ctx_ready (struct s5p_mfc_dev*) ; 
 int s5p_mfc_hw_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct s5p_mfc_dev*) ; 
 int /*<<< orphan*/  s5p_mfc_wait_for_done_ctx (struct s5p_mfc_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_work_bit_irqsave (struct s5p_mfc_dev*) ; 
 int /*<<< orphan*/  try_run ; 
 int vb2_reqbufs (int /*<<< orphan*/ *,struct v4l2_requestbuffers*) ; 

__attribute__((used)) static int reqbufs_capture(struct s5p_mfc_dev *dev, struct s5p_mfc_ctx *ctx,
				struct v4l2_requestbuffers *reqbufs)
{
	int ret = 0;

	s5p_mfc_clock_on();

	if (reqbufs->count == 0) {
		mfc_debug(2, "Freeing buffers\n");
		ret = vb2_reqbufs(&ctx->vq_dst, reqbufs);
		if (ret)
			goto out;
		s5p_mfc_hw_call(dev->mfc_ops, release_codec_buffers, ctx);
		ctx->dst_bufs_cnt = 0;
	} else if (ctx->capture_state == QUEUE_FREE) {
		WARN_ON(ctx->dst_bufs_cnt != 0);
		mfc_debug(2, "Allocating %d buffers for CAPTURE queue\n",
				reqbufs->count);
		ret = vb2_reqbufs(&ctx->vq_dst, reqbufs);
		if (ret)
			goto out;

		ctx->capture_state = QUEUE_BUFS_REQUESTED;
		ctx->total_dpb_count = reqbufs->count;

		ret = s5p_mfc_hw_call(dev->mfc_ops, alloc_codec_buffers, ctx);
		if (ret) {
			mfc_err("Failed to allocate decoding buffers\n");
			reqbufs->count = 0;
			vb2_reqbufs(&ctx->vq_dst, reqbufs);
			ret = -ENOMEM;
			ctx->capture_state = QUEUE_FREE;
			goto out;
		}

		WARN_ON(ctx->dst_bufs_cnt != ctx->total_dpb_count);
		ctx->capture_state = QUEUE_BUFS_MMAPED;

		if (s5p_mfc_ctx_ready(ctx))
			set_work_bit_irqsave(ctx);
		s5p_mfc_hw_call(dev->mfc_ops, try_run, dev);
		s5p_mfc_wait_for_done_ctx(ctx, S5P_MFC_R2H_CMD_INIT_BUFFERS_RET,
					  0);
	} else {
		mfc_err("Buffers have already been requested\n");
		ret = -EINVAL;
	}
out:
	s5p_mfc_clock_off();
	if (ret)
		mfc_err("Failed allocating buffers for CAPTURE queue\n");
	return ret;
}