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
struct TYPE_10__ {int /*<<< orphan*/  size; TYPE_1__* fmt; } ;
struct TYPE_9__ {TYPE_3__* fmt; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct s5p_jpeg_ctx {scalar_t__ mode; TYPE_5__ out_q; TYPE_4__ cap_q; int /*<<< orphan*/  subsampling; struct s5p_jpeg* jpeg; int /*<<< orphan*/  compr_quality; } ;
struct s5p_jpeg {int /*<<< orphan*/  slock; int /*<<< orphan*/  regs; TYPE_2__* variant; } ;
struct TYPE_8__ {int /*<<< orphan*/  fourcc; } ;
struct TYPE_7__ {scalar_t__ version; } ;
struct TYPE_6__ {int /*<<< orphan*/  fourcc; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 scalar_t__ S5P_JPEG_ENCODE ; 
 scalar_t__ SJPEG_EXYNOS4 ; 
 scalar_t__ SJPEG_EXYNOS5433 ; 
 int /*<<< orphan*/  exynos4_jpeg_parse_decode_h_tbl (struct s5p_jpeg_ctx*) ; 
 int /*<<< orphan*/  exynos4_jpeg_parse_decode_q_tbl (struct s5p_jpeg_ctx*) ; 
 int /*<<< orphan*/  exynos4_jpeg_parse_huff_tbl (struct s5p_jpeg_ctx*) ; 
 int /*<<< orphan*/  exynos4_jpeg_parse_q_tbl (struct s5p_jpeg_ctx*) ; 
 int /*<<< orphan*/  exynos4_jpeg_set_dec_bitstream_size (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  exynos4_jpeg_set_enc_dec_mode (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  exynos4_jpeg_set_enc_out_fmt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos4_jpeg_set_encode_hoff_cnt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos4_jpeg_set_encode_tbl_select (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos4_jpeg_set_huf_table_enable (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  exynos4_jpeg_set_huff_tbl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos4_jpeg_set_img_addr (struct s5p_jpeg_ctx*) ; 
 int /*<<< orphan*/  exynos4_jpeg_set_img_fmt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos4_jpeg_set_interrupt (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  exynos4_jpeg_set_jpeg_addr (struct s5p_jpeg_ctx*) ; 
 int /*<<< orphan*/  exynos4_jpeg_set_qtbl_chr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos4_jpeg_set_qtbl_lum (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos4_jpeg_set_stream_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos4_jpeg_set_sys_int_enable (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  exynos4_jpeg_sw_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos5433_jpeg_set_enc_out_fmt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos5433_jpeg_set_img_fmt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void exynos4_jpeg_device_run(void *priv)
{
	struct s5p_jpeg_ctx *ctx = priv;
	struct s5p_jpeg *jpeg = ctx->jpeg;
	unsigned int bitstream_size;
	unsigned long flags;

	spin_lock_irqsave(&jpeg->slock, flags);

	if (ctx->mode == S5P_JPEG_ENCODE) {
		exynos4_jpeg_sw_reset(jpeg->regs);
		exynos4_jpeg_set_interrupt(jpeg->regs, jpeg->variant->version);
		exynos4_jpeg_set_huf_table_enable(jpeg->regs, 1);

		exynos4_jpeg_set_huff_tbl(jpeg->regs);

		/*
		 * JPEG IP allows storing 4 quantization tables
		 * We fill table 0 for luma and table 1 for chroma
		 */
		exynos4_jpeg_set_qtbl_lum(jpeg->regs, ctx->compr_quality);
		exynos4_jpeg_set_qtbl_chr(jpeg->regs, ctx->compr_quality);

		exynos4_jpeg_set_encode_tbl_select(jpeg->regs,
							ctx->compr_quality);
		exynos4_jpeg_set_stream_size(jpeg->regs, ctx->cap_q.w,
							ctx->cap_q.h);

		if (ctx->jpeg->variant->version == SJPEG_EXYNOS4) {
			exynos4_jpeg_set_enc_out_fmt(jpeg->regs,
						     ctx->subsampling);
			exynos4_jpeg_set_img_fmt(jpeg->regs,
						 ctx->out_q.fmt->fourcc);
		} else {
			exynos5433_jpeg_set_enc_out_fmt(jpeg->regs,
							ctx->subsampling);
			exynos5433_jpeg_set_img_fmt(jpeg->regs,
						    ctx->out_q.fmt->fourcc);
		}
		exynos4_jpeg_set_img_addr(ctx);
		exynos4_jpeg_set_jpeg_addr(ctx);
		exynos4_jpeg_set_encode_hoff_cnt(jpeg->regs,
							ctx->out_q.fmt->fourcc);
	} else {
		exynos4_jpeg_sw_reset(jpeg->regs);
		exynos4_jpeg_set_interrupt(jpeg->regs,
					   jpeg->variant->version);
		exynos4_jpeg_set_img_addr(ctx);
		exynos4_jpeg_set_jpeg_addr(ctx);

		if (jpeg->variant->version == SJPEG_EXYNOS5433) {
			exynos4_jpeg_parse_huff_tbl(ctx);
			exynos4_jpeg_parse_decode_h_tbl(ctx);

			exynos4_jpeg_parse_q_tbl(ctx);
			exynos4_jpeg_parse_decode_q_tbl(ctx);

			exynos4_jpeg_set_huf_table_enable(jpeg->regs, 1);

			exynos4_jpeg_set_stream_size(jpeg->regs, ctx->cap_q.w,
					ctx->cap_q.h);
			exynos5433_jpeg_set_enc_out_fmt(jpeg->regs,
							ctx->subsampling);
			exynos5433_jpeg_set_img_fmt(jpeg->regs,
						    ctx->cap_q.fmt->fourcc);
			bitstream_size = DIV_ROUND_UP(ctx->out_q.size, 16);
		} else {
			exynos4_jpeg_set_img_fmt(jpeg->regs,
						 ctx->cap_q.fmt->fourcc);
			bitstream_size = DIV_ROUND_UP(ctx->out_q.size, 32);
		}

		exynos4_jpeg_set_dec_bitstream_size(jpeg->regs, bitstream_size);
	}

	exynos4_jpeg_set_sys_int_enable(jpeg->regs, 1);
	exynos4_jpeg_set_enc_dec_mode(jpeg->regs, ctx->mode);

	spin_unlock_irqrestore(&jpeg->slock, flags);
}