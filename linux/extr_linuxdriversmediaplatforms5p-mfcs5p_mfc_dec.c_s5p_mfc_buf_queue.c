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
struct vb2_buffer {size_t index; struct vb2_queue* vb2_queue; } ;
struct s5p_mfc_dev {int /*<<< orphan*/  mfc_ops; int /*<<< orphan*/  irqlock; } ;
struct s5p_mfc_ctx {int /*<<< orphan*/  dst_queue_cnt; int /*<<< orphan*/  dst_queue; int /*<<< orphan*/  dec_dst_flag; struct s5p_mfc_buf* dst_bufs; int /*<<< orphan*/  src_queue_cnt; int /*<<< orphan*/  src_queue; struct s5p_mfc_buf* src_bufs; struct s5p_mfc_dev* dev; } ;
struct s5p_mfc_buf {int /*<<< orphan*/  list; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MFC_BUF_FLAG_USED ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE ; 
 struct s5p_mfc_ctx* fh_to_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mfc_err (char*,scalar_t__) ; 
 scalar_t__ s5p_mfc_ctx_ready (struct s5p_mfc_ctx*) ; 
 int /*<<< orphan*/  s5p_mfc_hw_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct s5p_mfc_dev*) ; 
 int /*<<< orphan*/  set_bit (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_work_bit_irqsave (struct s5p_mfc_ctx*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  try_run ; 

__attribute__((used)) static void s5p_mfc_buf_queue(struct vb2_buffer *vb)
{
	struct vb2_queue *vq = vb->vb2_queue;
	struct s5p_mfc_ctx *ctx = fh_to_ctx(vq->drv_priv);
	struct s5p_mfc_dev *dev = ctx->dev;
	unsigned long flags;
	struct s5p_mfc_buf *mfc_buf;

	if (vq->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) {
		mfc_buf = &ctx->src_bufs[vb->index];
		mfc_buf->flags &= ~MFC_BUF_FLAG_USED;
		spin_lock_irqsave(&dev->irqlock, flags);
		list_add_tail(&mfc_buf->list, &ctx->src_queue);
		ctx->src_queue_cnt++;
		spin_unlock_irqrestore(&dev->irqlock, flags);
	} else if (vq->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) {
		mfc_buf = &ctx->dst_bufs[vb->index];
		mfc_buf->flags &= ~MFC_BUF_FLAG_USED;
		/* Mark destination as available for use by MFC */
		spin_lock_irqsave(&dev->irqlock, flags);
		set_bit(vb->index, &ctx->dec_dst_flag);
		list_add_tail(&mfc_buf->list, &ctx->dst_queue);
		ctx->dst_queue_cnt++;
		spin_unlock_irqrestore(&dev->irqlock, flags);
	} else {
		mfc_err("Unsupported buffer type (%d)\n", vq->type);
	}
	if (s5p_mfc_ctx_ready(ctx))
		set_work_bit_irqsave(ctx);
	s5p_mfc_hw_call(dev->mfc_ops, try_run, dev);
}