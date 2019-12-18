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
struct s5p_mfc_dev {scalar_t__ curr_ctx; int /*<<< orphan*/  irqlock; scalar_t__ hw_lock; } ;
struct s5p_mfc_ctx {scalar_t__ state; scalar_t__ num; scalar_t__ src_queue_cnt; int /*<<< orphan*/  src_queue; int /*<<< orphan*/  vq_src; scalar_t__ dst_queue_cnt; int /*<<< orphan*/  dst_queue; int /*<<< orphan*/  vq_dst; struct s5p_mfc_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ MFCINST_ABORT ; 
 scalar_t__ MFCINST_FINISHED ; 
 scalar_t__ MFCINST_FINISHING ; 
 scalar_t__ MFCINST_RUNNING ; 
 int /*<<< orphan*/  S5P_MFC_R2H_CMD_FRAME_DONE_RET ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ; 
 int /*<<< orphan*/  cleanup_ref_queue (struct s5p_mfc_ctx*) ; 
 struct s5p_mfc_ctx* fh_to_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5p_mfc_cleanup_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s5p_mfc_wait_for_done_ctx (struct s5p_mfc_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void s5p_mfc_stop_streaming(struct vb2_queue *q)
{
	unsigned long flags;
	struct s5p_mfc_ctx *ctx = fh_to_ctx(q->drv_priv);
	struct s5p_mfc_dev *dev = ctx->dev;

	if ((ctx->state == MFCINST_FINISHING ||
		ctx->state == MFCINST_RUNNING) &&
		dev->curr_ctx == ctx->num && dev->hw_lock) {
		ctx->state = MFCINST_ABORT;
		s5p_mfc_wait_for_done_ctx(ctx, S5P_MFC_R2H_CMD_FRAME_DONE_RET,
					  0);
	}
	ctx->state = MFCINST_FINISHED;
	spin_lock_irqsave(&dev->irqlock, flags);
	if (q->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) {
		s5p_mfc_cleanup_queue(&ctx->dst_queue, &ctx->vq_dst);
		INIT_LIST_HEAD(&ctx->dst_queue);
		ctx->dst_queue_cnt = 0;
	}
	if (q->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) {
		cleanup_ref_queue(ctx);
		s5p_mfc_cleanup_queue(&ctx->src_queue, &ctx->vq_src);
		INIT_LIST_HEAD(&ctx->src_queue);
		ctx->src_queue_cnt = 0;
	}
	spin_unlock_irqrestore(&dev->irqlock, flags);
}