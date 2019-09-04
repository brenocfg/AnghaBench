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
struct s5p_mfc_ctx {unsigned int buf_width; unsigned int img_width; unsigned int buf_height; unsigned int img_height; scalar_t__ codec_mode; unsigned int luma_size; unsigned int chroma_size; unsigned int mv_size; } ;

/* Variables and functions */
 unsigned int ALIGN (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S5P_FIMV_DEC_BUF_ALIGN ; 
 int /*<<< orphan*/  S5P_FIMV_NV12MT_HALIGN ; 
 int /*<<< orphan*/  S5P_FIMV_NV12MT_VALIGN ; 
 scalar_t__ S5P_MFC_CODEC_H264_DEC ; 
 int /*<<< orphan*/  mfc_debug (int,char*,unsigned int,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static void s5p_mfc_dec_calc_dpb_size_v5(struct s5p_mfc_ctx *ctx)
{
	unsigned int guard_width, guard_height;

	ctx->buf_width = ALIGN(ctx->img_width, S5P_FIMV_NV12MT_HALIGN);
	ctx->buf_height = ALIGN(ctx->img_height, S5P_FIMV_NV12MT_VALIGN);
	mfc_debug(2,
		"SEQ Done: Movie dimensions %dx%d, buffer dimensions: %dx%d\n",
		ctx->img_width,	ctx->img_height, ctx->buf_width,
		ctx->buf_height);

	if (ctx->codec_mode == S5P_MFC_CODEC_H264_DEC) {
		ctx->luma_size = ALIGN(ctx->buf_width * ctx->buf_height,
				S5P_FIMV_DEC_BUF_ALIGN);
		ctx->chroma_size = ALIGN(ctx->buf_width *
				ALIGN((ctx->img_height >> 1),
					S5P_FIMV_NV12MT_VALIGN),
				S5P_FIMV_DEC_BUF_ALIGN);
		ctx->mv_size = ALIGN(ctx->buf_width *
				ALIGN((ctx->buf_height >> 2),
					S5P_FIMV_NV12MT_VALIGN),
				S5P_FIMV_DEC_BUF_ALIGN);
	} else {
		guard_width =
			ALIGN(ctx->img_width + 24, S5P_FIMV_NV12MT_HALIGN);
		guard_height =
			ALIGN(ctx->img_height + 16, S5P_FIMV_NV12MT_VALIGN);
		ctx->luma_size = ALIGN(guard_width * guard_height,
				S5P_FIMV_DEC_BUF_ALIGN);

		guard_width =
			ALIGN(ctx->img_width + 16, S5P_FIMV_NV12MT_HALIGN);
		guard_height =
			ALIGN((ctx->img_height >> 1) + 4,
					S5P_FIMV_NV12MT_VALIGN);
		ctx->chroma_size = ALIGN(guard_width * guard_height,
				S5P_FIMV_DEC_BUF_ALIGN);

		ctx->mv_size = 0;
	}
}