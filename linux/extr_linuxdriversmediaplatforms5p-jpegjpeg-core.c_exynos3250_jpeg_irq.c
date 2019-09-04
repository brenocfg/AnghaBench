#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int /*<<< orphan*/  timestamp; } ;
struct vb2_v4l2_buffer {TYPE_3__ vb2_buf; int /*<<< orphan*/  timecode; } ;
struct TYPE_5__ {int /*<<< orphan*/  m2m_ctx; } ;
struct s5p_jpeg_ctx {scalar_t__ mode; TYPE_2__ fh; int /*<<< orphan*/  subsampling; } ;
struct s5p_jpeg {int irq_status; int /*<<< orphan*/  slock; int /*<<< orphan*/  m2m_dev; int /*<<< orphan*/  regs; int /*<<< orphan*/  dev; TYPE_1__* variant; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  enum vb2_buffer_state { ____Placeholder_vb2_buffer_state } vb2_buffer_state ;
struct TYPE_4__ {scalar_t__ version; } ;

/* Variables and functions */
 int EXYNOS3250_HEADER_STAT ; 
 int EXYNOS3250_JPEG_DONE ; 
 int EXYNOS3250_RDMA_DONE ; 
 int EXYNOS3250_RESULT_STAT ; 
 int EXYNOS3250_STREAM_STAT ; 
 int EXYNOS3250_TIMER_INT_STAT ; 
 int EXYNOS3250_WDMA_DONE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ S5P_JPEG_DECODE ; 
 scalar_t__ S5P_JPEG_ENCODE ; 
 scalar_t__ SJPEG_EXYNOS5420 ; 
 int VB2_BUF_STATE_DONE ; 
 int VB2_BUF_STATE_ERROR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  exynos3250_jpeg_clear_int_status (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  exynos3250_jpeg_clear_timer_status (int /*<<< orphan*/ ) ; 
 unsigned long exynos3250_jpeg_compressed_size (int /*<<< orphan*/ ) ; 
 int exynos3250_jpeg_get_int_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos3250_jpeg_get_subsampling_mode (int /*<<< orphan*/ ) ; 
 int exynos3250_jpeg_get_timer_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos3250_jpeg_rstart (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_m2m_buf_done (struct vb2_v4l2_buffer*,int) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_dst_buf_remove (int /*<<< orphan*/ ) ; 
 struct s5p_jpeg_ctx* v4l2_m2m_get_curr_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_job_finish (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_src_buf_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_set_plane_payload (TYPE_3__*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static irqreturn_t exynos3250_jpeg_irq(int irq, void *dev_id)
{
	struct s5p_jpeg *jpeg = dev_id;
	struct s5p_jpeg_ctx *curr_ctx;
	struct vb2_v4l2_buffer *src_buf, *dst_buf;
	unsigned long payload_size = 0;
	enum vb2_buffer_state state = VB2_BUF_STATE_DONE;
	bool interrupt_timeout = false;
	bool stream_error = false;
	u32 irq_status;

	spin_lock(&jpeg->slock);

	irq_status = exynos3250_jpeg_get_timer_status(jpeg->regs);
	if (irq_status & EXYNOS3250_TIMER_INT_STAT) {
		exynos3250_jpeg_clear_timer_status(jpeg->regs);
		interrupt_timeout = true;
		dev_err(jpeg->dev, "Interrupt timeout occurred.\n");
	}

	irq_status = exynos3250_jpeg_get_int_status(jpeg->regs);
	exynos3250_jpeg_clear_int_status(jpeg->regs, irq_status);

	jpeg->irq_status |= irq_status;

	if (jpeg->variant->version == SJPEG_EXYNOS5420 &&
	    irq_status & EXYNOS3250_STREAM_STAT) {
		stream_error = true;
		dev_err(jpeg->dev, "Syntax error or unrecoverable error occurred.\n");
	}

	curr_ctx = v4l2_m2m_get_curr_priv(jpeg->m2m_dev);

	if (!curr_ctx)
		goto exit_unlock;

	if ((irq_status & EXYNOS3250_HEADER_STAT) &&
	    (curr_ctx->mode == S5P_JPEG_DECODE)) {
		exynos3250_jpeg_rstart(jpeg->regs);
		goto exit_unlock;
	}

	if (jpeg->irq_status & (EXYNOS3250_JPEG_DONE |
				EXYNOS3250_WDMA_DONE |
				EXYNOS3250_RDMA_DONE |
				EXYNOS3250_RESULT_STAT))
		payload_size = exynos3250_jpeg_compressed_size(jpeg->regs);
	else if (interrupt_timeout || stream_error)
		state = VB2_BUF_STATE_ERROR;
	else
		goto exit_unlock;

	src_buf = v4l2_m2m_src_buf_remove(curr_ctx->fh.m2m_ctx);
	dst_buf = v4l2_m2m_dst_buf_remove(curr_ctx->fh.m2m_ctx);

	dst_buf->timecode = src_buf->timecode;
	dst_buf->vb2_buf.timestamp = src_buf->vb2_buf.timestamp;

	v4l2_m2m_buf_done(src_buf, state);
	if (curr_ctx->mode == S5P_JPEG_ENCODE)
		vb2_set_plane_payload(&dst_buf->vb2_buf, 0, payload_size);
	v4l2_m2m_buf_done(dst_buf, state);

	curr_ctx->subsampling =
			exynos3250_jpeg_get_subsampling_mode(jpeg->regs);

	spin_unlock(&jpeg->slock);

	v4l2_m2m_job_finish(jpeg->m2m_dev, curr_ctx->fh.m2m_ctx);
	return IRQ_HANDLED;

exit_unlock:
	spin_unlock(&jpeg->slock);
	return IRQ_HANDLED;
}