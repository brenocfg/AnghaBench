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
struct s5p_mfc_dev {int dummy; } ;
struct s5p_mfc_ctx {scalar_t__ src_bufs_cnt; scalar_t__ output_state; scalar_t__ state; int /*<<< orphan*/  vq_src; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MFCINST_INIT ; 
 scalar_t__ QUEUE_BUFS_REQUESTED ; 
 scalar_t__ QUEUE_FREE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  mfc_debug (int,char*,...) ; 
 int /*<<< orphan*/  mfc_err (char*) ; 
 int /*<<< orphan*/  s5p_mfc_clock_off () ; 
 int /*<<< orphan*/  s5p_mfc_clock_on () ; 
 int s5p_mfc_open_mfc_inst (struct s5p_mfc_dev*,struct s5p_mfc_ctx*) ; 
 int vb2_reqbufs (int /*<<< orphan*/ *,struct v4l2_requestbuffers*) ; 

__attribute__((used)) static int reqbufs_output(struct s5p_mfc_dev *dev, struct s5p_mfc_ctx *ctx,
				struct v4l2_requestbuffers *reqbufs)
{
	int ret = 0;

	s5p_mfc_clock_on();

	if (reqbufs->count == 0) {
		mfc_debug(2, "Freeing buffers\n");
		ret = vb2_reqbufs(&ctx->vq_src, reqbufs);
		if (ret)
			goto out;
		ctx->src_bufs_cnt = 0;
		ctx->output_state = QUEUE_FREE;
	} else if (ctx->output_state == QUEUE_FREE) {
		/* Can only request buffers when we have a valid format set. */
		WARN_ON(ctx->src_bufs_cnt != 0);
		if (ctx->state != MFCINST_INIT) {
			mfc_err("Reqbufs called in an invalid state\n");
			ret = -EINVAL;
			goto out;
		}

		mfc_debug(2, "Allocating %d buffers for OUTPUT queue\n",
				reqbufs->count);
		ret = vb2_reqbufs(&ctx->vq_src, reqbufs);
		if (ret)
			goto out;

		ret = s5p_mfc_open_mfc_inst(dev, ctx);
		if (ret) {
			reqbufs->count = 0;
			vb2_reqbufs(&ctx->vq_src, reqbufs);
			goto out;
		}

		ctx->output_state = QUEUE_BUFS_REQUESTED;
	} else {
		mfc_err("Buffers have already been requested\n");
		ret = -EINVAL;
	}
out:
	s5p_mfc_clock_off();
	if (ret)
		mfc_err("Failed allocating buffers for OUTPUT queue\n");
	return ret;
}