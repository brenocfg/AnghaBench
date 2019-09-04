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
struct vb2_queue {scalar_t__ type; int /*<<< orphan*/  drv_priv; } ;
struct s5p_mfc_dev {scalar_t__ curr_ctx; int /*<<< orphan*/  mfc_ops; scalar_t__ hw_lock; } ;
struct s5p_mfc_ctx {scalar_t__ state; scalar_t__ num; scalar_t__ src_bufs_cnt; scalar_t__ pb_count; struct s5p_mfc_dev* dev; } ;

/* Variables and functions */
 int ENOBUFS ; 
 scalar_t__ IS_MFCV6_PLUS (struct s5p_mfc_dev*) ; 
 scalar_t__ MFCINST_GOT_INST ; 
 int /*<<< orphan*/  S5P_MFC_R2H_CMD_SEQ_DONE_RET ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE ; 
 struct s5p_mfc_ctx* fh_to_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfc_err (char*,scalar_t__) ; 
 scalar_t__ s5p_mfc_ctx_ready (struct s5p_mfc_ctx*) ; 
 int /*<<< orphan*/  s5p_mfc_hw_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct s5p_mfc_dev*) ; 
 int /*<<< orphan*/  s5p_mfc_wait_for_done_ctx (struct s5p_mfc_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_work_bit_irqsave (struct s5p_mfc_ctx*) ; 
 int /*<<< orphan*/  try_run ; 

__attribute__((used)) static int s5p_mfc_start_streaming(struct vb2_queue *q, unsigned int count)
{
	struct s5p_mfc_ctx *ctx = fh_to_ctx(q->drv_priv);
	struct s5p_mfc_dev *dev = ctx->dev;

	if (IS_MFCV6_PLUS(dev) &&
			(q->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)) {

		if ((ctx->state == MFCINST_GOT_INST) &&
			(dev->curr_ctx == ctx->num) && dev->hw_lock) {
			s5p_mfc_wait_for_done_ctx(ctx,
						S5P_MFC_R2H_CMD_SEQ_DONE_RET,
						0);
		}

		if (ctx->src_bufs_cnt < ctx->pb_count) {
			mfc_err("Need minimum %d OUTPUT buffers\n",
					ctx->pb_count);
			return -ENOBUFS;
		}
	}

	/* If context is ready then dev = work->data;schedule it to run */
	if (s5p_mfc_ctx_ready(ctx))
		set_work_bit_irqsave(ctx);
	s5p_mfc_hw_call(dev->mfc_ops, try_run, dev);

	return 0;
}