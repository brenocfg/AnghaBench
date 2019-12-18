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
struct vb2_v4l2_buffer {int /*<<< orphan*/  vb2_buf; } ;
struct TYPE_4__ {int /*<<< orphan*/  m2m_ctx; } ;
struct s5p_jpeg_ctx {scalar_t__ mode; TYPE_2__ fh; int /*<<< orphan*/  subsampling; } ;
struct s5p_jpeg {scalar_t__ irq_ret; int /*<<< orphan*/  m2m_dev; int /*<<< orphan*/  slock; int /*<<< orphan*/  regs; TYPE_1__* variant; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {scalar_t__ version; } ;

/* Variables and functions */
 scalar_t__ ERR_DEC_INVALID_FORMAT ; 
 scalar_t__ ERR_FRAME ; 
 scalar_t__ ERR_MULTI_SCAN ; 
 scalar_t__ ERR_PROT ; 
 void* ERR_UNKNOWN ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ OK_ENC_OR_DEC ; 
 int /*<<< orphan*/  S5P_JPEG_DISABLE ; 
 scalar_t__ S5P_JPEG_ENCODE ; 
 scalar_t__ SJPEG_EXYNOS4 ; 
 int /*<<< orphan*/  VB2_BUF_STATE_DONE ; 
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 int /*<<< orphan*/  exynos4_jpeg_get_frame_fmt (int /*<<< orphan*/ ) ; 
 unsigned int exynos4_jpeg_get_int_status (int /*<<< orphan*/ ) ; 
 unsigned long exynos4_jpeg_get_stream_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos4_jpeg_set_enc_dec_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos4_jpeg_set_sys_int_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_m2m_buf_done (struct vb2_v4l2_buffer*,int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_dst_buf_remove (int /*<<< orphan*/ ) ; 
 struct s5p_jpeg_ctx* v4l2_m2m_get_curr_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_m2m_job_finish (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_src_buf_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_set_plane_payload (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static irqreturn_t exynos4_jpeg_irq(int irq, void *priv)
{
	unsigned int int_status;
	struct vb2_v4l2_buffer *src_vb, *dst_vb;
	struct s5p_jpeg *jpeg = priv;
	struct s5p_jpeg_ctx *curr_ctx;
	unsigned long payload_size = 0;

	spin_lock(&jpeg->slock);

	exynos4_jpeg_set_sys_int_enable(jpeg->regs, 0);

	curr_ctx = v4l2_m2m_get_curr_priv(jpeg->m2m_dev);

	src_vb = v4l2_m2m_src_buf_remove(curr_ctx->fh.m2m_ctx);
	dst_vb = v4l2_m2m_dst_buf_remove(curr_ctx->fh.m2m_ctx);

	int_status = exynos4_jpeg_get_int_status(jpeg->regs);

	if (int_status) {
		switch (int_status & 0x1f) {
		case 0x1:
			jpeg->irq_ret = ERR_PROT;
			break;
		case 0x2:
			jpeg->irq_ret = OK_ENC_OR_DEC;
			break;
		case 0x4:
			jpeg->irq_ret = ERR_DEC_INVALID_FORMAT;
			break;
		case 0x8:
			jpeg->irq_ret = ERR_MULTI_SCAN;
			break;
		case 0x10:
			jpeg->irq_ret = ERR_FRAME;
			break;
		default:
			jpeg->irq_ret = ERR_UNKNOWN;
			break;
		}
	} else {
		jpeg->irq_ret = ERR_UNKNOWN;
	}

	if (jpeg->irq_ret == OK_ENC_OR_DEC) {
		if (curr_ctx->mode == S5P_JPEG_ENCODE) {
			payload_size = exynos4_jpeg_get_stream_size(jpeg->regs);
			vb2_set_plane_payload(&dst_vb->vb2_buf,
					0, payload_size);
		}
		v4l2_m2m_buf_done(src_vb, VB2_BUF_STATE_DONE);
		v4l2_m2m_buf_done(dst_vb, VB2_BUF_STATE_DONE);
	} else {
		v4l2_m2m_buf_done(src_vb, VB2_BUF_STATE_ERROR);
		v4l2_m2m_buf_done(dst_vb, VB2_BUF_STATE_ERROR);
	}

	if (jpeg->variant->version == SJPEG_EXYNOS4)
		curr_ctx->subsampling = exynos4_jpeg_get_frame_fmt(jpeg->regs);

	exynos4_jpeg_set_enc_dec_mode(jpeg->regs, S5P_JPEG_DISABLE);

	spin_unlock(&jpeg->slock);

	v4l2_m2m_job_finish(jpeg->m2m_dev, curr_ctx->fh.m2m_ctx);
	return IRQ_HANDLED;
}