#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct vb2_v4l2_buffer {int /*<<< orphan*/  vb2_buf; } ;
struct TYPE_10__ {TYPE_4__* fmt; int /*<<< orphan*/  size; } ;
struct TYPE_8__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; TYPE_2__* fmt; } ;
struct TYPE_6__ {int /*<<< orphan*/  m2m_ctx; } ;
struct s5p_jpeg_ctx {scalar_t__ mode; struct s5p_jpeg* jpeg; TYPE_5__ cap_q; int /*<<< orphan*/  compr_quality; TYPE_3__ out_q; int /*<<< orphan*/  restart_interval; int /*<<< orphan*/  subsampling; TYPE_1__ fh; } ;
struct s5p_jpeg {int /*<<< orphan*/  slock; int /*<<< orphan*/  regs; } ;
struct TYPE_9__ {scalar_t__ fourcc; } ;
struct TYPE_7__ {scalar_t__ fourcc; } ;

/* Variables and functions */
 int /*<<< orphan*/  S5P_JPEG_COEF11 ; 
 int /*<<< orphan*/  S5P_JPEG_COEF12 ; 
 int /*<<< orphan*/  S5P_JPEG_COEF13 ; 
 int /*<<< orphan*/  S5P_JPEG_COEF21 ; 
 int /*<<< orphan*/  S5P_JPEG_COEF22 ; 
 int /*<<< orphan*/  S5P_JPEG_COEF23 ; 
 int /*<<< orphan*/  S5P_JPEG_COEF31 ; 
 int /*<<< orphan*/  S5P_JPEG_COEF32 ; 
 int /*<<< orphan*/  S5P_JPEG_COEF33 ; 
 scalar_t__ S5P_JPEG_ENCODE ; 
 int /*<<< orphan*/  S5P_JPEG_RAW_IN_422 ; 
 int /*<<< orphan*/  S5P_JPEG_RAW_IN_565 ; 
 int /*<<< orphan*/  S5P_JPEG_RAW_OUT_420 ; 
 int /*<<< orphan*/  S5P_JPEG_RAW_OUT_422 ; 
 scalar_t__ V4L2_PIX_FMT_RGB565 ; 
 scalar_t__ V4L2_PIX_FMT_YUYV ; 
 int /*<<< orphan*/  s5p_jpeg_coef (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5p_jpeg_data_num_int_enable (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s5p_jpeg_dri (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5p_jpeg_enc_stream_int (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5p_jpeg_final_mcu_num_int_enable (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s5p_jpeg_htbl_ac (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s5p_jpeg_htbl_dc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s5p_jpeg_imgadr (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  s5p_jpeg_input_raw_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5p_jpeg_jpgadr (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  s5p_jpeg_outform_raw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5p_jpeg_poweron (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5p_jpeg_proc_mode (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  s5p_jpeg_qtbl (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  s5p_jpeg_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5p_jpeg_rst_int_enable (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s5p_jpeg_set_qtbl_chr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5p_jpeg_set_qtbl_lum (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5p_jpeg_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5p_jpeg_subsampling_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5p_jpeg_x (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5p_jpeg_y (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_next_dst_buf (int /*<<< orphan*/ ) ; 
 struct vb2_v4l2_buffer* v4l2_m2m_next_src_buf (int /*<<< orphan*/ ) ; 
 unsigned long vb2_dma_contig_plane_dma_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s5p_jpeg_device_run(void *priv)
{
	struct s5p_jpeg_ctx *ctx = priv;
	struct s5p_jpeg *jpeg = ctx->jpeg;
	struct vb2_v4l2_buffer *src_buf, *dst_buf;
	unsigned long src_addr, dst_addr, flags;

	spin_lock_irqsave(&ctx->jpeg->slock, flags);

	src_buf = v4l2_m2m_next_src_buf(ctx->fh.m2m_ctx);
	dst_buf = v4l2_m2m_next_dst_buf(ctx->fh.m2m_ctx);
	src_addr = vb2_dma_contig_plane_dma_addr(&src_buf->vb2_buf, 0);
	dst_addr = vb2_dma_contig_plane_dma_addr(&dst_buf->vb2_buf, 0);

	s5p_jpeg_reset(jpeg->regs);
	s5p_jpeg_poweron(jpeg->regs);
	s5p_jpeg_proc_mode(jpeg->regs, ctx->mode);
	if (ctx->mode == S5P_JPEG_ENCODE) {
		if (ctx->out_q.fmt->fourcc == V4L2_PIX_FMT_RGB565)
			s5p_jpeg_input_raw_mode(jpeg->regs,
							S5P_JPEG_RAW_IN_565);
		else
			s5p_jpeg_input_raw_mode(jpeg->regs,
							S5P_JPEG_RAW_IN_422);
		s5p_jpeg_subsampling_mode(jpeg->regs, ctx->subsampling);
		s5p_jpeg_dri(jpeg->regs, ctx->restart_interval);
		s5p_jpeg_x(jpeg->regs, ctx->out_q.w);
		s5p_jpeg_y(jpeg->regs, ctx->out_q.h);
		s5p_jpeg_imgadr(jpeg->regs, src_addr);
		s5p_jpeg_jpgadr(jpeg->regs, dst_addr);

		/* ultimately comes from sizeimage from userspace */
		s5p_jpeg_enc_stream_int(jpeg->regs, ctx->cap_q.size);

		/* JPEG RGB to YCbCr conversion matrix */
		s5p_jpeg_coef(jpeg->regs, 1, 1, S5P_JPEG_COEF11);
		s5p_jpeg_coef(jpeg->regs, 1, 2, S5P_JPEG_COEF12);
		s5p_jpeg_coef(jpeg->regs, 1, 3, S5P_JPEG_COEF13);
		s5p_jpeg_coef(jpeg->regs, 2, 1, S5P_JPEG_COEF21);
		s5p_jpeg_coef(jpeg->regs, 2, 2, S5P_JPEG_COEF22);
		s5p_jpeg_coef(jpeg->regs, 2, 3, S5P_JPEG_COEF23);
		s5p_jpeg_coef(jpeg->regs, 3, 1, S5P_JPEG_COEF31);
		s5p_jpeg_coef(jpeg->regs, 3, 2, S5P_JPEG_COEF32);
		s5p_jpeg_coef(jpeg->regs, 3, 3, S5P_JPEG_COEF33);

		/*
		 * JPEG IP allows storing 4 quantization tables
		 * We fill table 0 for luma and table 1 for chroma
		 */
		s5p_jpeg_set_qtbl_lum(jpeg->regs, ctx->compr_quality);
		s5p_jpeg_set_qtbl_chr(jpeg->regs, ctx->compr_quality);
		/* use table 0 for Y */
		s5p_jpeg_qtbl(jpeg->regs, 1, 0);
		/* use table 1 for Cb and Cr*/
		s5p_jpeg_qtbl(jpeg->regs, 2, 1);
		s5p_jpeg_qtbl(jpeg->regs, 3, 1);

		/* Y, Cb, Cr use Huffman table 0 */
		s5p_jpeg_htbl_ac(jpeg->regs, 1);
		s5p_jpeg_htbl_dc(jpeg->regs, 1);
		s5p_jpeg_htbl_ac(jpeg->regs, 2);
		s5p_jpeg_htbl_dc(jpeg->regs, 2);
		s5p_jpeg_htbl_ac(jpeg->regs, 3);
		s5p_jpeg_htbl_dc(jpeg->regs, 3);
	} else { /* S5P_JPEG_DECODE */
		s5p_jpeg_rst_int_enable(jpeg->regs, true);
		s5p_jpeg_data_num_int_enable(jpeg->regs, true);
		s5p_jpeg_final_mcu_num_int_enable(jpeg->regs, true);
		if (ctx->cap_q.fmt->fourcc == V4L2_PIX_FMT_YUYV)
			s5p_jpeg_outform_raw(jpeg->regs, S5P_JPEG_RAW_OUT_422);
		else
			s5p_jpeg_outform_raw(jpeg->regs, S5P_JPEG_RAW_OUT_420);
		s5p_jpeg_jpgadr(jpeg->regs, src_addr);
		s5p_jpeg_imgadr(jpeg->regs, dst_addr);
	}

	s5p_jpeg_start(jpeg->regs);

	spin_unlock_irqrestore(&ctx->jpeg->slock, flags);
}